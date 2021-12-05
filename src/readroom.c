#include "header.h"

void readRoom(FILE* inFile,char* buf) {
  int i;
  ROOM* room;
  ROOM* next;
  ACTION* action;
  int number;
  char buffer[1024];
  char buf2[1024];
  char* pBuffer;
  char head[255];
  char flag;
  while (*buf != 0 && *buf != ' ') buf++;
  while (*buf != 0 && *buf == ' ') buf++;
  if (*buf == '{') number = numRooms;
    else number = atoi(buf);
  if (debug) printf("Reading room: %d (%d)\n",numRooms, number);
  if (number != numRooms) {
    printf("Room number mismatch: %d, %d\n",numRooms,number);
    exit(1);
    }
  numRooms++;
  room = (ROOM*)malloc(sizeof(ROOM));
  room->name = NULL;
  room->items = NULL;
  room->numItems = 0;
  room->north[0] = -1;
  room->south[0] = -1;
  room->east[0] = -1;
  room->west[0] = -1;
  room->up[0]   = -1;
  room->down[0] = -1;
  room->ne[0] = -1;
  room->nw[0] = -1;
  room->se[0] = -1;
  room->sw[0] = -1;
  room->north[1] = -1;
  room->south[1] = -1;
  room->east[1] = -1;
  room->west[1] = -1;
  room->up[1]   = -1;
  room->down[1] = -1;
  room->ne[1] = -1;
  room->nw[1] = -1;
  room->se[1] = -1;
  room->sw[1] = -1;
  room->visited = 0;
  room->actions = NULL;
  room->numActions = 0;
  room->description = NULL;
  room->numDesc = 0;
  room->enterSteps = NULL;
  room->leaveSteps = NULL;
  room->numEnterSteps = 0;
  room->numLeaveSteps = 0;
  room->occupiedSteps = NULL;
  room->turnSteps = NULL;
  room->numOccupiedSteps = 0;
  room->numTurnSteps = 0;
  room->needLight = 0;
  room->numDescSteps = 0;
  room->descSteps = NULL;
  if (rooms == NULL) {
    rooms = (ROOM**)malloc(sizeof(ROOM*));
    rooms[0] = room;
    }
  else {
    rooms = (ROOM**)realloc(rooms,sizeof(ROOM*) * numRooms);
    rooms[numRooms - 1] = room;
    }
  flag = ' ';
  while (flag == ' ') {
    if (fileRead(buffer,inFile) == NULL) flag = '*';
    if (flag != '*') {
      pBuffer = trim(buffer);
      sscanf(buffer,"%s",head);
      pBuffer = nextWord(pBuffer);
      if (strcmp(head,"name") == 0) {
        if (room->name != NULL) free(room->name);
        room->name = (char*)malloc(strlen(pBuffer) + 1);
        strcpy(room->name, pBuffer);
        }
      else if (strcmp(head,"identifier") == 0) {
        if (room->name != NULL) free(room->name);
        room->name = (char*)malloc(strlen(pBuffer) + 1);
        strcpy(room->name, pBuffer);
        }
      else if (strcmp(head,"short") == 0) {
        room->shortDesc = (char*)malloc(strlen(pBuffer) + 1);
        strcpy(room->shortDesc, pBuffer);
        }

      else if (strcmp(head,"desc") == 0) {
        if (pBuffer[0] == '{') {
          room->descSteps =
            readActionSteps(inFile,&(room->numDescSteps),pBuffer);
          } else {
          if (++room->numDesc == 1)
            room->description = (char**)malloc(sizeof(char*));
          else
            room->description = (char**)realloc(room->description,
                  sizeof(char*) * room->numDesc);
          room->description[room->numDesc-1] = (char*)malloc(strlen(pBuffer) + 1);
          strcpy(room->description[room->numDesc-1], pBuffer);
          }
        }

      else if (strcmp(head,"needlight") == 0) room->needLight = 1;
      else if (strcmp(head,"visited") == 0) room->visited = 1;
      else if (strcmp(head,"north") == 0) read_dest(pBuffer,room->north);
      else if (strcmp(head,"south") == 0) read_dest(pBuffer,room->south);
      else if (strcmp(head,"east") == 0) read_dest(pBuffer,room->east);
      else if (strcmp(head,"west") == 0) read_dest(pBuffer,room->west);
      else if (strcmp(head,"up") == 0) read_dest(pBuffer,room->up);
      else if (strcmp(head,"down") == 0) read_dest(pBuffer,room->down);
      else if (strcmp(head,"northeast") == 0) read_dest(pBuffer,room->ne);
      else if (strcmp(head,"northwest") == 0) read_dest(pBuffer,room->nw);
      else if (strcmp(head,"southeast") == 0) read_dest(pBuffer,room->se);
      else if (strcmp(head,"southwest") == 0) read_dest(pBuffer,room->sw);
      else if (strcmp(head,"enter") == 0)
         room->enterSteps =
           readActionSteps(inFile,&(room->numEnterSteps),pBuffer);
      else if (strcmp(head,"leave") == 0)
         room->leaveSteps =
           readActionSteps(inFile,&(room->numLeaveSteps),pBuffer);
      else if (strcmp(head,"occupied") == 0)
         room->occupiedSteps =
           readActionSteps(inFile,&(room->numOccupiedSteps),pBuffer);
      else if (strcmp(head,"turn") == 0)
         room->turnSteps =
           readActionSteps(inFile,&(room->numTurnSteps),pBuffer);
      else if (strcmp(head,"action") == 0) {
         pBuffer = trim(pBuffer);
         strcpy(buf2, pBuffer);
         for (i=0; i<strlen(pBuffer); i++)
           if (pBuffer[i] == '{') pBuffer[i] = 0;
         pBuffer = trim(pBuffer);
         i = tokenizeAdd(pBuffer);
         action = (ACTION*)malloc(sizeof(ACTION));
         if (++room->numActions == 1)
           room->actions = (ACTION**)malloc(sizeof(ACTION*));
         else 
           room->actions = (ACTION**)realloc(room->actions,
           sizeof(ACTION*) * room->numActions);
         room->actions[room->numActions-1] = action;
         action->numPhraseTokens = numTokens;
         action->phraseTokens = (int*)malloc(sizeof(int) * numTokens);
         for (i=0; i<numTokens; i++) action->phraseTokens[i] = tokens[i];
         action->numActionTokens = 0;
         action->actionTokens =
           readActionSteps(inFile,&(action->numActionTokens),buf2);
        }
      else if (strchr(buffer,'}') != NULL) flag='*';
        
      }
    }
  }
