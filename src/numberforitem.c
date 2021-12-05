#include "header.h"

int numberForItem(ITEM* item) {
  int i;
  for (i=0; i<numItems; i++)
    if (item == items[i]) return i;
  return -1;
  }

