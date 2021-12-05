#include "header.h"

int carrying(int item) {
  int i;
  for (i=0; i<player.numItems; i++)
    if (player.items[i] == items[item]) return -1;
  return 0;
  }

