#include "header.h"

int weight() {
  int i;
  int j;
  j = 0;
  for (i=0; i<player.numItems; i++) {
    j += player.items[i]->weight;
    if (player.items[i]->container != 0)
      j += containerWeight(player.items[i]->number);
    }
  return j;
  }

