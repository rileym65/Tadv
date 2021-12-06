#include "header.h"

int dropItem(int itemNum) {
  int i;
  int j;
  j = -1;
  for (i=0; i<player.numItems; i++)
    if (player.items[i] == items[itemNum]) j = i;
  if (j == -1) {
    printf("Your are not carrying $s\n",items[itemNum]->name);
    return 0;
    }
  if (++rooms[player.location]->numItems == 1)
    rooms[player.location]->items = (ITEM**)malloc(sizeof(ITEM*));
  else
    rooms[player.location]->items = (ITEM**)realloc(
      rooms[player.location]->items,
      sizeof(ITEM*) * rooms[player.location]->numItems);
  rooms[player.location]->items[rooms[player.location]->numItems-1] =
    items[itemNum];

  takeFromInventory(itemNum);
//  for (i=j; i<player.numItems-1; i++)
//    player.items[i] = player.items[i+1];
//  if (--player.numItems == 0) free(player.items);
//    else player.items = (ITEM**)realloc(player.items,
//      sizeof(ITEM*) * player.numItems);

  return -1;
  }

