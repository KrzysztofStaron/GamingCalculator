#ifndef MENU_H
#define MENU_H

#include <TFT_ILI9163C.h>

#include <Arduino.h>
#include "GetButtons.h"
#include "display.h"
#include "memory.h"

#define GAMES 5

int menu(TFT_ILI9163C dis, bool reload);

#endif
