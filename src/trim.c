#include "header.h"

char* trim(char* buffer) {
  while (*buffer == 32) buffer++;
  while (*buffer != 0 && buffer[strlen(buffer)-1] <= 32)
    buffer[strlen(buffer)-1] = 0;
  return buffer;
  }

