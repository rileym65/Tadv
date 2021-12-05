#include "header.h"

int checkActions() {
  int i;
  int j;
  int k;
  int ip;
  char flag;
  for (i=0; i<numActions; i++)
    if (actions[i]->numPhraseTokens == numTokens) {
      flag = 1;
      for (j=0; j<numTokens; j++) {
        if (tokens[j] != actions[i]->phraseTokens[j]) flag = 0;
        }
      if (flag) {
        k = performAction(actions[i]->actionTokens,
                          actions[i]->numActionTokens);
        if (k == 100) return 0;
        if (k == 101) return -1;
        }
      }
  return 0;
  }

