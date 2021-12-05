#include "header.h"

int getRoomNumber(char* wrd) {
  int i;
  int j;
  if (wrd[0] >= '0' && wrd[0] <= '9') return atoi(wrd);
  for (i=0; i<numRooms; i++) {
    if (rooms[i]->name != NULL)
      if (strcasecmp(wrd,rooms[i]->name) == 0) return i;
    }
  return -1;
  }

