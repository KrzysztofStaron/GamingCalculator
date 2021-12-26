#include "menu.h"

int activeGame = 3;

void ubdateActiveGame(TFT_ILI9163C display, bool reload) {
  int button = GetButton();

  if (!(button == UP || button == DOWN || reload)) {
    return ;
  }

  for (int x = 4; x < 127; x++) {
    for (int y = activeGame * 30 + 9; y < activeGame * 30 + 26; y++) {
      display.drawPixel(x, y, BLACK);
    }
  }

  if (button == UP) {
    if (activeGame > 0) {
      activeGame--;
    } else {
      activeGame = 3;
    }
  } else if (button == DOWN) {
    if (activeGame < 3) {
      activeGame++;
    } else {
      activeGame = 0;
    }
  }

  for (int x = 4; x < 127; x++) {
    for (int y = activeGame * 30 + 9; y < activeGame * 30 + 26; y++) {
      display.drawPixel(x, y, 0xCFC0);
    }
  }

  if (activeGame == 0) {
    display.setTextColor(0x0200);
  } else {
    display.setTextColor(WHITE);
  }
  display.setCursor(5, 10);
  display.print(" Max CPS");

  if (activeGame == 1) {
    display.setTextColor(0x0100);
  } else {
    display.setTextColor(WHITE);
  }
  display.setCursor(5, 40);
  display.print("  Space");

  if (activeGame == 2) {
    display.setTextColor(0x0100);
  } else {
    display.setTextColor(WHITE);
  }
  display.setCursor(5, 70);
  display.print("  Barka"); //tajne

  if (activeGame == 3) {
    display.setTextColor(0x0100);
  } else {
    display.setTextColor(WHITE);
  }
  display.setCursor(5, 100);
  display.print(" rubic2x2");
}

void beginMenu(TFT_ILI9163C display) {
  display.fillScreen(BLACK);
  Serial.println("Loaded: menu");
}

int menu(TFT_ILI9163C display, bool reload) {
  if (reload) {
    beginMenu(display);
  }
  ubdateActiveGame(display, reload);
  if (GetButton() == ACTION) {
    return activeGame + 1;
  } else {
    return 0;
  }
}
