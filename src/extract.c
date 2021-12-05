#include "header.h"

void extract(int item) {
  int i;
  int j;
  for (i=0; i<numRooms; i++) removeItem(item, i);
  takeFromInventory(item);
  for (i=0; i<player.numItems; i++)
    if (player.items[i]->container != 0)
      takeFromContainer(player.items[i]->number, item);
  }

