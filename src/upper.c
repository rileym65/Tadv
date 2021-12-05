#include "header.h"

char* upper(char* buffer) {
  int i;
  for (i=0; i<strlen(buffer); i++)
    if (buffer[i] >= 'a' && buffer[i] <= 'z') buffer[i] -= 32;
  return buffer;
  }

