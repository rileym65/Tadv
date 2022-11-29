#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void init() {
  int i;
  if (debug) printf("Entering INIT\n"); fflush(stdout);
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
  sVarNames   = NULL;
  sVarValues  = NULL;
  numStartSteps  = 0;
  numEquates     = 0;
  numTurnActions = 0;
  numVarNames  = 0;
  numFlagNames = 0;
  numSVars = 0;
  numActions  = 0;
  numVocab    = 0;
  numItems    = 0;
  numRooms    = 0;
  numMessages = 0;
  player.score = 0;
  player.light = 0;
  player.turnCount = 0;
  player.maxWeight =99999;
  player.maxItems = 99999;
  tracing = 0;
  tron = 0;
  if (debug) printf("Loading initial dictionary\n"); fflush(stdout);
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
  addWord("exits");         /* 36 */
  addWord("wear");          /* 37 */
  addWord("remove");        /* 38 */
  addWord("into");          /* 39 */
  addWord("in");            /* 40 */
  addWord("from");          /* 41 */
  addWord("wearing");       /* 42 */
  if (debug) printf("Loading initial flags\n"); fflush(stdout);
  addFlag("F_HAS_LIGHT");
  addFlag("F_CAN_MOVE");
  if (debug) printf("Exiting INIT\n"); fflush(stdout);
  }

