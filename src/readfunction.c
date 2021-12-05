#include "header.h"

void readFunction(FILE* inFile,char* buffer) {
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
  buffer += 8;
  buffer = trim(buffer);
  for (i=0; i<strlen(buffer); i++)
    if (buffer[i] == '{') buffer[i] = 0;
  buffer = trim(buffer);
  i = tokenizeAdd(buffer);
  action = (ACTION*)malloc(sizeof(ACTION));
  if (++numFunctions == 1) functions = (ACTION**)malloc(sizeof(ACTION*));
    else functions = (ACTION**)realloc(functions,sizeof(ACTION*)*numFunctions);
  functions[numFunctions-1] = action;
  action->numPhraseTokens = numTokens;
  action->phraseTokens = (int*)malloc(sizeof(int) * numTokens);
  for (i=0; i<numTokens; i++) action->phraseTokens[i] = tokens[i];
  action->numActionTokens = 0;
  action->actionTokens = readActionSteps(inFile,&(action->numActionTokens),buffer);
  }

