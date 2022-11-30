#include "header.h"

void readDoor(FILE* inFile,char* buf) {
  int     i;
  DOOR* door;
  ACTION* action;
  int number;
  char buffer[1024];
  char* pBuffer;
  char head[255];
  char flag;
  while (*buf != 0 && *buf != ' ') buf++;
  while (*buf != 0 && *buf == ' ') buf++;
  if (*buf == '{') number = numDoors;
    else number = atoi(buf);
  if (debug) printf("Reading door: %d (%d)\n",numDoors, number);
  if (number != numDoors) {
    printf("Door number mismatch: %d, %d\n",numDoors,number);
    exit(1);
    }
  numDoors++;
  door = (DOOR*)malloc(sizeof(DOOR));
  door->name = NULL;
  door->opened = 0;
  door->unlocked = 1;
  door->lockable = 0;
  door->numDescSteps = 0;
  door->numOnOpenSteps = 0;
  door->numOnCloseSteps = 0;
  door->numOnLockSteps = 0;
  door->numOnUnlockSteps = 0;
  if (doors == NULL) {
    doors = (DOOR**)malloc(sizeof(DOOR*));
    doors[0] = door;
    }
  else {
    doors = (DOOR**)realloc(doors,sizeof(DOOR*) * numDoors);
    doors[numDoors - 1] = door;
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
        if (door->name != NULL) free(door->name);
        door->name = (char*)malloc(strlen(pBuffer) + 1);
        strcpy(door->name, pBuffer);
//        addWord(door->name);
        }
      else if (strcmp(head,"identifier") == 0) {
        if (door->name != NULL) free(door->name);
        door->name = (char*)malloc(strlen(pBuffer) + 1);
        strcpy(door->name, pBuffer);
//        addWord(door->name);
        }
      if (strcasecmp(head,"onopen") == 0)
        door->onOpenSteps =
          readActionSteps(inFile,&(door->numOnOpenSteps),pBuffer);
      if (strcasecmp(head,"onclose") == 0)
        door->onCloseSteps =
          readActionSteps(inFile,&(door->numOnCloseSteps),pBuffer);
      if (strcasecmp(head,"onlock") == 0)
        door->onLockSteps =
          readActionSteps(inFile,&(door->numOnLockSteps),pBuffer);
      if (strcasecmp(head,"onunlock") == 0)
        door->onUnlockSteps =
          readActionSteps(inFile,&(door->numOnUnlockSteps),pBuffer);
      if (strcmp(head,"desc") == 0) {
        if (pBuffer[0] == '{') {
          door->descSteps =
            readActionSteps(inFile,&(door->numDescSteps),pBuffer);
          door->description = "null";
          } else {
          door->description = (char*)malloc(strlen(pBuffer) + 1);
          strcpy(door->description, pBuffer);
          }
        }
      if (strcmp(head,"opened") == 0) door->opened = 1;
      if (strcmp(head,"closed") == 0) door->opened = 0;
      if (strcmp(head,"locked") == 0) door->unlocked = 0;
      if (strcmp(head,"unlocked") == 0) door->unlocked = 1;
      if (strcmp(head,"lockable") == 0) door->lockable = 1;
      if (strcmp(head,"key") == 0) door->key = getItemNumber(pBuffer);
      }
    }
  }
