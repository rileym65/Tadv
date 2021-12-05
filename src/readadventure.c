#include "header.h"

void readAdventure(FILE* inFile) {
  int     i;
  char buffer[1024];
  char* pBuffer;
  char head[256];
  char *tail;
  char flag;
  char eq[255];
  int  val;
  ACTION* action;
  flag = ' ';
  while (flag == ' ') {
    if (fileRead(buffer,inFile) == NULL) flag = '*';
    if (strchr(buffer,'}') != NULL) flag='*';
    if (flag != '*') {
      pBuffer = trim(buffer);
      sscanf(buffer,"%s",head);
      pBuffer = nextWord(pBuffer);
      if (strcmp(head,"title") == 0) {
        printf("Adventure: %s\n",pBuffer);
        }
      if (strcmp(head,"author") == 0) {
        printf("Written by: %s\n",pBuffer);
        }
      if (strcmp(head,"intro") == 0) {
        printf("%s\n",pBuffer);
        }
      if (strcmp(head,"start") == 0)
         startSteps = readActionSteps(inFile,&numStartSteps,pBuffer);
      if (strcmp(head,"action") == 0) {
         action = (ACTION*)malloc(sizeof(ACTION));
         if (++numTurnActions == 1)
           turnActions = (ACTION**)malloc(sizeof(ACTION*));
         else 
           turnActions = (ACTION**)realloc(turnActions,
           sizeof(ACTION*) * numTurnActions);
         turnActions[numTurnActions-1] = action;
         action->numPhraseTokens = 0;
         action->phraseTokens = NULL;
         action->numActionTokens = 0;
         action->actionTokens =
           readActionSteps(inFile,&(action->numActionTokens),pBuffer);
        }
      if (strcmp(head,"flag") == 0) {
        addFlag(pBuffer);
        }
      if (strcmp(head,"var") == 0) {
        if (++numVarNames == 1) {
          varNames = (char**)malloc(sizeof(char*));
          vars = (int*)malloc(sizeof(int));
          }
        else {
          varNames = (char**)realloc(varNames,sizeof(char*) * numVarNames);
          vars = (int*)realloc(vars,sizeof(int) * numVarNames);
          }
        i = 0;
        if (strchr(pBuffer, '=') != NULL) {
          tail = strchr(pBuffer, '=');
          *tail = 0;
          tail++;
          tail = trim(tail);
          i = atoi(tail);
          pBuffer = trim(pBuffer);
          }
        varNames[numVarNames-1] = (char*)malloc(strlen(pBuffer) + 1);
        strcpy(varNames[numVarNames-1],pBuffer);
        vars[numVarNames-1] = i;
        }
      if (strcmp(head,"svar") == 0) {
        if (++numSVars == 1) {
          sVarNames = (char**)malloc(sizeof(char*));
          sVarValues = (char**)malloc(sizeof(char*));
          }
        else {
          sVarNames = (char**)realloc(sVarNames,sizeof(char*) * numSVars);
          sVarValues = (char**)realloc(sVarValues,sizeof(char*) * numSVars);
          }

        tail = NULL;
        if (strchr(pBuffer, '=') != NULL) {
          tail = strchr(pBuffer, '=');
          *tail = 0;
          tail++;
          tail = trim(tail);
          pBuffer = trim(pBuffer);
          }

        sVarNames[numSVars-1] = (char*)malloc(strlen(pBuffer) + 1);
        strcpy(sVarNames[numSVars-1],pBuffer);
        sVarValues[numSVars-1] = (char*)malloc(256);
        if (tail != NULL)
          strcpy(sVarValues[numSVars-1],tail);
        else 
          strcpy(sVarValues[numSVars-1],"Not Initialized");
        }
      if (strcmp(head,"equate") == 0) {
        if (++numEquates == 1) {
          equates = (char**)malloc(sizeof(char*));
          eqValues = (int*)malloc(sizeof(int));
          }
        else {
          equates = (char**)realloc(equates,sizeof(char*) * numEquates);
          eqValues = (int*)realloc(eqValues,sizeof(int) * numEquates);
          }
        sscanf(pBuffer,"%s %d",eq,&val);
        equates[numEquates-1] = (char*)malloc(strlen(eq) + 1);
        addWord(eq);
        strcpy(equates[numEquates-1],eq);
        eqValues[numEquates-1] = val;
        }
      }
    }
  }
