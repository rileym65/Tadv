#include "header.h"

int checkRoomActions() {
  ROOM* room;
  int i;
  int j;
  int k;
  int ip;
  char flag;
  room = rooms[player.location];
  for (i=0; i<room->numActions; i++)
    if (room->actions[i]->numPhraseTokens == numTokens) {
      flag = 1;
      for (j=0; j<numTokens; j++) {
        if (tokens[j] != room->actions[i]->phraseTokens[j]) flag = 0;
        }
      if (flag) {
        k = performAction(room->actions[i]->actionTokens,
                          room->actions[i]->numActionTokens);
        if (k == 100) return 0;
        if (k == 101) return -1;
        }
      }
  return 0;
  }

