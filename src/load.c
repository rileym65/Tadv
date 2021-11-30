#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

ACTION* loadAction(FILE* file) {
  int j;
  char buffer[256];
  ACTION* action;
  action = (ACTION*)malloc(sizeof(ACTION));
    fscanf(file,"%d\n",&(action->numPhraseTokens));
    action->phraseTokens = (int*)malloc(sizeof(int) * action->numPhraseTokens);
    for (j=0; j<action->numPhraseTokens; j++) {
      fscanf(file,"%d\n",&(action->phraseTokens[j]));
      }
    fscanf(file,"%d\n",&(action->numActionTokens));
    action->actionTokens = (int*)malloc(sizeof(int) * action->numActionTokens);
    for (j=0; j<action->numActionTokens; j++) {
      fscanf(file,"%d\n",&(action->actionTokens[j]));
      }
  return action;  
  }

int load(char* filename) {
  int i;
  int j;
  int count;
  char buffer[256];
  FILE* file;
  MESSAGE* msg;
  ACTION*  action;
  ROOM*    room;
  DOOR*    door;
  file = fopen(filename,"r");
  if (file == NULL) return 0;

/* ************************************ */
/* ********* Load vocabulary ********** */
/* ************************************ */
  fscanf(file,"%d\n",&j);
  for (i=25; i<j; i++) {
    fgets(buffer,255,file);
    trim(buffer);
// printf("%d %s\n",i,buffer);
    addWord(buffer);
    }

/* *********************************** */
/* ********** Load messages ********** */
/* *********************************** */
  fscanf(file,"%d\n",&numMessages);
  messages = (MESSAGE**)malloc(sizeof(MESSAGE*) * numMessages);
  for (i=0; i<numMessages; i++) {
    msg = (MESSAGE*)malloc(sizeof(MESSAGE));
    messages[i] = msg;
    fscanf(file,"%d\n",&(msg->numLines));
    msg->message = (char**)malloc(sizeof(char*) * msg->numLines);
    for (j=0; j<msg->numLines; j++) {
      fgets(buffer,255,file);
      trim(buffer);
      msg->message[j] = (char*)malloc(strlen(buffer) + 1);
      strcpy(msg->message[j], buffer);
      }
    }

/* ************************************* */
/* ********** Load flag names ********** */
/* ************************************* */
  fscanf(file,"%d\n",&numFlagNames);
  flagNames = (char**)malloc(sizeof(char*) * numFlagNames);
  for (i=0; i<numFlagNames; i++) {
    fgets(buffer,255,file);
    trim(buffer);
    flagNames[i] = (char*)malloc(strlen(buffer) + 1);
    strcpy(flagNames[i], buffer);
    }

/* ******************************** */
/* ********** Load Flags ********** */
/* ******************************** */
  for (i=0; i<1024; i++) {
    fscanf(file,"%d\n",&flags[i]);
    }

/* ********************************** */
/* ********** Load Actions ********** */
/* ********************************** */
  fscanf(file,"%d\n",&numActions);
  actions = (ACTION**)malloc(sizeof(ACTION*) * numActions);
  for (i=0; i<numActions; i++) actions[i] = loadAction(file);

/* ************************************** */
/* ********** Load player data ********** */
/* ************************************** */
  fscanf(file,"%d\n",&(player.location));
  fscanf(file,"%d\n",&(player.lastLocation));
  fscanf(file,"%d\n",&(player.score));
  fscanf(file,"%ld\n",&(player.turnCount));

/* ******************************** */
/* ********** Load Items ********** */
/* ******************************** */
  if (debug) printf("*** Loading Items ***\n");
  fscanf(file,"%d\n",&numItems);
  items = (ITEM**)malloc(sizeof(ITEM*) * numItems);
  for (i=0; i<numItems; i++) {
     items[i] = (ITEM*)malloc(sizeof(ITEM));
    fgets(buffer,255,file); trim(buffer);
    items[i]->name = (char*)malloc(strlen(buffer) + 1);
    strcpy(items[i]->name,buffer);
    fgets(buffer,255,file); trim(buffer);
    items[i]->description = (char*)malloc(strlen(buffer) + 1);
    strcpy(items[i]->description,buffer);
    fgets(buffer,255,file); trim(buffer);
    items[i]->examine = (char*)malloc(strlen(buffer) + 1);
    strcpy(items[i]->examine,buffer);
    fscanf(file,"%d\n",&(items[i]->weight));
    fscanf(file,"%d\n",&(items[i]->score));
    fscanf(file,"%d\n",&(items[i]->location));
    fscanf(file,"%d\n",&(items[i]->wearable));
    fscanf(file,"%d\n",&(items[i]->beingworn));
    fscanf(file,"%d\n",&(items[i]->numActions));
    items[i]->actions = (ACTION**)malloc(sizeof(ACTION*)*items[i]->numActions);
    for (j=0; j<items[i]->numActions; j++)
      items[i]->actions[j] = loadAction(file);
    fscanf(file,"%d\n",&(items[i]->numDescSteps));
    items[i]->descSteps = (int*)malloc(sizeof(int) * items[i]->numDescSteps);
    for (j=0; j<items[i]->numDescSteps; j++)
      fscanf(file,"%d\n",&(items[i]->descSteps[j]));
    fscanf(file,"%d\n",&(items[i]->numExamSteps));
    items[i]->examSteps = (int*)malloc(sizeof(int) * items[i]->numExamSteps);
    for (j=0; j<items[i]->numExamSteps; j++)
      fscanf(file,"%d\n",&(items[i]->examSteps[j]));
    fscanf(file,"%d\n",&(items[i]->numCarryingSteps));
    items[i]->carryingSteps = (int*)malloc(sizeof(int) * items[i]->numCarryingSteps);
    for (j=0; j<items[i]->numCarryingSteps; j++)
      fscanf(file,"%d\n",&(items[i]->carryingSteps[j]));
    fscanf(file,"%d\n",&(items[i]->numTurnSteps));
    items[i]->turnSteps = (int*)malloc(sizeof(int) * items[i]->numTurnSteps);
    for (j=0; j<items[i]->numTurnSteps; j++)
      fscanf(file,"%d\n",&(items[i]->turnSteps[j]));
    }

/* ******************************************* */
/* ********** Load player inventory ********** */
/* ******************************************* */
  if (debug) printf("*** Loading Player Inventory ***\n");
  fscanf(file,"%d\n",&(player.numItems));
  player.items = (ITEM**)malloc(sizeof(ITEM*) * player.numItems);
  for (i=0; i<player.numItems; i++) {
    fgets(buffer,255,file);
    player.items[i] = items[atoi(buffer)];
    }

/* ******************************** */
/* ********** Load Rooms ********** */
/* ******************************** */
  if (debug) printf("*** Loading Rooms ***\n");
  fscanf(file,"%d\n",&numRooms);
  rooms = (ROOM**)malloc(sizeof(ROOM*) * numRooms);
  for (i=0; i<numRooms; i++) {
    room = (ROOM*)malloc(sizeof(ROOM));
    rooms[i] = room;
    fgets(buffer,255,file); trim(buffer);
    room->name = (char*)malloc(strlen(buffer) + 1);
    strcpy(room->name, buffer);
    fgets(buffer,255,file); trim(buffer);
    room->shortDesc = (char*)malloc(strlen(buffer) + 1);
    strcpy(room->shortDesc, buffer);
    fscanf(file,"%d\n",&(room->numDesc));
    room->description = (char**)malloc(sizeof(char*) * room->numDesc);
    for (j=0; j<rooms[i]->numDesc; j++) {
      fgets(buffer,255,file); trim(buffer);
      room->description[j] = (char*)malloc(strlen(buffer) + 1);
      strcpy(room->description[j], buffer);
      }
    fscanf(file,"%d\n",&(room->north[0]));
    fscanf(file,"%d\n",&(room->south[0]));
    fscanf(file,"%d\n",&(room->east[0]));
    fscanf(file,"%d\n",&(room->west[0]));
    fscanf(file,"%d\n",&(room->up[0]));
    fscanf(file,"%d\n",&(room->down[0]));
    fscanf(file,"%d\n",&(room->ne[0]));
    fscanf(file,"%d\n",&(room->nw[0]));
    fscanf(file,"%d\n",&(room->se[0]));
    fscanf(file,"%d\n",&(room->sw[0]));
    fscanf(file,"%d\n",&(room->north[1]));
    fscanf(file,"%d\n",&(room->south[1]));
    fscanf(file,"%d\n",&(room->east[1]));
    fscanf(file,"%d\n",&(room->west[1]));
    fscanf(file,"%d\n",&(room->up[1]));
    fscanf(file,"%d\n",&(room->down[1]));
    fscanf(file,"%d\n",&(room->ne[1]));
    fscanf(file,"%d\n",&(room->nw[1]));
    fscanf(file,"%d\n",&(room->se[1]));
    fscanf(file,"%d\n",&(room->sw[1]));
    fscanf(file,"%d\n",&(room->visited));
    fscanf(file,"%d\n",&(room->needLight));
    fscanf(file,"%d\n",&(room->numItems));
    room->items = (ITEM**)malloc(sizeof(ITEM*) * room->numItems);
    for (j=0; j<room->numItems; j++) {
      fscanf(file,"%d\n",&count);
      room->items[j] = items[count];
      }
    fscanf(file,"%d\n",&(room->numEnterSteps));
    room->enterSteps = (int*)malloc(sizeof(int) * room->numEnterSteps);
    for (j=0; j<room->numEnterSteps; j++)
      fscanf(file,"%d\n",&(room->enterSteps[j]));
    fscanf(file,"%d\n",&(room->numLeaveSteps));
    room->leaveSteps = (int*)malloc(sizeof(int) * room->numLeaveSteps);
    for (j=0; j<room->numLeaveSteps; j++)
      fscanf(file,"%d\n",&(room->leaveSteps[j]));
    fscanf(file,"%d\n",&(rooms[i]->numActions));
// printf("%d %d\n",i,rooms[i]->numActions);
    rooms[i]->actions = (ACTION**)malloc(sizeof(ACTION*)*rooms[i]->numActions);
    for (j=0; j<rooms[i]->numActions; j++)
      rooms[i]->actions[j] = loadAction(file);

    fscanf(file,"%d\n",&(room->numOccupiedSteps));
    room->occupiedSteps = (int*)malloc(sizeof(int) * room->numOccupiedSteps);
    for (j=0; j<room->numOccupiedSteps; j++)
      fscanf(file,"%d\n",&(room->occupiedSteps[j]));
    fscanf(file,"%d\n",&(room->numTurnSteps));
    room->turnSteps = (int*)malloc(sizeof(int) * room->numTurnSteps);
    for (j=0; j<room->numTurnSteps; j++)
      fscanf(file,"%d\n",&(room->turnSteps[j]));
    fscanf(file,"%d\n",&(room->numDescSteps));
    room->descSteps = (int*)malloc(sizeof(int) * room->numDescSteps);
    for (j=0; j<room->numDescSteps; j++)
      fscanf(file,"%d\n",&(room->descSteps[j]));
    }

/* *************************************** */
/* ********** Load Turn Actions ********** */
/* *************************************** */
  if (debug) printf("*** Loading Turn Actions ***\n");
  fscanf(file,"%d\n",&numTurnActions);
  turnActions = (ACTION**)malloc(sizeof(ACTION*) * numTurnActions);
  for (i=0; i<numTurnActions; i++) {
    action = (ACTION*)malloc(sizeof(ACTION));
    turnActions[i] = action;
    fscanf(file,"%d\n",&(action->numActionTokens));
    action->actionTokens = (int*)malloc(sizeof(int) * action->numActionTokens);
    for (j=0; j<action->numActionTokens; j++)
      fscanf(file,"%d\n",&(action->actionTokens[j]));    
    }

/* ************************************ */
/* ********** Load Variables ********** */
/* ************************************ */
  fscanf(file,"%d\n",&numVarNames);
  if (numVarNames > 0) {
    vars = (int*)malloc(sizeof(int) * numVarNames);
    for (j=0; j<numVarNames; j++)
      fscanf(file,"%d\n",&(vars[j]));
    }

/* ************************************************* */
/* ********** Load other player variables ********** */
/* ************************************************* */
  fscanf(file,"%d\n",&(player.light));

/* ******************************** */
/* ********** Load doors ********** */
/* ******************************** */
  if (debug) printf("*** Loading Doors ***\n");
  fscanf(file,"%d\n",&numDoors);
  doors = (DOOR**)malloc(sizeof(DOOR*) * numDoors);
  for (i=0; i<numDoors; i++) {
    door = (DOOR*)malloc(sizeof(DOOR));
    doors[i] = door;
    fgets(buffer,255,file); trim(buffer);
    door->name = (char*)malloc(strlen(buffer) + 1);
    strcpy(door->name, buffer);
    fscanf(file,"%d\n",&(door->opened));
    fscanf(file,"%d\n",&(door->unlocked));
    fscanf(file,"%d\n",&(door->lockable));
    fscanf(file,"%d\n",&(door->key));
    fgets(buffer,255,file); trim(buffer);
    door->description = (char*)malloc(strlen(buffer) + 1);
    strcpy(door->description, buffer);
    fscanf(file,"%d\n",&(door->numDescSteps));
    door->descSteps = (int*)malloc(sizeof(int) * door->numDescSteps);
    for (j=0; j<door->numDescSteps; j++)
      fscanf(file,"%d\n",&(door->descSteps[j]));
    }
  return -1;
  }

