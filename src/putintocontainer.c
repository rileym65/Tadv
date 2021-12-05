#include "header.h"

int putIntoContainer(int container, int item) {
  if (items[container]->container == 0) return -1;
  if (items[container]->numContents == items[container]->maxContents) return -1;
  items[container]->contents[items[container]->numContents++] = item;
  return 0;
  }

