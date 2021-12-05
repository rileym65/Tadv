#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

char* fileRead(char* buffer,FILE* file) {
  char* ret;
  char temp[1024];
  ret = fgets(buffer,1023,file);
  if (encrypted == 'Y' && ret != NULL) {
    decrypt(buffer,temp,&key);
    strcpy(buffer,temp);
    }
  while (strlen(buffer) > 0 && buffer[strlen(buffer)-1] <= ' ')
    buffer[strlen(buffer)-1] = 0;
  return ret;
  }

int rcs_random(int size) {
  float r;
  r = rand();
  r /= RAND_MAX;
  r -= (int)r;
  r *= size;
  return (int)r;
  }

void rcs_randomize() {
  time_t t;
  t = time(&t);
  t&=0xfffff;
  srand(t);
  }

int numberForItem(ITEM* item) {
  int i;
  for (i=0; i<numItems; i++)
    if (item == items[i]) return i;
  return -1;
  }

char* upper(char* buffer) {
  int i;
  for (i=0; i<strlen(buffer); i++)
    if (buffer[i] >= 'a' && buffer[i] <= 'z') buffer[i] -= 32;
  return buffer;
  }

char* trim(char* buffer) {
  while (*buffer == 32) buffer++;
  while (*buffer != 0 && buffer[strlen(buffer)-1] <= 32)
    buffer[strlen(buffer)-1] = 0;
  return buffer;
  }

char* nextWord(char* buffer) {
  while (*buffer != 0 && *buffer != 32) buffer++;
  while (*buffer != 0 && *buffer == 32) buffer++;
  return buffer;
  }

int getToken(char* buffer) {
  int i;
  for (i=0; i<numVocab; i++) {
    if (strcmp(upper(buffer),upper(vocab[i])) == 0) return i;
    }
  return -1;
  }

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

void printToken(int token) {
  if (token >=40000 && token < 50000) printf("%s",items[token-40000]->description);
  else printf("%s",vocab[token]);
  }

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

int carrying(int item) {
  int i;
  for (i=0; i<player.numItems; i++)
    if (player.items[i] == items[item]) return -1;
  return 0;
  }

