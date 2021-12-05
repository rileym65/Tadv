#include "header.h"

int getItem(int itemNum) {
  int i;
  int j;
  j = -1;
  for (i=0; i<rooms[player.location]->numItems; i++)
    if (rooms[player.location]->items[i] == items[itemNum]) j = i;
  if (j == -1) {
    printf("There is no %s here\n",items[itemNum]->name);
    return 0;
    }
  if (items[itemNum]->weight < 0) {
    printf("You cannot pick up this item\n");
    return 0;
    }
  if (++player.numItems == 1)
    player.items = (ITEM**)malloc(sizeof(ITEM*));
  else
    player.items = (ITEM**)realloc(player.items,
                   sizeof(ITEM*)*player.numItems);
  player.items[player.numItems-1] = items[itemNum];
  for (i=j; i<rooms[player.location]->numItems-1; i++)
    rooms[player.location]->items[i] =
    rooms[player.location]->items[i+1];
  if (--rooms[player.location]->numItems == 0)
    free(rooms[player.location]->items);
  else rooms[player.location]->items = (ITEM**)realloc(
    rooms[player.location]->items,
    sizeof(ITEM*) * rooms[player.location]->numItems);
  return -1;
  }

