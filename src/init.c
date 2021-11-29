#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void addFlag(char* pBuffer) {
  if (++numFlagNames == 1)
    flagNames = (char**)malloc(sizeof(char*));
  else
    flagNames = (char**)realloc(flagNames,sizeof(char*) * numFlagNames);
  flagNames[numFlagNames-1] = (char*)malloc(strlen(pBuffer) + 1);
  strcpy(flagNames[numFlagNames-1],pBuffer);
  }

int getRoomNumber(char* wrd) {
  int i;
  int j;
  if (wrd[0] >= '0' && wrd[0] <= '9') return atoi(wrd);
  for (i=0; i<numRooms; i++) {
    if (rooms[i]->name != NULL)
      if (strcasecmp(wrd,rooms[i]->name) == 0) return i;
    }
  return -1;
  }

int getItemNumber(char* wrd) {
  int i;
  int j;
  if (wrd[0] >= '0' && wrd[0] <= '9') return atoi(wrd);
  for (i=0; i<numItems; i++)
    if (strcasecmp(wrd,items[i]->name) == 0) return i;
  for (i=0; i<numEquates; i++)
    if (strcasecmp(wrd, equates[i]) == 0) return eqValues[i];
  return -1;
  }

void read_dest(char* buffer,int* link) {
  link[0] = atoi(buffer);
  while (*buffer != 0 && *buffer != ' ') buffer++;
  if (*buffer == 0) {
    link[1] = -1;
    return;
    }
  while (*buffer == ' ') buffer++;
  if (strncmp(buffer,"door",4) == 0) {
    while (*buffer != 0 && *buffer != ' ') buffer++;
    while (*buffer == ' ') buffer++;
    link[1] = atoi(buffer);
    }
  else {
    printf("Error in direction: %s\n",buffer);
    }
  }

int getCode(char* wrd) {
  int i;
  int t;
  if (wrd[0] >= '0' && wrd[0] <= '9') return atoi(wrd);
  if (wrd[0] == '-' && wrd[1] >= '0' && wrd[1] <= '9') return atoi(wrd);
  if (strcasecmp(wrd,"INROOM?") == 0) return CMD_IN_ROOM;
  if (strcasecmp(wrd,"TELEPORT") == 0) return CMD_TELEPORT;
  if (strcasecmp(wrd,"NOTINROOM?") == 0) return CMD_NOT_IN_ROOM;
  if (strcasecmp(wrd,"SAY")    == 0) return CMD_SAY;
  if (strcasecmp(wrd,"ADDSCORE") == 0) return CMD_ADD_SCORE;
  if (strcasecmp(wrd,"SUBSCORE") == 0) return CMD_SUB_SCORE;
  if (strcasecmp(wrd,"TRUE")   == 0) return CMD_TRUE;
  if (strcasecmp(wrd,"FALSE")  == 0) return CMD_FALSE;
  if (strcasecmp(wrd,"ELSE")   == 0) return CMD_ELSE;
  if (strcasecmp(wrd,"DIE")    == 0) return CMD_DIE;
  if (strcasecmp(wrd,"WIN")    == 0) return CMD_WIN;
  if (strcasecmp(wrd,"LOSE")   == 0) return CMD_LOSE;
  if (strcasecmp(wrd,"MORE")   == 0) return CMD_MORE;
  if (strcasecmp(wrd,"CARRYING?") == 0) return CMD_CARRYING;
  if (strcasecmp(wrd,"NOTCARRYING?") == 0) return CMD_NOT_CARRYING;
  if (strcasecmp(wrd,"FLAGSET?")  == 0) return CMD_FLAG_SET;
  if (strcasecmp(wrd,"FLAGRESET?") == 0) return CMD_FLAG_RESET;
  if (strcasecmp(wrd,"SETFLAG")  == 0) return CMD_SET_FLAG;
  if (strcasecmp(wrd,"RESETFLAG") == 0) return CMD_RESET_FLAG;
  if (strcasecmp(wrd,"ITEMINROOM?") == 0) return CMD_OBJECT_IN_ROOM;
  if (strcasecmp(wrd,"ITEMNOTINROOM?") == 0) return CMD_OBJECT_NOT_IN_ROOM;
  if (strcasecmp(wrd,"PLACEITEM") == 0) return CMD_PLACE_OBJECT;
  if (strcasecmp(wrd,"TAKEITEM") == 0) return CMD_TAKE_OBJECT;
  if (strcasecmp(wrd,"DROPITEM") == 0) return CMD_DROP_OBJECT;
  if (strcasecmp(wrd,"IF") == 0) return CMD_IF;
  if (strcasecmp(wrd,"+") == 0) return CMD_ADD;
  if (strcasecmp(wrd,"-") == 0) return CMD_SUB;
  if (strcasecmp(wrd,"*") == 0) return CMD_MUL;
  if (strcasecmp(wrd,"/") == 0) return CMD_DIV;
  if (strcasecmp(wrd,"dup") == 0) return CMD_DUP;
  if (strcasecmp(wrd,"drop") == 0) return CMD_DROP;
  if (strcasecmp(wrd,"swap") == 0) return CMD_SWAP;
  if (strcasecmp(wrd,"set") == 0) return CMD_SET;
  if (strcasecmp(wrd,"get") == 0) return CMD_GET;
  if (strcasecmp(wrd,"!") == 0) return CMD_SET;
  if (strcasecmp(wrd,"@") == 0) return CMD_GET;
  if (strcasecmp(wrd,"=") == 0) return CMD_EQ;
  if (strcasecmp(wrd,"<>") == 0) return CMD_NE;
  if (strcasecmp(wrd,">") == 0) return CMD_GT;
  if (strcasecmp(wrd,"<") == 0) return CMD_LT;
  if (strcasecmp(wrd,">=") == 0) return CMD_GE;
  if (strcasecmp(wrd,"<=") == 0) return CMD_LE;
  if (strcasecmp(wrd,"random") == 0) return CMD_RANDOM;
  if (strcasecmp(wrd,".") == 0) return CMD_DOT;
  if (strcasecmp(wrd,"cr") == 0) return CMD_CR;
  if (strcasecmp(wrd,"nsay") == 0) return CMD_NSAY;
  if (strcasecmp(wrd,"enteredfrom?") == 0) return CMD_ENTERED;
  if (strcasecmp(wrd,"goingwest?") == 0) return CMD_GOING_WEST;
  if (strcasecmp(wrd,"goingeast?") == 0) return CMD_GOING_EAST;
  if (strcasecmp(wrd,"goingnorth?") == 0) return CMD_GOING_NORTH;
  if (strcasecmp(wrd,"goingsouth?") == 0) return CMD_GOING_SOUTH;
  if (strcasecmp(wrd,"goingup?") == 0) return CMD_GOING_UP;
  if (strcasecmp(wrd,"goingdown?") == 0) return CMD_GOING_DOWN;
  if (strcasecmp(wrd,"currentroom") == 0) return CMD_CURRENT_ROOM;
  if (strcasecmp(wrd,"removeitem") == 0) return CMD_REMOVE_ITEM;
  if (strcasecmp(wrd,"then") == 0) return CMD_THEN;
  if (strcasecmp(wrd,"over") == 0) return CMD_OVER;
  if (strcasecmp(wrd,"rot") == 0) return CMD_ROT;
  if (strcasecmp(wrd,"-rot") == 0) return CMD_MROT;
  if (strcasecmp(wrd,"and") == 0) return CMD_AND;
  if (strcasecmp(wrd,"or") == 0) return CMD_OR;
  if (strcasecmp(wrd,"xor") == 0) return CMD_XOR;
  if (strcasecmp(wrd,"pick") == 0) return CMD_PICK;
  if (strcasecmp(wrd,"do") == 0) return CMD_DO;
  if (strcasecmp(wrd,"i") == 0) return CMD_I;
  if (strcasecmp(wrd,"roomdesc") == 0) return CMD_ROOM_DESC;
  if (strcasecmp(wrd,"loop") == 0) return CMD_LOOP;
  if (strcasecmp(wrd,"spaces") == 0) return CMD_SPACES;
  if (strcasecmp(wrd,"location") ==0 ) return CMD_LOCATION;
  if (strcasecmp(wrd,"extractitem") == 0) return CMD_EXTRACT;
  if (strcasecmp(wrd,"score") == 0) return CMD_SCORE;
  if (strcasecmp(wrd,"weight") == 0) return CMD_WEIGHT;
  if (strcasecmp(wrd,"geteast") == 0) return CMD_GET_EAST;
  if (strcasecmp(wrd,"getwest") == 0) return CMD_GET_WEST;
  if (strcasecmp(wrd,"getnorth") == 0) return CMD_GET_NORTH;
  if (strcasecmp(wrd,"getsouth") == 0) return CMD_GET_SOUTH;
  if (strcasecmp(wrd,"getup") == 0) return CMD_GET_UP;
  if (strcasecmp(wrd,"getdown") == 0) return CMD_GET_DOWN;
  if (strcasecmp(wrd,"emit") == 0) return CMD_EMIT;
  if (strcasecmp(wrd,"not") == 0) return CMD_NOT;
  if (strcasecmp(wrd,"light") == 0) return CMD_LIGHT;
  if (strcasecmp(wrd,"light?") == 0) return CMD_HAS_LIGHT;
  if (strcasecmp(wrd,"open") == 0) return CMD_OPEN;
  if (strcasecmp(wrd,"close") == 0) return CMD_CLOSE;
  if (strcasecmp(wrd,"opened?") == 0) return CMD_OPENED;
  if (strcasecmp(wrd,"lock") == 0) return CMD_LOCK;
  if (strcasecmp(wrd,"unlock") == 0) return CMD_UNLOCK;
  if (strcasecmp(wrd,"unlock?") == 0) return CMD_UNLOCKED;
  if (strcasecmp(wrd,"turncount") == 0) return CMD_TURNCOUNT;
  if (strcasecmp(wrd,"examineitem") == 0) return CMD_EXAMINEITEM;
  if (strcasecmp(wrd,"opendoor") == 0) return CMD_OPEN_DOOR;
  if (strcasecmp(wrd,"closedoor") == 0) return CMD_CLOSE_DOOR;
  if (strcasecmp(wrd,"lockdoor") == 0) return CMD_LOCK_DOOR;
  if (strcasecmp(wrd,"unlockdoor") == 0) return CMD_UNLOCK_DOOR;
  if (strcasecmp(wrd,"doorlocked?") == 0) return CMD_DOOR_LOCKED;
  if (strcasecmp(wrd,"doorclosed?") == 0) return CMD_DOOR_CLOSED;
  if (strcasecmp(wrd,"invcount") == 0) return CMD_INV_COUNT;
  for (i=0; i<numItems; i++)
    if (strcasecmp(wrd,items[i]->name) == 0) return i;
  for (i=0; i<numRooms; i++)
    if (strcasecmp(wrd,rooms[i]->name) == 0) return i;
  for (i=0; i<numFlagNames; i++)
    if (strcasecmp(wrd,flagNames[i]) == 0) return i;  
  for (i=0; i<numVarNames; i++)
    if (strcasecmp(wrd,varNames[i]) == 0) return i;  
  t = -1;
  for (i=0; i<numVocab; i++)
    if (strcasecmp(wrd,vocab[i]) == 0) t = i;
  for (i=0; i<numFunctions; i++) {
    if (t == functions[i]->phraseTokens[0]) return i+40000;  
    }
  for (i=0; i<numEquates; i++)
    if (strcasecmp(wrd,equates[i]) == 0) return eqValues[i];  
  return CMD_ERROR;
  }

int* readActionSteps(FILE* inFile,int* count, char* pBuf) {
  int*    steps;
  char    flag;
  char*   pWrd;
  char    wrd[255];
  char    buf2[1024];
  char    arg;
  int     token;
  int i;
  int j;
  *count = 0;
  flag = ' ';
  pBuf = upper(pBuf);
  while (*pBuf != 0 && *pBuf != '{') pBuf++;
  if (*pBuf == '{') pBuf++;
  while (flag == ' ') {
    if (*pBuf == 0) {
      fileRead(buf2,inFile);
      pBuf = upper(buf2);
      }
    while (*pBuf > 0 && *pBuf <= ' ') pBuf++;
    if (*pBuf == 0) {
      fileRead(buf2,inFile);
      pBuf = upper(buf2);
      while (*pBuf > 0 && *pBuf <= ' ') pBuf++;
      }
    pWrd = wrd;
    if (*pBuf == '}') flag = '*';
      else {
      while (*pBuf > ' ' && *pBuf <='z') *pWrd++ = *pBuf++;
      *pWrd = 0;
      token = getCode(wrd);
      if (token == CMD_ERROR) {
        printf("Syntax error in file: %s\n",buf2);
        exit(1);
        }
      if ((*count += 1) == 1)
        steps = (int*)malloc(sizeof(int));
      else
        steps = (int*)realloc(steps,sizeof(int) * *count);
      steps[*count - 1] = token;
      }
    }
  return steps;
  }

void addWord(char* wrd) {
  int i;
  for (i=0; i<numVocab; i++)
    if (strcasecmp(wrd,vocab[i]) == 0) return;
  numVocab++;
  if (numVocab == 1) vocab = (char**)malloc(sizeof(char*));
    else vocab = (char**)realloc(vocab,sizeof(char*) * numVocab);
  vocab[numVocab-1] = (char*)malloc(strlen(wrd) + 1);
  strcpy(vocab[numVocab-1], wrd);
  }

void init() {
  int i;
  for (i=0; i<1024; i++) flags[i] = 0;
  flagNames = NULL;
  actions  = NULL;
  vocab    = NULL;
  items    = NULL;
  rooms    = NULL;
  messages = NULL;
  varNames = NULL;
  vars     = NULL;
  turnActions = NULL;
  equates     = NULL;
  eqValues    = NULL;
  startSteps  = NULL;
  numStartSteps  = 0;
  numEquates     = 0;
  numTurnActions = 0;
  numVarNames  = 0;
  numFlagNames = 0;
  numActions  = 0;
  numVocab    = 0;
  numItems    = 0;
  numRooms    = 0;
  numMessages = 0;
  player.score = 0;
  player.light = 0;
  player.turnCount = 0;
  addWord("look");          /*  0 */
  addWord("north");         /*  1 */
  addWord("n");             /*  2 */
  addWord("south");         /*  3 */
  addWord("s");             /*  4 */
  addWord("east");          /*  5 */
  addWord("e");             /*  6 */
  addWord("west");          /*  7 */
  addWord("w");             /*  8 */
  addWord("go");            /*  9 */
  addWord("up");            /* 10 */
  addWord("down");          /* 11 */
  addWord("invent");        /* 12 */
  addWord("score");         /* 13 */
  addWord("save");          /* 14 */
  addWord("diagnose");      /* 15 */
  addWord("quit");          /* 16 */
  addWord("get");           /* 17 */
  addWord("take");          /* 18 */
  addWord("put");           /* 19 */
  addWord("drop");          /* 20 */
  addWord("all");           /* 21 */
  addWord("vocab");         /* 22 */
  addWord("examine");       /* 23 */
  addWord("load");          /* 24 */
  addWord("ne");            /* 25 */
  addWord("nw");            /* 26 */
  addWord("se");            /* 27 */
  addWord("sw");            /* 28 */
  addWord("weight");        /* 29 */
  addWord("open");          /* 30 */
  addWord("close");         /* 31 */
  addWord("lock");          /* 32 */
  addWord("unlock");        /* 33 */
  addWord("door");          /* 34 */
  addWord("with");          /* 35 */
  addFlag("F_HAS_LIGHT");
  addFlag("F_CAN_MOVE");
  }

void reset() {
  int i;
  int loc;
  player.items = NULL;
  player.numItems = 0;
  player.location = 0;
  player.lastLocation = -1;
  player.score = 0;
  for (i=0; i<numRooms; i++) {
    if (rooms[i]->items != NULL) free(rooms[i]->items);
    rooms[i]->items = NULL;
    rooms[i]->numItems = 0;
    }
  for (i=0; i<numItems; i++) {
    if (items[i]->location >= 0) {
      loc = items[i]->location;
      rooms[loc]->numItems++;
      if (rooms[loc]->numItems == 1)
        rooms[loc]->items = (ITEM**)malloc(sizeof(ITEM*));
      else
        rooms[loc]->items = (ITEM**)realloc(rooms[loc]->items,
          sizeof(ITEM*) * rooms[loc]->numItems);
      rooms[loc]->items[rooms[loc]->numItems - 1] = items[i];
      }
    }
  }

void readMessage(FILE* inFile,char* buf) {
  int number;
  char     flag;
  char*    pBuffer;
  MESSAGE* message;
  char buffer[1024];
  char msg[1024];
  int  pos;
  sscanf(buf,"%s %d",buffer,&number);
  if (number != numMessages) {
    printf("Message number mismatch: %d, %s\n",numMessages,buf);
    exit(1);
    }
  numMessages++;
  message = (MESSAGE*)malloc(sizeof(MESSAGE));
  message->numLines = 0;
  if (messages == NULL) {
    messages = (MESSAGE**)malloc(sizeof(MESSAGE*));
    messages[0] = message;
    }
  else {
    messages = (MESSAGE**)realloc(messages,sizeof(MESSAGE*) * numMessages);
    messages[numMessages - 1] = message;
    }
  while (*buf != 0 && *buf != '{') buf++;
  buf++;
  while (*buf > 0 && *buf <= ' ') buf++;
  flag = ' ';
  pos = 0;
  while (flag == ' ') {
    if (*buf == 0) {
      if (fileRead(buffer,inFile) == NULL) flag = '*';
      buf = buffer;
      pos = 0;
      while (*buf > 0 && *buf <= ' ') buf++;
      }
    while (*buf != 0 && *buf != '}') msg[pos++] = *buf++;
    msg[pos] = 0;
    if (++message->numLines == 1)
      message->message = (char**)malloc(sizeof(char*));
    else
      message->message = (char**)realloc(message->message,
        sizeof(char*) * message->numLines);
    message->message[message->numLines-1]=(char*)malloc(strlen(msg)+1);
      strcpy(message->message[message->numLines-1],msg);
    if (*buf == '}') flag = '*';
    }

  }

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
  sscanf(buf,"%s %d",buffer,&number);
  if (number != numRooms) {
    printf("Room number mismatch: %d, %s\n",numRooms,buf);
    exit(1);
    }
  numRooms++;
  room = (ROOM*)malloc(sizeof(ROOM));
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


void readItem(FILE* inFile,char* buf) {
  int     i;
  ITEM* item;
  ACTION* action;
  int number;
  char buffer[1024];
  char* pBuffer;
  char head[255];
  char flag;
  sscanf(buf,"%s %d",buffer,&number);
  if (number != numItems) {
    printf("Item number mismatch: %d, %s\n",numItems,buf);
    exit(1);
    }
  numItems++;
  item = (ITEM*)malloc(sizeof(ITEM));
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
  item->examine = NULL;
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
    if (strchr(buffer,'}') != NULL) flag='*';
    if (flag != '*') {
      pBuffer = trim(buffer);
      sscanf(buffer,"%s",head);
      pBuffer = nextWord(pBuffer);
      if (strcmp(head,"name") == 0) {
        item->name = (char*)malloc(strlen(pBuffer) + 1);
        strcpy(item->name, pBuffer);
        addWord(item->name);
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


void readDoor(FILE* inFile,char* buf) {
  int     i;
  DOOR* door;
  ACTION* action;
  int number;
  char buffer[1024];
  char* pBuffer;
  char head[255];
  char flag;
  sscanf(buf,"%s %d",buffer,&number);
  if (number != numDoors) {
    printf("Door number mismatch: %d, %s\n",numDoors,buf);
    exit(1);
    }
  numDoors++;
  door = (DOOR*)malloc(sizeof(DOOR));
  door->opened = 0;
  door->unlocked = 1;
  door->lockable = 0;
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
    if (strchr(buffer,'}') != NULL) flag='*';
    if (flag != '*') {
      pBuffer = trim(buffer);
      sscanf(buffer,"%s",head);
      pBuffer = nextWord(pBuffer);
      if (strcmp(head,"name") == 0) {
        door->name = (char*)malloc(strlen(pBuffer) + 1);
        strcpy(door->name, pBuffer);
        addWord(door->name);
        }
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

void readAction(FILE* inFile,char* buffer) {
  ACTION* action;
  char    flag;
  char*   pWrd;
  char*   pBuf;
  char    wrd[255];
  char    buf2[1024];
  char    arg;
  int     token;
  int i;
  int j;
  buffer += 6;
  buffer = trim(buffer);
  strcpy(buf2, buffer);
  for (i=0; i<strlen(buffer); i++)
    if (buffer[i] == '{') buffer[i] = 0;
  buffer = trim(buffer);
  i = tokenizeAdd(buffer);
  action = (ACTION*)malloc(sizeof(ACTION));
  if (++numActions == 1) actions = (ACTION**)malloc(sizeof(ACTION*));
    else actions = (ACTION**)realloc(actions,sizeof(ACTION*) * numActions);
  actions[numActions-1] = action;
  action->numPhraseTokens = numTokens;
  action->phraseTokens = (int*)malloc(sizeof(int) * numTokens);
  for (i=0; i<numTokens; i++) action->phraseTokens[i] = tokens[i];
  action->numActionTokens = 0;
  action->actionTokens = readActionSteps(inFile,&(action->numActionTokens),buf2);
  }

void readFunction(FILE* inFile,char* buffer) {
  ACTION* action;
  char    flag;
  char*   pWrd;
  char*   pBuf;
  char    wrd[255];
  char    buf2[1024];
  char    arg;
  int     token;
  int i;
  int j;
  buffer += 8;
  buffer = trim(buffer);
  for (i=0; i<strlen(buffer); i++)
    if (buffer[i] == '{') buffer[i] = 0;
  buffer = trim(buffer);
  i = tokenizeAdd(buffer);
  action = (ACTION*)malloc(sizeof(ACTION));
  if (++numFunctions == 1) functions = (ACTION**)malloc(sizeof(ACTION*));
    else functions = (ACTION**)realloc(functions,sizeof(ACTION*)*numFunctions);
  functions[numFunctions-1] = action;
  action->numPhraseTokens = numTokens;
  action->phraseTokens = (int*)malloc(sizeof(int) * numTokens);
  for (i=0; i<numTokens; i++) action->phraseTokens[i] = tokens[i];
  action->numActionTokens = 0;
  action->actionTokens = readActionSteps(inFile,&(action->numActionTokens),buffer);
  }

void readAdventure(FILE* inFile) {
  int     i;
  char buffer[1024];
  char* pBuffer;
  char head[255];
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
        varNames[numVarNames-1] = (char*)malloc(strlen(pBuffer) + 1);
        strcpy(varNames[numVarNames-1],pBuffer);
        vars[numVarNames-1] = 0;
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


int readFile(char* filename) {
  FILE* inFile;
  char buffer[1024];
  if ((inFile = fopen(filename,"r")) == NULL) {
    printf("Could not open file\n");
    return -1;
    }
  fgets(buffer,1024,inFile);
  while (strlen(buffer) > 0 && buffer[strlen(buffer)-1] <= ' ')
    buffer[strlen(buffer)-1] = 0;
  encrypted = 'N';
  if (strncmp(buffer,"tadv",4) != 0) {
    printf("Invalid file\n");
    fclose(inFile);
    exit(1);
    }
  if (strstr(buffer,"ENC") != NULL) {
    encrypted = 'Y';
    key=rc4_init("tadvencrypt",11);
    }
  while (fileRead(buffer,inFile) != NULL) {
    while (strlen(buffer) > 0 && buffer[strlen(buffer)-1] <= ' ')
      buffer[strlen(buffer)-1] = 0;
    if (strncmp(buffer,"room",4)         == 0) readRoom(inFile,buffer);
    else if (strncmp(buffer,"message",7) == 0) readMessage(inFile,buffer);
    else if (strncmp(buffer,"item",4)    == 0) readItem(inFile,buffer);
    else if (strncmp(buffer,"action",6)  == 0) readAction(inFile,buffer);
    else if (strncmp(buffer,"adventure",9) == 0) readAdventure(inFile);
    else if (strncmp(buffer,"function",8) == 0) readFunction(inFile,buffer);
    else if (strncmp(buffer,"door",4) == 0) readDoor(inFile,buffer);
    else if (strlen(buffer) == 0) ;
    else printf("Unknown line: %s\n",buffer);
    }
  return 0;
  }
