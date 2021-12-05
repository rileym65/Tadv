#include "header.h"

int getItemNumber(char* wrd) {
  int i;
  int j;
  if (wrd[0] >= '0' && wrd[0] <= '9') return atoi(wrd);
  for (i=0; i<numItems; i++)
    if (strcasecmp(wrd,items[i]->name) == 0) return i;
  for (i=0; i<numEquates; i++)
    if (strcasecmp(wrd, equates[i]) == 0) return eqValues[i];
  printf("Name not found: %s\n",wrd);
  return -1;
  }

