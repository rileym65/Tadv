#include "header.h"

int score() {
  int i;
  int j;
  j = player.score;
  for (i=0; i<player.numItems; i++) {
    j += player.items[i]->score;
    if (player.items[i]->container != 0)
      j += containerScore(player.items[i]->number);
    }
  return j;
  }

