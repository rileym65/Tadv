#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int tokenize(char* buffer) {
  int  i;
  int  token;
  char wrd[255];
  char *pWord;
  numTokens = 0;
  buffer = trim(buffer);
  if (debug) printf("Tokenizing: %s\n[",buffer); fflush(stdout);
  while (*buffer != 0) {
    pWord = wrd;
    while (*buffer > ' ') *pWord++ = *buffer++;
    *pWord = 0;
    token = -1;
    for (i=0; i<numVocab; i++) {
      if (strcmp(upper(wrd),upper(vocab[i])) == 0) token = i;
      }
    for (i=0; i<numItems; i++) {
      if (strcmp(upper(wrd),upper(items[i]->name)) == 0) token = i+40000;
      }
    if (token == -1) {
      printf("I do not understand %s\n",wrd);
      return -1;
      }
    tokens[numTokens++] = token;
    if (debug) printf(" %d",token);
    while (*buffer > 0 && *buffer <= ' ') buffer++;
    }
  if (debug) printf(" ]\n");
  return numTokens;
  }

