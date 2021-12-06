#include "header.h"

int putIntoInventory(int item) {
  if (items[item]->weight < 0) return -1;
  if ((weight() + items[item]->weight) > player.maxWeight) return -2;
  if (player.numItems >= player.maxItems) return -3;
  if (++player.numItems == 1)
    player.items = (ITEM**)malloc(sizeof(ITEM*));
  else
    player.items = (ITEM**)realloc(player.items,
                   sizeof(ITEM*)*player.numItems);
  player.items[player.numItems-1] = items[item];
  if (items[item]->numAcquiredSteps > 0)
    performAction(items[item]->acquiredSteps,items[item]->numAcquiredSteps);
  return 0;
  }

