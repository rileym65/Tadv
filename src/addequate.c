#include "header.h"

void addEquate(char* name, int value) {
  if (debug) printf("Adding equate: %s = %d\n",name, value); fflush(stdout);
  if (++numEquates == 1) {
    equates = (char**)malloc(sizeof(char*));
    eqValues = (int*)malloc(sizeof(int));
    }
  else {
    equates = (char**)realloc(equates,sizeof(char*) * numEquates);
    eqValues = (int*)realloc(eqValues,sizeof(int) * numEquates);
    }
  equates[numEquates-1] = (char*)malloc(strlen(name) + 1);
//  addWord(name);
  strcpy(equates[numEquates-1],name);
  eqValues[numEquates-1] = value;
  }

