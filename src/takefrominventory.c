#include "header.h"

int takeFromInventory(int item) {
  int i;
  int j;
  j = -1;
  for (i=0; i<player.numItems; i++)
    if (player.items[i] == items[item]) j = i;
  if (j >= 0) {
    for (i=j; i<player.numItems-1; i++)
      player.items[i] = player.items[i+1];
    if (--player.numItems == 0) free(player.items);
      else player.items = (ITEM**)realloc(player.items,
        sizeof(ITEM*) * player.numItems);
    return item;
    }
  return -1;
  }

