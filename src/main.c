#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAIN
#include "header.h"

int processLeave() {
  int ret;
  if (rooms[player.location]->numLeaveSteps > 0) {
    ret = performAction(rooms[player.location]->leaveSteps,
                  rooms[player.location]->numLeaveSteps);
    return ret;
    }
  return ACTION_FALSE;
  }

int doorsInRoom(int room,int* door) {
  int i;
  i = 0;
  if (rooms[room]->north[1] >= 0) { i++; *door = (rooms[room]->north[1]); }
  if (rooms[room]->south[1] >= 0) { i++; *door = (rooms[room]->south[1]); }
  if (rooms[room]->east[1] >= 0) { i++; *door = (rooms[room]->east[1]); }
  if (rooms[room]->west[1] >= 0) { i++; *door = (rooms[room]->west[1]); }
  if (rooms[room]->up[1] >= 0) { i++; *door = (rooms[room]->up[1]); }
  if (rooms[room]->down[1] >= 0) { i++; *door = (rooms[room]->down[1]); }
  if (rooms[room]->ne[1] >= 0) { i++; *door = (rooms[room]->ne[1]); }
  if (rooms[room]->nw[1] >= 0) { i++; *door = (rooms[room]->nw[1]); }
  if (rooms[room]->se[1] >= 0) { i++; *door = (rooms[room]->se[1]); }
  if (rooms[room]->sw[1] >= 0) { i++; *door = (rooms[room]->sw[1]); }
  return i;
  }

int getItemFromTokens(int pos) {
  }

void mainLoop() {
  int  i;
  int  j;
  int  f;
  int  look;
  char buffer[1024];
  gameFlag = ' ';
  look = 0;
  while (gameFlag == ' ') {

/* ************************************ */
/* ***** Process any turn actions ***** */
/* ************************************ */
    for (i=0; i<numTurnActions; i++) {
      performAction(turnActions[i]->actionTokens,turnActions[i]->numActionTokens);
      if (gameFlag != ' ') return;
      }

/* ************************************************ */
/* ***** Process any TURN blocks in all rooms ***** */
/* ************************************************ */
    for (i=0; i<numRooms; i++) {
      if (rooms[i]->numTurnSteps > 0) {
        performAction(rooms[i]->turnSteps,
                      rooms[i]->numTurnSteps);
         if (gameFlag != ' ') return;
         }
      }

/* ******************************* */
/* ***** Entering a new room ***** */
/* ******************************* */
    if (rooms[player.location]->needLight && player.light == 0) {
      printf("It is too dark to see where you are.\n");
      } else {
      if (player.location != player.lastLocation || look == 1) {
  /* ***** Long or short depending on if the room has been visited ***** */
        if (rooms[player.location]->visited)
          printf("%s\n",rooms[player.location]->shortDesc);
          else {
            for (i=0; i<rooms[player.location]->numDesc; i++)
              printf("%s\n",rooms[player.location]->description[i]);
            if (rooms[player.location]->numDescSteps > 0) {
              performAction(rooms[i]->descSteps,
                            rooms[i]->numDescSteps);
              }
            }
  /* ***** Mark room as visited ***** */
        rooms[player.location]->visited = -1;
  /* ***** List any items found in the room ***** */
        if (rooms[player.location]->numItems > 0) {
          printf("You find here:\n");
          for (i=0; i<rooms[player.location]->numItems; i++) {
              if (rooms[player.location]->items[i]->numDescSteps > 0)
                performAction(rooms[player.location]->items[i]->descSteps,
                              rooms[player.location]->items[i]->numDescSteps);
                else printf("    %s\n",rooms[player.location]->items[i]->description);
            }
          }
        }
      }

/* ***** If the player entered a new room, process entry action ***** */
    if (player.location != player.lastLocation && player.lastLocation >= 0) {
      if (rooms[player.location]->numEnterSteps > 0)
        performAction(rooms[player.location]->enterSteps,
                      rooms[player.location]->numEnterSteps);
      if (gameFlag != ' ') return;
      }

/* ***** Process occupied block for room player is in ***** */
  if (rooms[player.location]->numOccupiedSteps > 0) {
    performAction(rooms[player.location]->occupiedSteps,
                  rooms[player.location]->numOccupiedSteps);
     if (gameFlag != ' ') return;
     }

/* ***** Process items player is carrying ***** */
    for (i=0; i<player.numItems; i++)
      if (player.items[i]->numCarryingSteps > 0)
        performAction(player.items[i]->carryingSteps,
                      player.items[i]->numCarryingSteps);

/* ***** Process items turn blocks ***** */
    for (i=0; i<numItems; i++)
      if (items[i]->numTurnSteps > 0)
        performAction(items[i]->turnSteps,
                      items[i]->numTurnSteps);

/* ***** Process light ***** */
    if (player.light > 0) player.light--;
 
    player.lastLocation = player.location;
    look = 0;
    lastDir = ' ';
    printf(">");
    fgets(buffer,1023,stdin);
    while (strlen(buffer) > 0 && buffer[strlen(buffer)-1] < 32)
      buffer[strlen(buffer)-1] = 0;
    printf("\n\n");
    if (tokenize(buffer) > 0) {
      player.turnCount++;
      if (checkRoomActions()) ;
      else if (checkObjects());
      else if (checkActions()) ;
/* ******************** QUIT object ********************* */
      else if (numTokens == 1 && tokens[0] == 16) gameFlag = '*';
/* ******************** SAVE *********************** */
      else if (numTokens == 1 && tokens[0] == 24) save();
      else if (numTokens == 1 && tokens[0] == 14) save();
/* ******************** EXITS ********************** */
      else if (numTokens == 1 && tokens[0] == 36) {
        printf("Exits:");
        if (rooms[player.location]->north[0] >= 0) printf(" N");
        if (rooms[player.location]->south[0] >= 0) printf(" S");
        if (rooms[player.location]->west[0] >= 0) printf(" W");
        if (rooms[player.location]->east[0] >= 0) printf(" E");
        if (rooms[player.location]->nw[0] >= 0) printf(" NW");
        if (rooms[player.location]->ne[0] >= 0) printf(" NE");
        if (rooms[player.location]->sw[0] >= 0) printf(" SW");
        if (rooms[player.location]->se[0] >= 0) printf(" SE");
        if (rooms[player.location]->up[0] >= 0) printf(" U");
        if (rooms[player.location]->down[0] >= 0) printf(" D");
        printf("\n\n");
        }

/* ******************** INVENT ********************* */
      else if (numTokens == 1 && tokens[0] == 12) {
        printf("You are carrying:\n");
        for (i=0; i<player.numItems; i++)
          if (player.items[i]->numDescSteps > 0)
            performAction(player.items[i]->descSteps,
                          player.items[i]->numDescSteps);
            else printf("    %s\n",player.items[i]->description);
        }
/* ******************** VOCAB ********************* */
      else if (numTokens == 1 && tokens[0] == 22) {
        j = 0;
        for (i=0; i<numVocab; i++) {
          if (vocab[i][0] != '_') {
            printf("%15s",vocab[i]);
            if (++j == 4) {
              printf("\n");
              j = 0;
              }
            }
          }
        if (j != 0) printf("\n");
        }
/* ******************** SCORE ********************* */
      else if (numTokens == 1 && tokens[0] == 13) {
        printf("You have scored %d points in %ld turns.\n",player.score,player.turnCount);
        }
/* ******************** Weight ********************* */
      else if (numTokens == 1 && tokens[0] == 29) {
         j = 0;
         for (i=0; i<player.numItems; i++)
         j += player.items[i]->weight;
        printf("You are carrying %d pound",j);
        if (j!= 1) printf("s");
        printf("\n");
        }
/* ******************** LOOK ********************* */
      else if (numTokens == 1 && tokens[0] == 0) {
        rooms[player.location]->visited = 0;
        look = 1;
        }
/* ******************** NORTH ********************* */
      else if ((numTokens == 1 && (tokens[0] == 1 || tokens[0] == 2)) ||
               (numTokens == 2 && tokens[0] == 9 && (tokens[1] == 1 || tokens[1] == 2))) {
        lastDir = 'N';
        if (rooms[player.location]->north[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->north[1] < 0)
              player.location = rooms[player.location]->north[0];
            else if (rooms[player.location]->north[1] >= 0 &&
                doors[rooms[player.location]->north[1]]->opened == 1)
              player.location = rooms[player.location]->north[0];
              else printf("Your passage is currently blocked\n");
            }
          }
        else printf("You bump into a wall\n");
        }
/* ******************** SOUTH ********************* */
      else if ((numTokens == 1 && (tokens[0] == 3 || tokens[0] == 4)) ||
               (numTokens == 2 && tokens[0] == 9 && (tokens[1] == 3 || tokens[1] == 4))) {
        lastDir = 'S';
        if (rooms[player.location]->south[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->south[1] < 0)
              player.location = rooms[player.location]->south[0];
            else if (rooms[player.location]->south[1] >= 0 &&
                doors[rooms[player.location]->south[1]]->opened == 1)
              player.location = rooms[player.location]->south[0];
              else printf("Your passage is currently blocked\n");
            }
          }
        else printf("You bump into a wall\n");
        }
/* ******************** EAST ********************* */
      else if ((numTokens == 1 && (tokens[0] == 5 || tokens[0] == 6)) ||
               (numTokens == 2 && tokens[0] == 9 && (tokens[1] == 5 || tokens[1] == 6))) {
        lastDir = 'E';
        if (rooms[player.location]->east[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->east[1] < 0)
              player.location = rooms[player.location]->east[0];
            else if (rooms[player.location]->east[1] >= 0 &&
                doors[rooms[player.location]->east[1]]->opened == 1)
              player.location = rooms[player.location]->east[0];
              else printf("Your passage is currently blocked\n");
            }
          }
        else printf("You bump into a wall\n");
        }
/* ******************** WEST ********************* */
      else if ((numTokens == 1 && (tokens[0] == 7 || tokens[0] == 8)) ||
               (numTokens == 2 && tokens[0] == 9 && (tokens[1] == 7 || tokens[1] == 8))) {
        lastDir = 'W';
        if (rooms[player.location]->west[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->west[1] < 0)
              player.location = rooms[player.location]->west[0];
            else if (rooms[player.location]->west[1] >= 0 &&
                doors[rooms[player.location]->west[1]]->opened == 1)
              player.location = rooms[player.location]->west[0];
              else printf("Your passage is currently blocked\n");
            }
            }
        else printf("You bump into a wall\n");
        }
/* ******************** NW ********************* */
      else if ((numTokens == 1 && tokens[0] == 26) ||
               (numTokens == 2 && tokens[0] == 9 && tokens[1] == 26)) {
        lastDir = 'N';
        if (rooms[player.location]->nw[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->nw[1] < 0)
              player.location = rooms[player.location]->nw[0];
            else if (rooms[player.location]->nw[1] >= 0 &&
                doors[rooms[player.location]->nw[1]]->opened == 1)
              player.location = rooms[player.location]->nw[0];
              else printf("Your passage is currently blocked\n");
            }
          }
        else printf("You bump into a wall\n");
        }
/* ******************** NE ********************* */
      else if ((numTokens == 1 && tokens[0] == 25) ||
               (numTokens == 2 && tokens[0] == 9 && tokens[1] == 25)) {
        lastDir = 'N';
        if (rooms[player.location]->ne[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->ne[1] < 0)
              player.location = rooms[player.location]->ne[0];
            else if (rooms[player.location]->ne[1] >= 0 &&
                doors[rooms[player.location]->ne[1]]->opened == 1)
              player.location = rooms[player.location]->ne[0];
              else printf("Your passage is currently blocked\n");
            }
          }
        else printf("You bump into a wall\n");
        }
/* ******************** SW ********************* */
      else if ((numTokens == 1 && tokens[0] == 28) ||
               (numTokens == 2 && tokens[0] == 9 && tokens[1] == 28)) {
        lastDir = 'S';
        if (rooms[player.location]->sw[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->sw[1] < 0)
              player.location = rooms[player.location]->sw[0];
            else if (rooms[player.location]->sw[1] >= 0 &&
                doors[rooms[player.location]->sw[1]]->opened == 1)
              player.location = rooms[player.location]->sw[0];
              else printf("Your passage is currently blocked\n");
            }
          }
        else printf("You bump into a wall\n");
        }
/* ******************** SE ********************* */
      else if ((numTokens == 1 && tokens[0] == 27) ||
               (numTokens == 2 && tokens[0] == 9 && tokens[1] == 27)) {
        lastDir = 'S';
        if (rooms[player.location]->se[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->se[1] < 0)
              player.location = rooms[player.location]->se[0];
            else if (rooms[player.location]->se[1] >= 0 &&
                doors[rooms[player.location]->se[1]]->opened == 1)
              player.location = rooms[player.location]->se[0];
              else printf("Your passage is currently blocked\n");
            }
          }
        else printf("You bump into a wall\n");
        }
/* ******************** UP ********************* */
      else if ((numTokens == 1 && tokens[0] == 10) ||
               (numTokens == 2 && tokens[0] == 9 && tokens[1] == 10)) {
        lastDir = 'U';
        if (rooms[player.location]->up[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->up[1] < 0)
              player.location = rooms[player.location]->up[0];
            else if (rooms[player.location]->up[1] >= 0 &&
                doors[rooms[player.location]->up[1]]->opened == 1)
              player.location = rooms[player.location]->up[0];
              else printf("Your passage is currently blocked\n");
            }
            }
        else printf("You are incapable of climbing here\n");
        }
/* ******************** DOWN ********************* */
      else if ((numTokens == 1 && tokens[0] == 11) ||
               (numTokens == 2 && tokens[0] == 9 && tokens[1] == 11)) {
        lastDir = 'D';
        if (rooms[player.location]->down[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->down[1] < 0)
              player.location = rooms[player.location]->down[0];
            else if (rooms[player.location]->down[1] >= 0 &&
                doors[rooms[player.location]->down[1]]->opened == 1)
              player.location = rooms[player.location]->down[0];
              else printf("Your passage is currently blocked\n");
            }
          }
        else printf("You are incapable of climbing here\n");
        }
/* ******************** GET object ********************** */
      else if (numTokens == 2 && (tokens[0] == 17 || tokens[0] == 18)) {
        j = getItemNumber(vocab[tokens[1]]);
        if (j == -1) {
          printf("There is no %s here\n",vocab[tokens[1]]);
          } else {
          if (getItem(j)) printf("Taken\n");
          }
        }
/* ******************** DROP object ********************* */
      else if (numTokens == 2 && (tokens[0] == 19 || tokens[0] == 20)) {
        j = getItemNumber(vocab[tokens[1]]);
        if (j == -1) {
          printf("Yor are not carrying %s\n",vocab[tokens[1]]);
          } else {
          if (dropItem(j)) printf("Dropped\n");
          }
        }
/* **************************************************** */
/* ******************** OPEN door ********************* */
/* **************************************************** */
      else if (tokens[0] == 30) {
        if (doorsInRoom(player.location,&j) == 1) {
          if (numTokens == 2 && tokens[1] == 34) {
            if (doors[j]->unlocked != 0) {
              if (doors[j]->opened == 0) {
                doors[j]->opened = 1;
                printf("The door is now open.\n");
                } else {
                printf("The door is already open.\n");
                }
              } else {
              printf("The door is currently locked.\n");
              }
            }
          }
        }
/* ***************************************************** */
/* ******************** CLOSE door ********************* */
/* ***************************************************** */
      else if (tokens[0] == 31) {
        if (doorsInRoom(player.location,&j) == 1) {
          if (numTokens == 2 && tokens[1] == 34) {
              if (doors[j]->opened != 0) {
                doors[j]->opened = 0;
                printf("The door is now closed.\n");
                } else {
                printf("The door is already closed.\n");
                }
              }
            }
          }
/* ****************************************************** */
/* ******************** UNLOCK door ********************* */
/* ****************************************************** */
      else if (tokens[0] == 33) {
        if (doorsInRoom(player.location,&j) == 1) {
          if (numTokens == 2 && tokens[1] == 34) {
            if (doors[j]->unlocked != 0) {
              printf("The door is already unlocked.\n");
              } else {
              f = -1;
              for (i=0; i< player.numItems; i++) {
                if (player.items[i] == items[doors[j]->key]) f = i;
                }
              if (f >= 0) {
                printf("The door has been unlocked.\n");
                doors[j]->unlocked = 1;
                } else {
                printf("You do not have the key for that door.\n");
                }
              }
            }
          }
        }
/* ****************************************************** */
/* ******************** LOCK door *********************** */
/* ****************************************************** */
      else if (tokens[0] == 32) {
        if (doorsInRoom(player.location,&j) == 1) {
          if (numTokens == 2 && tokens[1] == 34) {
            if (doors[j]->lockable == 0)
              printf("This door cannot be locked.\n");
            else if (doors[j]->unlocked == 0) {
              printf("The door is already locked.\n");
              } else {
              f = -1;
              for (i=0; i< player.numItems; i++) {
                if (player.items[i] == items[doors[j]->key]) f = i;
                }
              if (f >= 0) {
                printf("The door has been locked.\n");
                doors[j]->unlocked = 0;
                } else {
                printf("You do not have the key for that door.\n");
                }
              }
            }
          }
        }
/* ********************************************************* */
/* ******************** EXAMINE object ********************* */
/* ********************************************************* */
      else if (numTokens == 2 && tokens[0] == 23) {
        j = -1;
/* ***** Check for item in inventory ***** */
        for (i=0; i<player.numItems; i++)
          if (getToken(player.items[i]->name) == tokens[1])
            j = i;
/* ***** Show description if item is found ***** */
        if (j >= 0) {
          if (player.items[j]->numExamSteps > 0) 
            performAction(player.items[j]->examSteps,
                          player.items[j]->numExamSteps);
            else printf("%s\n",player.items[j]->examine);
          j = -2;
          }
        if (j == -1) {
/* ***** Check for noncarryable items in room ***** */
          for (i=0; i<rooms[player.location]->numItems; i++) {
            if (rooms[player.location]->items[i]->weight < 0 &&
                getToken(rooms[player.location]->items[i]->name) == tokens[1])
                  j = i;
            }
          }
/* ***** Show description if item is found ***** */
        if (j >= 0) {
          if (rooms[player.location]->items[j]->numExamSteps > 0) 
            performAction(rooms[player.location]->items[j]->examSteps,
                          rooms[player.location]->items[j]->numExamSteps);
            else printf("%s\n",rooms[player.location]->items[j]->examine);
          }
/* ***** Otherwise indicate player cannot examine ***** */
        if (j == -1) {
          printf("You are not carrying the ");
          printToken(tokens[1]);
          printf("\n");
          }
        }
      else printf("I do not understand\n");
      }
    }
  }

void encodeFile(char* fname) {
  char fname2[256];
  char inBuffer[1024];
  char outBuffer[1024];
  FILE* inFile;
  FILE* outFile;
  RC4_DATA key;
  int   i;
  key=rc4_init("tadvencrypt",11);
  strcpy(fname2,fname);
  strcat(fname2,".enc");
  inFile = fopen(fname,"r");
  outFile = fopen(fname2,"w");
  fgets(inBuffer,1023,inFile);
  for (i=0; i<strlen(inBuffer); i++)
    if (inBuffer[i]>0 && inBuffer[i]<32 && inBuffer[i]!=9) inBuffer[i] = 0;
  strcat(inBuffer," ENC");
  fprintf(outFile,"%s\n",inBuffer);
  while (fgets(inBuffer,1023,inFile) != NULL) {
    for (i=0; i<strlen(inBuffer); i++)
      if (inBuffer[i]>0 && inBuffer[i]<32 && inBuffer[i]!=9) inBuffer[i] = 0;
    encrypt(inBuffer,outBuffer,&key);
    fprintf(outFile,"%s\n",outBuffer);
    }
  fclose(inFile);
  fclose(outFile);
  }

int main(int argc,char* argv[]) {
  int i;
  debug = 1;
  numFunctions = 0;
  rcs_randomize();
  for (i=0; i<1024; i++) flags[i] = 0;
  i = 0;
  if (argc == 3 && strcmp(argv[1],"-c")==0) i=1;
  if (argc == 2 && strcmp(argv[1],"-c")!=0) i=1;
  if (i==0) {
    printf("Usage: adv adventure-file\n");
    printf("   or  adv -c adventure-file\n");
    return 0;
    }
  if (strcmp(argv[1],"-c")==0) {
    encodeFile(argv[2]);
    return 0;
    }
  init();
  if (strstr(argv[1],".sav") != NULL) {
    load(argv[1]);
    player.lastLocation = -1;
    } else {
    readFile(argv[1]);
    reset(); 
    }
  printf("\n\n");
  if (numStartSteps > 0) performAction(startSteps, numStartSteps);
  mainLoop();
  printf("You scored a total of %d points in %ld turns\n",player.score,player.turnCount);
  return 0;
  }
