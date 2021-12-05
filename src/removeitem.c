#include "header.h"

int removeItem(int itemNum,int roomNumber) {
  int i;
  int j;
  j = -1;
  for (i=0; i<rooms[roomNumber]->numItems; i++)
    if (rooms[roomNumber]->items[i] == items[itemNum]) j = i;
  if (j == -1) {
    return 0;
    }
  for (i=j; i<rooms[roomNumber]->numItems-1; i++)
    rooms[roomNumber]->items[i] =
    rooms[roomNumber]->items[i+1];
  if (--rooms[roomNumber]->numItems == 0)
    free(rooms[roomNumber]->items);
  else rooms[roomNumber]->items = (ITEM**)realloc(
    rooms[roomNumber]->items,
    sizeof(ITEM*) * rooms[roomNumber]->numItems);
  return -1;
  }

