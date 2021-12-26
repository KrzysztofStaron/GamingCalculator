#include "tajne.h"

void test(TFT_ILI9163C display) {
  if (!digitalRead(12)) {
    display.begin();
  }
}

void beginTajne(TFT_ILI9163C display) {
  display.fillScreen(BLACK);
  display.setCursor(10, 0);
  Serial.print("Loaded: tajne");
}

void tajne(TFT_ILI9163C display, bool reload) {
  if (reload) {
    beginTajne (display);
  }
  display.setTextSize(1);
  display.clearScreen();
  display.setCursor(10, 50);
  display.print("Never gonna give");
  display.setCursor(30, 60);
  display.print("you up");
  display.setCursor(10, 50);
  test(display);
  delay(1500);
  display.clearScreen();
  display.print("Never gonna let");
  display.setCursor(30, 60);
  display.print("you down");
  display.setCursor(10, 50);
  test(display);
  delay(1500);
  display.clearScreen();
  display.print("Never gonna make");
  display.setCursor(30, 60);
  display.print("you cry");
  display.setCursor(10, 50);
  test(display);
  delay(1500);
  display.clearScreen();
  display.print("Never gonna say");
  display.setCursor(30, 60);
  display.print("goodbye");
  display.setCursor(0, 0);
  test(display);
  delay(1500);
  display.setTextSize(2);
}
