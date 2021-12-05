#include "header.h"

int containerWeight(int container) {
  int i;
  int j;
  j = 0;
  for (i=0; i<items[container]->numContents; i++) {
    j += items[items[container]->contents[i]]->weight;
    if (items[items[container]->contents[i]]->container != 0)
      j += containerWeight(items[items[container]->contents[i]]->number);
    }
  return j;
  }

