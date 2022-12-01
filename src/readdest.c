#include "header.h"

void read_dest(char* buffer,int* link) {
  char name[256];
  int  pos;
  pos = 0;
  while (*buffer != 0 && *buffer != ' ') name[pos++] =*buffer++;
  name[pos] = 0;
  link[0] = getValue(name);
  while (*buffer != 0 && *buffer != ' ') buffer++;
  if (*buffer == 0) {
    link[1] = -1;
    return;
    }
  while (*buffer == ' ') buffer++;
  if (strncasecmp(buffer,"door",4) == 0) {
    while (*buffer != 0 && *buffer != ' ') buffer++;
    while (*buffer == ' ') buffer++;
    link[1] = getValue(buffer);
    }
  else {
    printf("Error in direction: %s\n",buffer);
    }
  }

