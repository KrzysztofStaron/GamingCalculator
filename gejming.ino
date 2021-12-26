#include "menu.h" // 0
#include "maxCps.h" // 1
#include "space.h" // 2
#include "tajne.h" // 3
#include "rubic.h" // 4

#include "display.h"

int scene = 0;
bool changeScene = true;
bool readyToChange;

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

#define __CS 10
#define __DC 9

TFT_ILI9163C display = TFT_ILI9163C(__CS, 8, __DC);

void setup() {
  display.begin();
  display.setTextSize(2);
  Serial.begin(9600);

  for (int i = 2; i <= 7; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(12, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(2) && scene != 0) {
    scene = 0;
    changeScene = true;
  }
  if (!digitalRead(12)) { // reset
    display.begin();
    changeScene = true;
  }


  if (scene == 0) {
    int newScene = menu(display, changeScene);
    if (GAMES > newScene) {
      scene = newScene;
    }
    if (scene != 0) {
      readyToChange = true;
      changeScene = true;
    }
    delay(65);
  } else if (scene == 1) {
    maxcps(display, changeScene);
  } else if (scene == 2) {
    if (space(display, changeScene)) {
      scene = 0;
      readyToChange = true;
      changeScene = true;
    }
    delay(120 - (readByte(0) * 2));
  } else if (scene == 3) {
    tajne(display, changeScene);
  } else if (scene == 4) {
    rubic(display, changeScene);
    delay(100);
  }
  if (!readyToChange) {
    changeScene = false;
  } else {
    readyToChange = false;
  }
}
