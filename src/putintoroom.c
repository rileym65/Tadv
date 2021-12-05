#include "header.h"

void putIntoRoom(int room, int item) {
  int i;
  int j;
  if (++rooms[room]->numItems == 1)
    rooms[room]->items = (ITEM**)malloc(sizeof(ITEM*));
  else
    rooms[room]->items = (ITEM**)realloc(
      rooms[room]->items,
      sizeof(ITEM*) * rooms[room]->numItems);
  rooms[room]->items[rooms[player.location]->numItems-1] = items[item];
  }

