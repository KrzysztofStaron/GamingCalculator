#include "GetButtons.h"

int GetButton() {
  for (int i = 3; i <= 7; i++) {
    if (!digitalRead(i)) {
      return i - 3;
    }
  }
  return 5;
}
