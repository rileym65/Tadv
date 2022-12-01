#include "header.h"

int checkObjects() {
  ROOM* room;
  int i;
  int j;
  int k;
  int r;
  int item;
  char flag;
  if (numTokens < 2) return 0;
  if (tokens[numTokens-1] < 40000 || tokens[numTokens-1] >= 50000) return 0;
  item = tokens[numTokens-1] - 40000;
  for (i=0; i<player.numItems; i++) {
//    if (strcasecmp(player.items[i]->name,vocab[tokens[numTokens-1]]) == 0) {
    if (player.items[i] == items[item]) {
      for (j=0; j<player.items[i]->numActions; j++) {
        flag = 1;
        for (k=0; k<numTokens-1; k++)
          if (k < player.items[i]->actions[j]->numPhraseTokens &&
              tokens[k] != player.items[i]->actions[j]->phraseTokens[k])
            flag = 0;
        if (flag) {
          r = performAction(player.items[i]->actions[j]->actionTokens,
                            player.items[i]->actions[j]->numActionTokens);
          if (r == 100) return 0;
          if (r == 101) return -1;
          }
        }
      }
    }
  room = rooms[player.location];
  for (i=0; i<room->numItems; i++)
//    if (strcasecmp(room->items[i]->name,vocab[tokens[numTokens-1]]) == 0) {
    if (room->items[i] == items[item]) {
      for (j=0; j<room->items[i]->numActions; j++) {
        flag = 1;
        for (k=0; k<numTokens-1; k++)
          if (tokens[k] != room->items[i]->actions[j]->phraseTokens[k])
            flag = 0;
        if (flag) {
          r = performAction(room->items[i]->actions[j]->actionTokens,
                            room->items[i]->actions[j]->numActionTokens);
          if (r == 100) return 0;
          if (r == 101) return -1;
          }
        }
      }
  return 0;
  }

