#include "header.h"

int doorsInRoom(int room,int* door) {
  int i;
  i = 0;
  if (rooms[room]->north[1] >= 0) { i++; *door = (rooms[room]->north[1]); }
  if (rooms[room]->south[1] >= 0) { i++; *door = (rooms[room]->south[1]); }
  if (rooms[room]->east[1] >= 0) { i++; *door = (rooms[room]->east[1]); }
  if (rooms[room]->west[1] >= 0) { i++; *door = (rooms[room]->west[1]); }
  if (rooms[room]->up[1] >= 0) { i++; *door = (rooms[room]->up[1]); }
  if (rooms[room]->down[1] >= 0) { i++; *door = (rooms[room]->down[1]); }
  if (rooms[room]->ne[1] >= 0) { i++; *door = (rooms[room]->ne[1]); }
  if (rooms[room]->nw[1] >= 0) { i++; *door = (rooms[room]->nw[1]); }
  if (rooms[room]->se[1] >= 0) { i++; *door = (rooms[room]->se[1]); }
  if (rooms[room]->sw[1] >= 0) { i++; *door = (rooms[room]->sw[1]); }
  return i;
  }

