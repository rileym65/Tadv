#include "header.h"

int takeFromContainer(int container, int item) {
  int i;
  int j;
  j = -1;
  for (i=0; i<items[container]->numContents; i++)
    if (items[container]->contents[i] == item) j = i;
  if (j < 0) return -1;
  for (i=j; i<items[container]->numContents-1; i++)
    items[container]->contents[i] = items[container]->contents[i+1];
  items[container]->numContents--;
  return item;
  }

