#include "header.h"

void reset() {
  int i;
  int loc;
  player.items = NULL;
  player.numItems = 0;
  player.location = -1;
  player.lastLocation = -1;
  player.score = 0;
  player.health = 100;
  for (i=0; i<numRooms; i++) {
    if (strcasecmp(rooms[i]->name, startingRoom) == 0) player.location=i;
    }
  if (player.location < 0) {
    if (startingRoom[0] >= '0' && startingRoom[0] <= '9')
      player.location = atoi(startingRoom);
    }
  if (player.location < 0) player.location = 0;
  for (i=0; i<numRooms; i++) {
    if (rooms[i]->items != NULL) free(rooms[i]->items);
    rooms[i]->items = NULL;
    rooms[i]->numItems = 0;
    }
  for (i=0; i<numItems; i++) {
    if (items[i]->location >= 0 && items[i]->beingworn == 0 && items[i]->startingItem == 0) {
      loc = items[i]->location;
      rooms[loc]->numItems++;
      if (rooms[loc]->numItems == 1)
        rooms[loc]->items = (ITEM**)malloc(sizeof(ITEM*));
      else
        rooms[loc]->items = (ITEM**)realloc(rooms[loc]->items,
          sizeof(ITEM*) * rooms[loc]->numItems);
      rooms[loc]->items[rooms[loc]->numItems - 1] = items[i];
      }
    if (items[i]->beingworn != 0 || items[i]->startingItem != 0) {
      if (++player.numItems == 1)
        player.items = (ITEM**)malloc(sizeof(ITEM*));
      else
        player.items = (ITEM**)realloc(player.items,
                       sizeof(ITEM*)*player.numItems);
      player.items[player.numItems-1] = items[i];
      }
    }
  }

