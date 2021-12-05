#include "header.h"

void readAction(FILE* inFile,char* buffer) {
  ACTION* action;
  char    flag;
  char*   pWrd;
  char*   pBuf;
  char    wrd[255];
  char    buf2[1024];
  char    arg;
  int     token;
  int i;
  int j;
  buffer += 6;
  buffer = trim(buffer);
  strcpy(buf2, buffer);
  for (i=0; i<strlen(buffer); i++)
    if (buffer[i] == '{') buffer[i] = 0;
  buffer = trim(buffer);
  i = tokenizeAdd(buffer);
  action = (ACTION*)malloc(sizeof(ACTION));
  if (++numActions == 1) actions = (ACTION**)malloc(sizeof(ACTION*));
    else actions = (ACTION**)realloc(actions,sizeof(ACTION*) * numActions);
  actions[numActions-1] = action;
  action->numPhraseTokens = numTokens;
  action->phraseTokens = (int*)malloc(sizeof(int) * numTokens);
  for (i=0; i<numTokens; i++) action->phraseTokens[i] = tokens[i];
  action->numActionTokens = 0;
  action->actionTokens = readActionSteps(inFile,&(action->numActionTokens),buf2);
  }

