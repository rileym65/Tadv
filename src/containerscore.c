#include "header.h"

int containerScore(int container) {
  int i;
  int j;
  j = 0;
  for (i=0; i<items[container]->numContents; i++) {
    j += items[items[container]->contents[i]]->score;
    if (items[items[container]->contents[i]]->container != 0)
      j += containerScore(items[items[container]->contents[i]]->number);
    }
  return j;
  }

