#include "header.h"

int getValue(char* wrd) {
  int i;
  if (*wrd >= '0' && *wrd <= '9') return atoi(wrd);
  for (i=0; i<numEquates; i++)
    if (strcasecmp(wrd, equates[i]) == 0) return eqValues[i];
  printf("Name not found: %s\n",wrd);
  return -1;
  }

