#include "header.h"

int carryingInContainer(int container, int item) {
  int i;
  for (i=0; i<items[container]->numContents; i++) {
    if (items[container]->contents[i] == item) return -1;
    if (items[items[container]->contents[i]]->container != 0) {
      if (carryingInContainer(items[container]->contents[i], item)) return -1;
      }
    }
  return 0;
  }

int carrying(int item) {
  int i;
  for (i=0; i<player.numItems; i++) {
    if (player.items[i] == items[item]) return -1;
    if (player.items[i]->container != 0)
      if (carryingInContainer(player.items[i]->number, item)) return -1;
    }
  return 0;
  }

