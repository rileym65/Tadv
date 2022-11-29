#include "header.h"

int checkRoomActions() {
  ROOM* room;
  int i;
  int j;
  int k;
  int ip;
  char flag;
  int nTokens;
  int tkns[256];
  char buffer[1024];
  char tkn[256];
  int p;
  nTokens = 0;
  i = 0;
  while (i < numTokens) {
    if (tokens[i] >= 40000) {
      strcpy(buffer,items[tokens[i]-40000]->name);
      i++;
      p = 0;
      j = 0;
      while (buffer[j] == ' ') j++;
      while (buffer[j] != 0) {
        while (buffer[j] > ' ') tkn[p++] = buffer[j++];
        tkn[p] = 0;
        tkns[nTokens++] = getToken(tkn);
        while (buffer[j] == ' ') j++;
        }
      }
    else
      tkns[nTokens++] = tokens[i++];
    }
  
  room = rooms[player.location];
  for (i=0; i<room->numActions; i++)
    if (room->actions[i]->numPhraseTokens == nTokens) {
      flag = 1;
      for (j=0; j<nTokens; j++) {
        if (tkns[j] != room->actions[i]->phraseTokens[j]) flag = 0;
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

