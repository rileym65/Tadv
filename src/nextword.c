#include "header.h"

char* nextWord(char* buffer) {
  while (*buffer != 0 && *buffer != 32) buffer++;
  while (*buffer != 0 && *buffer == 32) buffer++;
  return buffer;
  }

