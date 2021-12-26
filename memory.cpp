#include "memory.h"

int numbers[4];
char bytes[4];

int readNumber(char index) {
  return numbers[index];
}

void writeNumber(char index, int num) {
  numbers[index] = num;
}


char readByte(char index) {
  return bytes[index];
}

void writeByte(char index, char num) {
  bytes[index] = num;
}
