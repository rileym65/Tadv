#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int getItemPos(ITEM* item) {
  int i;
  for (i=0; i<numItems; i++)
    if (item == items[i]) return i;
  return -1;
  }

void saveAction(ACTION* action,FILE* file) {
  int j;
  fprintf(file,"%d\n",action->numPhraseTokens);
  for (j=0; j<action->numPhraseTokens; j++)
    fprintf(file,"%d\n",action->phraseTokens[j]);
  fprintf(file,"%d\n",action->numActionTokens);
  for (j=0; j<action->numActionTokens; j++)
    fprintf(file,"%d\n",action->actionTokens[j]);
  }

void save() {
  int i;
  int j;
  FILE* file;
  char buffer[255];
  printf("Enter Filename? ");
  fgets(buffer,254,stdin);
  while (strlen(buffer) > 0 && buffer[strlen(buffer)-1] < 32)
    buffer[strlen(buffer)-1] = 0;
  strcat(buffer,".sav");
  file = fopen(buffer,"w");
/* *************************** */
/* ***** Save vocabulary ***** */
/* *************************** */
  if (debug) printf("*** Saving vocabulary ***\n");
  fprintf(file,"%d\n",numVocab);
  for (i=25; i<numVocab; i++) fprintf(file,"%s\n",vocab[i]);

/* ************************* */
/* ***** Save messages ***** */
/* ************************* */
  if (debug) printf("*** Saving messages ***\n");
  fprintf(file,"%d\n",numMessages);
  for (i=0; i<numMessages; i++) {
    fprintf(file,"%d\n",messages[i]->numLines);
    for (j=0; j<messages[i]->numLines; j++)
      fprintf(file,"%s\n",messages[i]->message[j]);
    }

/* *************************** */
/* ***** Save flag names ***** */
/* *************************** */
  if (debug) printf("*** Saving flag names ***\n");
  fprintf(file,"%d\n",numFlagNames);
  for (i=0; i<numFlagNames; i++) fprintf(file,"%s\n",flagNames[i]);

/* ********************** */
/* ***** Save flags ***** */
/* ********************** */
  if (debug) printf("*** Saving flags ***\n");
  for (i=0; i<1024; i++) fprintf(file,"%d\n",flags[i]);

/* ************************ */
/* ***** Save actions ***** */
/* ************************ */
  if (debug) printf("*** Saving actions ***\n");
  fprintf(file,"%d\n",numActions);
  for (i=0; i<numActions; i++) saveAction(actions[i],file);

/* **************************** */
/* ***** Save player data ***** */
/* **************************** */
  if (debug) printf("*** Saving player data ***\n");
  fprintf(file,"%d\n",player.location);
  fprintf(file,"%d\n",player.lastLocation);
  fprintf(file,"%d\n",player.score);
  fprintf(file,"%ld\n",player.turnCount);

/* ********************** */
/* ***** Save Items ***** */
/* ********************** */
  if (debug) printf("*** Saving items ***\n");
  fprintf(file,"%d\n",numItems);
  for (i=0; i<numItems; i++) {
    fprintf(file,"%d\n",items[i]->number);
    fprintf(file,"%s\n",items[i]->name);
    fprintf(file,"%s\n",items[i]->identifier);
    fprintf(file,"%s\n",items[i]->description);
    fprintf(file,"%s\n",items[i]->examine);
    fprintf(file,"%d\n",items[i]->weight);
    fprintf(file,"%d\n",items[i]->score);
    fprintf(file,"%d\n",items[i]->location);
    fprintf(file,"%d\n",items[i]->wearable);
    fprintf(file,"%d\n",items[i]->beingworn);
    fprintf(file,"%d\n",items[i]->cursed);
    fprintf(file,"%d\n",items[i]->numActions);
    for (j=0; j<items[i]->numActions; j++)
      saveAction(items[i]->actions[j],file);
    fprintf(file,"%d\n",items[i]->numDescSteps);
    for (j=0; j<items[i]->numDescSteps; j++)
      fprintf(file,"%d\n",items[i]->descSteps[j]);
    fprintf(file,"%d\n",items[i]->numExamSteps);
    for (j=0; j<items[i]->numExamSteps; j++)
      fprintf(file,"%d\n",items[i]->examSteps[j]);
    fprintf(file,"%d\n",items[i]->numCarryingSteps);
    for (j=0; j<items[i]->numCarryingSteps; j++)
      fprintf(file,"%d\n",items[i]->carryingSteps[j]);
    fprintf(file,"%d\n",items[i]->numTurnSteps);
    for (j=0; j<items[i]->numTurnSteps; j++)
      fprintf(file,"%d\n",items[i]->turnSteps[j]);
    fprintf(file,"%d\n",items[i]->container);
    fprintf(file,"%d\n",items[i]->maxContents);
    fprintf(file,"%d\n",items[i]->numContents);
    for (j=0; j<items[i]->numContents; j++)
      fprintf(file,"%d\n",items[i]->contents[j]);
    }

/* ********************************* */
/* ***** Save player inventory ***** */
/* ********************************* */
  if (debug) printf("*** Saving inventory ***\n");
  fprintf(file,"%d\n",player.numItems);
  for (i=0; i<player.numItems; i++)
    fprintf(file,"%d\n",getItemPos(player.items[i]));

/* ********************** */
/* ***** Save rooms ***** */
/* ********************** */
  if (debug) printf("*** Saving rooms ***\n");
  fprintf(file,"%d\n",numRooms);
  for (i=0; i<numRooms; i++) {
    fprintf(file,"%s\n",rooms[i]->name);
    fprintf(file,"%s\n",rooms[i]->shortDesc);
    fprintf(file,"%d\n",rooms[i]->numDesc);
    for (j=0; j<rooms[i]->numDesc; j++)
      fprintf(file,"%s\n",rooms[i]->description[j]);
    fprintf(file,"%d\n",rooms[i]->north[0]);
    fprintf(file,"%d\n",rooms[i]->south[0]);
    fprintf(file,"%d\n",rooms[i]->east[0]);
    fprintf(file,"%d\n",rooms[i]->west[0]);
    fprintf(file,"%d\n",rooms[i]->up[0]);
    fprintf(file,"%d\n",rooms[i]->down[0]);
    fprintf(file,"%d\n",rooms[i]->ne[0]);
    fprintf(file,"%d\n",rooms[i]->nw[0]);
    fprintf(file,"%d\n",rooms[i]->se[0]);
    fprintf(file,"%d\n",rooms[i]->sw[0]);
    fprintf(file,"%d\n",rooms[i]->north[1]);
    fprintf(file,"%d\n",rooms[i]->south[1]);
    fprintf(file,"%d\n",rooms[i]->east[1]);
    fprintf(file,"%d\n",rooms[i]->west[1]);
    fprintf(file,"%d\n",rooms[i]->up[1]);
    fprintf(file,"%d\n",rooms[i]->down[1]);
    fprintf(file,"%d\n",rooms[i]->ne[1]);
    fprintf(file,"%d\n",rooms[i]->nw[1]);
    fprintf(file,"%d\n",rooms[i]->se[1]);
    fprintf(file,"%d\n",rooms[i]->sw[1]);
    fprintf(file,"%d\n",rooms[i]->visited);
    fprintf(file,"%d\n",rooms[i]->needLight);
    fprintf(file,"%d\n",rooms[i]->numItems);
    for (j=0; j<rooms[i]->numItems; j++)
      fprintf(file,"%d\n",getItemPos(rooms[i]->items[j]));
    fprintf(file,"%d\n",rooms[i]->numEnterSteps);
    for (j=0; j<rooms[i]->numEnterSteps; j++)
      fprintf(file,"%d\n",rooms[i]->enterSteps[j]);
    fprintf(file,"%d\n",rooms[i]->numLeaveSteps);
    for (j=0; j<rooms[i]->numLeaveSteps; j++)
      fprintf(file,"%d\n",rooms[i]->leaveSteps[j]);
    fprintf(file,"%d\n",rooms[i]->numActions);
    for (j=0; j<rooms[i]->numActions; j++)
      saveAction(rooms[i]->actions[j],file);
    fprintf(file,"%d\n",rooms[i]->numOccupiedSteps);
    for (j=0; j<rooms[i]->numOccupiedSteps; j++)
      fprintf(file,"%d\n",rooms[i]->occupiedSteps[j]);
    fprintf(file,"%d\n",rooms[i]->numTurnSteps);
    for (j=0; j<rooms[i]->numTurnSteps; j++)
      fprintf(file,"%d\n",rooms[i]->turnSteps[j]);
    fprintf(file,"%d\n",rooms[i]->numDescSteps);
    for (j=0; j<rooms[i]->numDescSteps; j++)
      fprintf(file,"%d\n",rooms[i]->descSteps[j]);
    }

/* ***************************** */
/* ***** Save turn actions ***** */
/* ***************************** */
  if (debug) printf("*** Saving turn actions ***\n");
  fprintf(file,"%d\n",numTurnActions);
  for (i=0; i<numTurnActions; i++) {
    fprintf(file,"%d\n",turnActions[i]->numActionTokens);
    for (j=0; j<turnActions[i]->numActionTokens; j++)
      fprintf(file,"%d\n",turnActions[i]->actionTokens[j]);
    }

/* ************************** */
/* ***** Save variables ***** */
/* ************************** */
  if (debug) printf("*** Saving variables ***\n");
  fprintf(file,"%d\n",numVarNames);
  for (i=0; i<numVarNames; i++) fprintf(file,"%d\n",vars[i]);

/* ********************************* */
/* ***** Save string variables ***** */
/* ********************************* */
  if (debug) printf("*** Saving string variables ***\n");
  fprintf(file,"%d\n",numSVars);
  for (i=0; i<numSVars; i++) fprintf(file,"%s\n",sVarValues[i]);

/* *************************************** */
/* ***** Save other player variables ***** */
/* *************************************** */
  if (debug) printf("*** Saving other player data ***\n");
  fprintf(file,"%d\n",player.light);
  fprintf(file,"%d\n",player.health);
  fprintf(file,"%d\n",player.maxWeight);
  fprintf(file,"%d\n",player.maxItems);

/* ********************** */
/* ***** Save doors ***** */
/* ********************** */
  if (debug) printf("*** Saving doors ***\n");
  fprintf(file,"%d\n",numDoors);
  for (i=0; i<numDoors; i++) {
    fprintf(file,"%s\n",doors[i]->name);
    fprintf(file,"%d\n",doors[i]->opened);
    fprintf(file,"%d\n",doors[i]->unlocked);
    fprintf(file,"%d\n",doors[i]->lockable);
    fprintf(file,"%d\n",doors[i]->key);
    fprintf(file,"%s\n",doors[i]->description);
    fprintf(file,"%d\n",doors[i]->numDescSteps);
    for (j=0; j<doors[i]->numDescSteps; j++)
      fprintf(file,"%d\n",doors[i]->descSteps[j]);
    }

  fclose(file);
  }
