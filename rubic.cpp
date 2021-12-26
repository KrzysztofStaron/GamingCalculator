#include "rubic.h"
/*
  colors:
    0: Red
    1: Green
    2: Magenta
    3: Blue

    4: Yellow
    5: White
*/

#define MARGIN 50

char faces[6][4];
char currentFace = 0;
bool rotationY = 1; // 0 - White Top
char rotationType = 0;

#define LEFT_FACE false
#define TOP_FACE true

// int16_t color
char getFace(char num) {
  if (rotationY) {
    if (num + 1 > 3) {
      return 0;
    }

    return num + 1;
  } else {
    if (num - 1 < 0) {
      return 3;
    }

    return num - 1;
  }
}

int16_t numToColor(char num) {
  switch (num) {
    case 0:
      return RED;
      break;
    case 1:
      return GREEN;
      break;
    case 2:
      return MAGENTA;
      break;
    case 3:
      return BLUE;
      break;
    case 4:
      return YELLOW;
      break;
    case 5:
      return WHITE;
      break;

  }
}

char slant(char num) {
  switch (num) {
    case 0:
      return 3;
      break;
    case 1:
      return 2;
      break;
    case 2:
      return 1;
      break;
    case 3:
      return 0;
      break;
  }
}

char vertical(char num) {
  switch (num) {
    case 0:
      return 1;
      break;
    case 1:
      return 3;
      break;
    case 2:
      return 0;
      break;
    case 3:
      return 2;
      break;
  }
}

char calcRotation(char num) {
  switch (num) {
    case 0:
      return 0;
      break;
    case 1:
      return 1;
      break;
    case 2:
      return 3;
      break;
    case 3:
      return 2;
      break;
  }
}

char GetButton12(bool rotateButton = false) {
  for (char i = 4; i <= 7; i++) {
    if (!digitalRead(i)) {
      if (digitalRead(3) || rotateButton) {
        return i - 3;
      } else if (!digitalRead(3)) {
        return i + 3; //i - 3 + 6
      }
    }
  }

  if (!digitalRead(14)) {
    if (digitalRead(3) || rotateButton) {
      return 5;
    } else if (!digitalRead(3)) {
      return 10;
    }
  }

  if (!digitalRead(15)) {
    if (digitalRead(3) || rotateButton) {
      return 6;
    } else if (!digitalRead(3)) {
      return 11;
    }
  }



  return 12;
}

void ubdateFaces(TFT_ILI9163C display) {
  char Size = 25;
  char block;

  for (char xc = 0; xc < 2; xc++) {
    for (char yc = 0 ; yc < 2; yc++) {
      for (char x = MARGIN + xc * Size; x < MARGIN + xc * Size + Size; x++) {
        for (char y = MARGIN + yc * Size ; y < MARGIN + yc * Size + Size; y++) {
          display.drawPixel(x, y, numToColor(faces[currentFace][block]));
        }
      }
      block++;
    }
  }

  block = 0;

  for (char i = MARGIN - Size; i < MARGIN; i++) {
    if (i < (MARGIN - Size) + (MARGIN - (MARGIN - Size)) / 2) {
      block = 0;
    } else {
      block = 2;
    }
    for (char y = 0; y < Size; y++) {
      if (rotationY == 0) {
        display.drawPixel(i, i + y, numToColor(faces[getFace(currentFace)][block]));
        display.drawPixel(i, i + y + Size, numToColor(faces[getFace(currentFace)][block + 1]));
      } else {
        display.drawPixel(i, i + y, numToColor(faces[getFace(currentFace)][2 - block]));
        display.drawPixel(i, i + y + Size, numToColor(faces[getFace(currentFace)][3 - block]));
      }
    }
  }

  block = 0;
  for (char x = MARGIN - Size; x < MARGIN + Size; x++) {
    char face = 0;
    if (rotationY) {
      face = 5;
    } else {
      face = 4;
    }
    if (x < MARGIN - Size + ((MARGIN + Size) - (MARGIN - Size)) / 2) {
      block = 0;
    } else {
      block = 2;
    }
    for (char i = 0; i < Size; i++) {
      char f0 = calcRotation(currentFace);
      char f1 = vertical(f0);
      char f2 = slant(f1);
      char f3 = slant(f0);

      if (i < Size / 2) {
        if (block == 0) {
          display.drawPixel(x + i, MARGIN - Size + i, numToColor(faces[face][f0])); // 0
        } else {
          display.drawPixel(x + i, MARGIN - Size + i, numToColor(faces[face][f2])); // 2
        }
      } else {
        if (block == 2) {
          display.drawPixel(x + i, MARGIN - Size + i, numToColor(faces[face][f3])); // 3
        } else {
          display.drawPixel(x + i, MARGIN - Size + i, numToColor(faces[face][(f1)])); // 1
        }
      }
    }
    //faces[getFace(currentFace)][block + 2]
  }
}

void setupRubic(TFT_ILI9163C display) {
  for (char i = 0; i < 6; i++) {
    for (char o = 0; o < 4; o++) {
      faces[i][o] = i;
    }
  }

  display.fillScreen(0x6690);
  Serial.println("Loaded: rubic");

  ubdateFaces(display);
}

void rotate() {
  char button = GetButton12(true);
  if (button == 1) {
    if (currentFace + 1 > 3) {
      currentFace = 0;
    } else  {
      currentFace++;
    }
    rotationType = 1;
  } else if (button == 4) {
    if (currentFace - 1 < 0) {
      currentFace = 3;
    } else {
      currentFace--;
    }
    rotationType = -1;
  } else if (button == 3 || button == 2) {
    if (rotationY == 0) {
      rotationY = 1;
      if (getFace(getFace(currentFace)) - 1 < 0) {
        currentFace = 3;
      } else {
        currentFace = getFace(getFace(currentFace)) - 1;
      }
    } else {
      rotationY = 0;
      if (getFace(getFace(currentFace)) + 1 > 3) {
        currentFace = 0;
      } else {
        currentFace = getFace(getFace(currentFace)) + 1;
      }
    }
  }
  Serial.println(currentFace);
}

void rubic(TFT_ILI9163C display, bool reload) {
  if (reload) {
    setupRubic(display);
  }
  if (!digitalRead(16)) {
    rotate();
  } else {
    int button = GetButton12();
    if (button == 12) {
      return ;
    }
    Serial.println(button);
  }

  ubdateFaces(display);
}
