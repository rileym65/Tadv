#include "header.h"

int takeFromRoom(int room, int item) {
  int i;
  int j;
  j = -1;
  for (i=0; i<rooms[room]->numItems; i++)
    if (rooms[room]->items[i] == items[item]) j = i;
  if (j == -1) return -1;
  for (i=j; i<rooms[room]->numItems-1; i++)
    rooms[room]->items[i] = rooms[room]->items[i+1];
  if (--rooms[room]->numItems == 0)
    free(rooms[room]->items);
  else rooms[room]->items = (ITEM**)realloc(
    rooms[room]->items,
    sizeof(ITEM*) * rooms[room]->numItems);
  return item;
  }

