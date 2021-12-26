#include "space.h"

#define STARS 100

char starPos[STARS][2];
char meteorsY[5];
bool meteors[5];

void stars(TFT_ILI9163C display) {
  for (int i = 0; i < STARS; i++) {
    display.drawPixel(starPos[i][0], starPos[i][1], 0xFF60);
  }
}

void spaceSetup(TFT_ILI9163C display) {
  Serial.println("Loaded: space");
  writeByte(0, 0);
  writeByte(1, 5);
  for (char i = 0; i < sizeof(meteors); i++) {
    meteors[i] = 0;
    meteorsY[i] = 0;
  }
  display.fillScreen(BLACK);
  for (int i = 0; i < STARS; i++) {
    char newPos[2] = {(char)random(0, 128), (char)random(0, 128)};
    starPos[i][0] = newPos[0];
    starPos[i][1] = newPos[1];
  }
}

void renderPlayer(TFT_ILI9163C display) {
  for (char y = 100; y < 120; y++) {
    for (char x = readByte(0) * 22; x < readByte(0) * 22 + 20; x++) {
      display.drawPixel(x + 10, y, WHITE);
    }
  }
}

void tryMove(TFT_ILI9163C display) {
  if (GetButton() == LEFT) {
    for (char y = 100; y < 120; y++) {
      for (char x = readByte(0) * 22; x < readByte(0) * 22 + 20; x++) {
        display.drawPixel(x + 10, y, BLACK);
      }
    }
    if (readByte(0) > 0) {
      writeByte(0, readByte(0) - 1);
    } else {
      writeByte(0, 4);
    }
  } else if (GetButton() == RIGHT) {
    for (char y = 100; y < 120; y++) {
      for (char x = readByte(0) * 22; x < readByte(0) * 22 + 20; x++) {
        display.drawPixel(x + 10, y, BLACK);
      }
    }
    if (readByte(0) < 4) {
      writeByte(0, readByte(0) + 1);
    } else {
      writeByte(0, 0);
    }
  }
  renderPlayer(display);
}

void renderMeteor(TFT_ILI9163C display) {
  for (int i = 0; i < sizeof(meteors); i++) {
    if (meteors[i] == true) {
      for (char y = meteorsY[i]; y < meteorsY[i] + 20; y++) {
        for (char x = i * 22; x < i * 22 + 20; x++) {
          display.drawPixel(x + 10, y, BLACK);
        }
      }
      meteorsY[i] += readByte(1);
      if (meteorsY[i] + 20 < 128) {
        for (char y = meteorsY[i]; y < meteorsY[i] + 20; y++) {
          for (char x = i * 22; x < i * 22 + 20; x++) {
            display.drawPixel(x + 10, y, RED);
          }
        }
      } else {
        if (readByte(1) < 15) {
          writeByte(1, readByte(1) + 1);
        }
        meteorsY[i] = 0;
        meteors[i] = false;
      }
    }
  }
}

void meteor(TFT_ILI9163C display) {
  Serial.print("Metor: ");
  int num = random(0, 6);
  if (meteors[num] == false) {
    meteors[num] = true;
    Serial.println(num);
  } else {
    Serial.println("failled");
  }
}

bool space(TFT_ILI9163C display, bool reload) {
  if (reload) {
    spaceSetup(display);
  }
  if (random(0, 16 - readByte(1)) == 0) {
    meteor(display);
  }

  tryMove(display);
  stars(display);
  renderMeteor(display);
  if (meteors[readByte(0)] && meteorsY[readByte(0)] + 20 > 100) {
    Serial.print("ded");
    return true;
  }
  return false;
}
