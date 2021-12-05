#include "header.h"

void addWord(char* wrd) {
  int i;
  if (debug) printf("Adding vocabulary: %s\n",wrd); fflush(stdout);
  for (i=0; i<numVocab; i++)
    if (strcasecmp(wrd,vocab[i]) == 0) return;
  numVocab++;
  if (numVocab == 1) vocab = (char**)malloc(sizeof(char*));
    else vocab = (char**)realloc(vocab,sizeof(char*) * numVocab);
  vocab[numVocab-1] = (char*)malloc(strlen(wrd) + 1);
  strcpy(vocab[numVocab-1], wrd);
  }

