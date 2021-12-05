#include "header.h"

int tokenizeAdd(char* buffer) {
  int  i;
  int  token;
  char wrd[255];
  char *pWord;
  numTokens = 0;
  buffer = trim(buffer);
  while (*buffer != 0) {
    pWord = wrd;
    while (*buffer > ' ') *pWord++ = *buffer++;
    *pWord = 0;
    token = -1;
    for (i=0; i<numVocab; i++) {
      if (strcmp(upper(wrd),upper(vocab[i])) == 0) token = i;
      }
    if (token == -1) {
      if (++numVocab == 1) vocab = (char**)malloc(sizeof(char*));
        else vocab = (char**)realloc(vocab,sizeof(char*) * numVocab);
      vocab[numVocab-1] = (char*)malloc(strlen(wrd)+1);
      strcpy(vocab[numVocab-1],wrd);
      token = numVocab-1;
      }
    tokens[numTokens++] = token;
    while (*buffer > 0 && *buffer <= ' ') buffer++;
    }
  return numTokens;
  }

