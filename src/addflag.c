#include "header.h"

void addFlag(char* pBuffer) {
  char *value;
  if (debug) printf("Adding flag: %s\n",pBuffer); fflush(stdout);
  value = NULL;
  if (strchr(pBuffer, '=') != NULL) {
    value = strchr(pBuffer, '=');
    *value = 0;
    value++;
    value = trim(value);
    pBuffer = trim(pBuffer);
    }
  if (++numFlagNames == 1)
    flagNames = (char**)malloc(sizeof(char*));
  else
    flagNames = (char**)realloc(flagNames,sizeof(char*) * numFlagNames);
  flagNames[numFlagNames-1] = (char*)malloc(strlen(pBuffer) + 1);
  strcpy(flagNames[numFlagNames-1],pBuffer);
  flags[numFlagNames-1] = 0;
  if (value != NULL) {
    if (strcasecmp(value,"true") == 0) flags[numFlagNames-1] = 1;
    }
  }

