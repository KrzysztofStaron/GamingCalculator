#include "maxCps.h"

long counter = 0;

void beginMaxCps(TFT_ILI9163C display){
  display.fillScreen(BLACK);
  Serial.println("Loaded: space");  
}

void maxcps(TFT_ILI9163C display, bool reload) {
  if (reload){
    beginMaxCps(display);
  }
  counter++;
  for (int x = 20; x < 80; x++) {
    for (int y = 50; y < 65; y++) {
      display.drawPixel(x, y, BLACK);
    }
  }
  display.setCursor(20, 50);
  display.print(counter); 
}
