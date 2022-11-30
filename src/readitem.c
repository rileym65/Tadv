#include "header.h"

void readItem(FILE* inFile,char* buf) {
  int     i;
  ITEM* item;
  ACTION* action;
  int number;
  char buffer[1024];
  char* pBuffer;
  char head[255];
  char flag;
  while (*buf != 0 && *buf != ' ') buf++;
  while (*buf != 0 && *buf == ' ') buf++;
  if (*buf == '{') number = numItems;
    else number = atoi(buf);
  if (debug) printf("Reading item: %d (%d)\n",numItems, number);
  if (number != numItems) {
    printf("Item number mismatch: %d, %d\n",numItems,number);
    exit(1);
    }
  numItems++;
  item = (ITEM*)malloc(sizeof(ITEM));
  item->name = NULL;
  item->identifier = NULL;
  item->number = numItems-1;
  item->location = -1;
  item->weight = 0;
  item->score = 0;
  item->actions = NULL;
  item->numActions = 0;
  item->examSteps = NULL;
  item->numExamSteps = 0;
  item->descSteps = NULL;
  item->numDescSteps = 0;
  item->carryingSteps = NULL;
  item->numCarryingSteps = 0;
  item->turnSteps = NULL;
  item->numTurnSteps = 0;
  item->wornSteps = NULL;
  item->numWornSteps = 0;
  item->removedSteps = NULL;
  item->numRemovedSteps = 0;
  item->wearingSteps = NULL;
  item->numWearingSteps = 0;
  item->examine = NULL;
  item->wearable = 0;
  item->beingworn = 0;
  item->startingItem = 0;
  item->cursed = 0;
  item->container = 0;
  item->maxContents = 0;
  item->numContents = 0;
  item->acquiredSteps = NULL;
  item->numAcquiredSteps = 0;
  if (items == NULL) {
    items = (ITEM**)malloc(sizeof(ITEM*));
    items[0] = item;
    }
  else {
    items = (ITEM**)realloc(items,sizeof(ITEM*) * numItems);
    items[numItems - 1] = item;
    }
  flag = ' ';
  while (flag == ' ') {
    if (fileRead(buffer,inFile) == NULL) flag = '*';
    pBuffer = trim(buffer);
    if (*pBuffer == '}') flag='*';
    if (flag != '*') {
      sscanf(buffer,"%s",head);
      pBuffer = nextWord(pBuffer);
      if (strcmp(head,"name") == 0) {
        if (item->name != NULL) free(item->name);
        item->name = (char*)malloc(strlen(pBuffer) + 1);
        strcpy(item->name, pBuffer);
        if (item->identifier == NULL) {
          item->identifier = (char*)malloc(strlen(pBuffer) + 1);
          strcpy(item->identifier, pBuffer);
          }
//        addWord(item->name);
        }
      if (strcmp(head,"identifier") == 0) {
        if (item->identifier != NULL) free(item->identifier);
        item->identifier = (char*)malloc(strlen(pBuffer) + 1);
        strcpy(item->identifier, pBuffer);
//        addWord(item->name);
        }
      if (strcmp(head,"desc") == 0) {
        if (pBuffer[0] == '{') {
          item->descSteps =
            readActionSteps(inFile,&(item->numDescSteps),pBuffer);
          item->description = "null";
          } else {
          item->description = (char*)malloc(strlen(pBuffer) + 1);
          strcpy(item->description, pBuffer);
          }
        }
      if (strcmp(head,"examine") == 0) {
        if (pBuffer[0] == '{') {
          item->examSteps =
            readActionSteps(inFile,&(item->numExamSteps),pBuffer);
          item->examine = "null";
          } else {
          if (item->examine ==NULL) {
            item->examine = (char*)malloc(strlen(pBuffer) + 1);
            strcpy(item->examine, pBuffer); }
          else {
            item->examine = (char*)realloc(item->examine,strlen(pBuffer) + 2 + 
               strlen(item->examine));
            strcat(item->examine,"\n");
            strcat(item->examine, pBuffer);
            }
          }
        }
      if (strcmp(head,"noncarryable") == 0) item->weight = -1;
      if (strcmp(head,"wearable") == 0) item->wearable = 1;
      if (strcmp(head,"beingworn") == 0) item->beingworn = 1;
      if (strcmp(head,"startingitem") == 0) item->startingItem = 1;
      if (strcmp(head,"cursed") == 0) item->cursed = 1;
      if (strcmp(head,"container") == 0) {
        item->container = 1;
        if (item->maxContents == 0) item->maxContents = 255;
        }
      if (strcmp(head,"maxcontents") == 0) item->maxContents = atoi(pBuffer);
      if (strcmp(head,"weight") == 0 && item->weight == 0)
        item->weight = atoi(pBuffer);
      if (strcmp(head,"location") == 0) item->location = getRoomNumber(pBuffer);
      if (strcmp(head,"score") == 0) item->score = atoi(pBuffer);
      if (strcmp(head,"carrying") == 0)
         item->carryingSteps =
           readActionSteps(inFile,&(item->numCarryingSteps),pBuffer);
      if (strcmp(head,"turn") == 0)
         item->turnSteps =
           readActionSteps(inFile,&(item->numTurnSteps),pBuffer);
      if (strcmp(head,"acquired") == 0)
         item->acquiredSteps =
           readActionSteps(inFile,&(item->numAcquiredSteps),pBuffer);
      if (strcmp(head,"lost") == 0)
         item->lostSteps =
           readActionSteps(inFile,&(item->numLostSteps),pBuffer);
      if (strcmp(head,"worn") == 0)
         item->wornSteps =
           readActionSteps(inFile,&(item->numWornSteps),pBuffer);
      if (strcmp(head,"wearing") == 0)
         item->wearingSteps =
           readActionSteps(inFile,&(item->numWearingSteps),pBuffer);
      if (strcmp(head,"removed") == 0)
         item->removedSteps =
           readActionSteps(inFile,&(item->numRemovedSteps),pBuffer);
      if (strcmp(head,"action") == 0) {
         pBuffer = trim(pBuffer);
         for (i=0; i<strlen(pBuffer); i++)
           if (pBuffer[i] == '{') pBuffer[i] = 0;
         pBuffer = trim(pBuffer);
         i = tokenizeAdd(pBuffer);
         action = (ACTION*)malloc(sizeof(ACTION));
         if (++item->numActions == 1)
           item->actions = (ACTION**)malloc(sizeof(ACTION*));
         else 
           item->actions = (ACTION**)realloc(item->actions,
           sizeof(ACTION*) * item->numActions);
         item->actions[item->numActions-1] = action;
         action->numPhraseTokens = numTokens;
         action->phraseTokens = (int*)malloc(sizeof(int) * numTokens);
         for (i=0; i<numTokens; i++) action->phraseTokens[i] = tokens[i];
         action->numActionTokens = 0;
         action->actionTokens =
           readActionSteps(inFile,&(action->numActionTokens),pBuffer);
        }
      }
    }
  }
