#include "header.h"

void putIntoInventory(int item) {
  if (++player.numItems == 1)
    player.items = (ITEM**)malloc(sizeof(ITEM*));
  else
    player.items = (ITEM**)realloc(player.items,
                   sizeof(ITEM*)*player.numItems);
  player.items[player.numItems-1] = items[item];
  }

