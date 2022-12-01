#include "header.h"

void mainLoop() {
  int  i;
  int  j;
  int  f;
  int  look;
  int  a;
  int  b;
  int  room;
  int  newRoom;
  char buffer[1024];
  ITEM *item;
  gameFlag = ' ';
  look = 0;
  newRoom = 0;
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
      if (player.location != player.lastLocation || look == 1 || newRoom != 0) {
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
    if (player.location != player.lastLocation && player.lastLocation >= 0) newRoom = -1;
    if (newRoom) {
      newRoom = 0;
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

/* ***** Process items player is wearing ***** */
    for (i=0; i<player.numItems; i++)
      if (player.items[i]->wearable && player.items[i]->beingworn)
        if (player.items[i]->numWearingSteps > 0)
          performAction(player.items[i]->wearingSteps,
                        player.items[i]->numWearingSteps);

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
      else if (numTokens == 1 && tokens[0] == V_QUIT) gameFlag = '*';
/* ******************** SAVE *********************** */
      else if (numTokens == 1 && tokens[0] == 24) save();
      else if (numTokens == 1 && tokens[0] == V_SAVE) save();
/* ******************** EXITS ********************** */
      else if (numTokens == 1 && tokens[0] == V_EXITS) {
        if (rooms[player.location]->needLight && player.light == 0) {
          printf("It is too dark to see the exits\n");
          }
        else {
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
        }

/* ******************** INVENT ********************* */
      else if (numTokens == 1 && tokens[0] == V_INVENT) {
        printf("You are carrying:\n");
        for (i=0; i<player.numItems; i++) {
          if (player.items[i]->numDescSteps > 0)
            performAction(player.items[i]->descSteps,
                          player.items[i]->numDescSteps);
            else printf("    %s",player.items[i]->description);
          if (player.items[i]->beingworn) printf(" being worn");
          if (player.items[i]->container != 0 &&
              player.items[i]->numContents > 0) {
            printf(" Contains:\n");
            for (j=0; j<player.items[i]->numContents; j++) {
              if (items[player.items[i]->contents[j]]->numDescSteps > 0)
                performAction(items[player.items[i]->contents[j]]->descSteps,
                              items[player.items[i]->contents[j]]->numDescSteps);
                else printf("      %s",items[player.items[i]->contents[j]]->description);
                printf("\n");
              }
            }
          else printf("\n");
          }
        }
/* ******************** VOCAB ********************* */
      else if (numTokens == 1 && tokens[0] == V_VOCAB) {
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
      else if (numTokens == 1 && tokens[0] == V_SCORE) {
        printf("You have scored %d points in %ld turns.\n",score(),player.turnCount);
        }
/* ******************** Weight ********************* */
      else if (numTokens == 1 && tokens[0] == V_WEIGHT) {
         j = weight();
        printf("You are carrying %d pound",j);
        if (j!= 1) printf("s");
        printf("\n");
        }
/* ******************** LOOK ********************* */
      else if (numTokens == 1 && tokens[0] == V_LOOK) {
        rooms[player.location]->visited = 0;
        look = 1;
        }
/* ******************** NORTH ********************* */
      else if ((numTokens == 1 && (tokens[0] == V_NORTH || tokens[0] == V_N)) ||
               (numTokens == 2 && tokens[0] == V_GO && (tokens[1] == V_NORTH || tokens[1] == V_N))) {
        lastDir = 'N';
        if (rooms[player.location]->north[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->north[1] < 0) {
              player.location = rooms[player.location]->north[0];
              newRoom = -1;
              }
            else if (rooms[player.location]->north[1] >= 0 &&
                doors[rooms[player.location]->north[1]]->opened == 1) {
              player.location = rooms[player.location]->north[0];
              newRoom = -1;
              }
              else printf("Your passage is currently blocked\n");
            }
          }
        else printf("You bump into a wall\n");
        }
/* ******************** SOUTH ********************* */
      else if ((numTokens == 1 && (tokens[0] == V_SOUTH || tokens[0] == V_S)) ||
               (numTokens == 2 && tokens[0] == V_GO && (tokens[1] == V_SOUTH || tokens[1] == V_S))) {
        lastDir = 'S';
        if (rooms[player.location]->south[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->south[1] < 0) {
              player.location = rooms[player.location]->south[0];
              newRoom = -1;
              }
            else if (rooms[player.location]->south[1] >= 0 &&
                doors[rooms[player.location]->south[1]]->opened == 1) {
              player.location = rooms[player.location]->south[0];
              newRoom = -1;
              }
              else printf("Your passage is currently blocked\n");
            }
          }
        else printf("You bump into a wall\n");
        }
/* ******************** EAST ********************* */
      else if ((numTokens == 1 && (tokens[0] == V_EAST || tokens[0] == V_E)) ||
               (numTokens == 2 && tokens[0] == V_GO && (tokens[1] == V_EAST || tokens[1] == V_E))) {
        lastDir = 'E';
        if (rooms[player.location]->east[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->east[1] < 0) {
              player.location = rooms[player.location]->east[0];
              newRoom = -1;
              }
            else if (rooms[player.location]->east[1] >= 0 &&
                doors[rooms[player.location]->east[1]]->opened == 1) {
              player.location = rooms[player.location]->east[0];
              newRoom = -1;
              }
              else printf("Your passage is currently blocked\n");
            }
          }
        else printf("You bump into a wall\n");
        }
/* ******************** WEST ********************* */
      else if ((numTokens == 1 && (tokens[0] == V_WEST || tokens[0] == V_W)) ||
               (numTokens == 2 && tokens[0] == V_GO && (tokens[1] == V_WEST || tokens[1] == V_W))) {
        lastDir = 'W';
        if (rooms[player.location]->west[0] >= 0) {
          if (processLeave() != ACTION_TRUE) {
            if (rooms[player.location]->west[1] < 0) {
              player.location = rooms[player.location]->west[0];
              newRoom = -1;
              }
            else if (rooms[player.location]->west[1] >= 0 &&
                doors[rooms[player.location]->west[1]]->opened == 1) {
              player.location = rooms[player.location]->west[0];
              newRoom = -1;
              }
              else printf("Your passage is currently blocked\n");
            }
            }
        else printf("You bump into a wall\n");
        }
/* ******************** NW ********************* */
      else if ((numTokens == 1 && tokens[0] == V_NW) ||
               (numTokens == 2 && tokens[0] == V_GO && tokens[1] == V_NW)) {
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
      else if ((numTokens == 1 && tokens[0] == V_NE) ||
               (numTokens == 2 && tokens[0] == V_GO && tokens[1] == V_NE)) {
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
      else if ((numTokens == 1 && tokens[0] == V_SW) ||
               (numTokens == 2 && tokens[0] == V_GO && tokens[1] == V_SW)) {
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
      else if ((numTokens == 1 && tokens[0] == V_SE) ||
               (numTokens == 2 && tokens[0] == V_GO && tokens[1] == V_SE)) {
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
      else if ((numTokens == 1 && tokens[0] == V_UP) ||
               (numTokens == 2 && tokens[0] == V_GO && tokens[1] == V_UP)) {
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
      else if ((numTokens == 1 && tokens[0] == V_DOWN) ||
               (numTokens == 2 && tokens[0] == V_GO && tokens[1] == V_DOWN)) {
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
/* ******************** GET ALL ********************** */
      else if (numTokens == 2 &&
               (tokens[0] == V_GET || tokens[0] == V_TAKE) &&
               tokens[1] == V_ALL) {
        i = 0;
        while (i < rooms[player.location]->numItems) {
          item = rooms[player.location]->items[i];
          if (item->weight >= 0) {
            j = putIntoInventory(item->number);
            if (j == -1) {
              printf("You cannot carry that item\n");
              i++;
              }
            if (j == -2) {
              printf("This item is too heavy to carry at this time.\n");
              i++;
              }
            if (j == -3) {
              printf("You cannot carry any more items.\n");
              i++;
              }
            if (j >= 0) {
              printf("  %s taken\n", item->description);
              for (j=i; j<rooms[player.location]->numItems-1; j++)
                rooms[player.location]->items[j] =
                rooms[player.location]->items[j+1];
              if (--rooms[player.location]->numItems == 0)
                free(rooms[player.location]->items);
              else rooms[player.location]->items = (ITEM**)realloc(
                rooms[player.location]->items,
                sizeof(ITEM*) * rooms[player.location]->numItems);
              }
            }
          else i++;
          }
        printf("\n");
        }
/* ******************** GET object ********************** */
      else if (numTokens == 2 && (tokens[0] == V_GET || tokens[0] == V_TAKE)) {
        j = tokens[1]-40000;
        if (j < 0) {
          printf("You must specify a valid item name\n");
          } else {
          if (getItem(j)) printf("Taken\n\n");
          }
        }
/* ******************** DROP object ********************* */
      else if (numTokens == 2 && (tokens[0] == V_PUT || tokens[0] == V_DROP)) {
        j = tokens[1]-40000;
        if (j < 0) {
          printf("You must specify a valid item name\n");
          }
        else if (items[j]->cursed != 0) {
          printf("Item cannot be dropped, it is cursed\n");
          }
        else if (items[j]->beingworn != 0) {
          printf("Item must be removed before it can be dropped\n");
          }
        else {
          if (dropItem(j)) printf("Dropped\n\n");
          }
        }
/* ******************* PUT object INTO container ******************* */
      else if (numTokens == 4 && tokens[0] == V_PUT &&
               (tokens[2] == V_INTO || tokens[2] == V_IN)) {
        a = tokens[1] - 40000;
        b = tokens[3] - 40000;
        if (a < 0) {
          printf("You must specify a valid item name\n");
          }
        else if (b < 0) {
          printf("You must specify a valid item name\n");
          }
        else if (carrying(a) == 0) {
          printf("You are not carrying the %s\n",items[a]->description);
          }
        else if (carrying(b) == 0) {
          printf("You are not carrying the %s\n",items[b]->description);
          }
        else if (items[b]->container == 0) {
          printf("%s is not a container\n", vocab[tokens[3]]);
          }
        else {
          takeFromInventory(a);
          putIntoContainer(b, a);
          printf("You place the %s into the %s\n",items[a]->description, items[b]->description);
          }
        }
/* ******************* TAKE object FROM container ******************* */
      else if (numTokens == 4 && (tokens[0] == V_GET || tokens[0] == V_TAKE) &&
               tokens[2] == V_FROM) {
        a = tokens[1] - 40000;
        b = tokens[3] - 40000;
        j = a;
        if (a < 0) {
          printf("You must specify a valid item name\n");
          }
        if (b < 0) {
          printf("You must specify a valid item name\n");
          }
        else if (items[b]->container == 0) {
          printf("%s is not a container\n", items[b]->description);
          }
        else {
          j = takeFromContainer(b, a);
          if (j < 0) {
            printf("The %s does not contain the %s\n",items[b]->description, items[a]->description);
            }
          else {
            putIntoInventory(a);
            printf("You take the %s out of the %s\n",items[a]->description, items[b]->description);
            }
          }
        }

/* **************************************************** */
/* ******************** OPEN door ********************* */
/* **************************************************** */
      else if (numTokens == 2 && tokens[0] == V_OPEN && tokens[1] == V_DOOR) {
        if (doorsInRoom(player.location,&j) == 1) {
          if (numTokens == 2 && tokens[1] == V_DOOR) {
            if (doors[j]->unlocked != 0) {
              if (doors[j]->opened == 0) {
                doors[j]->opened = 1;
                if (doors[j]->numOnOpenSteps > 0)
                  performAction(doors[j]->onOpenSteps,
                                doors[j]->numOnOpenSteps);
                printf("The door is now open.\n");
                } else {
                printf("The door is already open.\n");
                }
              } else {
              printf("The door is currently locked.\n");
              }
            }
          }
        else printf("You need to specify which door.\n");
        }

/* **************************************************** */
/* ******************** OPEN door ********************* */
/* **************************************************** */
      else if (numTokens == 3 && tokens[0] == V_OPEN && tokens[2] == V_DOOR &&
               (tokens[1] == V_NORTH || tokens[1] == V_N ||
                tokens[1] == V_SOUTH || tokens[1] == V_S || 
                tokens[1] == V_EAST || tokens[1] == V_E ||
                tokens[1] == V_WEST || tokens[1] == V_W || 
                tokens[1] == V_NE || tokens[1] == V_NW ||
                tokens[1] == V_SE || tokens[1] == V_SW)) {
        j = -1;
        room = player.location;
        if (tokens[1] == V_NORTH && rooms[room]->north[1] >= 0) j = rooms[room]->north[1];
        if (tokens[1] == V_N && rooms[room]->north[1] >= 0) j = rooms[room]->north[1];
        if (tokens[1] == V_SOUTH && rooms[room]->south[1] >= 0) j = rooms[room]->south[1];
        if (tokens[1] == V_S && rooms[room]->south[1] >= 0) j = rooms[room]->south[1];
        if (tokens[1] == V_EAST && rooms[room]->east[1] >= 0) j = rooms[room]->east[1];
        if (tokens[1] == V_E && rooms[room]->east[1] >= 0) j = rooms[room]->east[1];
        if (tokens[1] == V_WEST && rooms[room]->west[1] >= 0) j = rooms[room]->west[1];
        if (tokens[1] == V_W && rooms[room]->west[1] >= 0) j = rooms[room]->west[1];
        if (tokens[1] == V_NE && rooms[room]->ne[1] >= 0) j = rooms[room]->ne[1];
        if (tokens[1] == V_NW && rooms[room]->nw[1] >= 0) j = rooms[room]->nw[1];
        if (tokens[1] == V_SE && rooms[room]->se[1] >= 0) j = rooms[room]->se[1];
        if (tokens[1] == V_SW && rooms[room]->sw[1] >= 0) j = rooms[room]->sw[1];
        if (j >= 0) {
          if (doors[j]->unlocked != 0) {
            if (doors[j]->opened == 0) {
              doors[j]->opened = 1;
              if (doors[j]->numOnOpenSteps > 0)
                performAction(doors[j]->onOpenSteps,
                              doors[j]->numOnOpenSteps);
              printf("The door is now open.\n");
              } else {
              printf("The door is already open.\n");
              }
            } else {
            printf("The door is currently locked.\n");
            }
          }
        else printf("There is no door there.\n");
        }

/* ***************************************************** */
/* ******************** CLOSE door ********************* */
/* ***************************************************** */
      else if (tokens[0] == V_CLOSE && tokens[1] == V_DOOR) {
        if (doorsInRoom(player.location,&j) == 1) {
          if (numTokens == 2 && tokens[1] == V_DOOR) {
              if (doors[j]->opened != 0) {
                doors[j]->opened = 0;
                if (doors[j]->numOnCloseSteps > 0)
                  performAction(doors[j]->onCloseSteps,
                                doors[j]->numOnCloseSteps);
                printf("The door is now closed.\n");
                } else {
                printf("The door is already closed.\n");
                }
              }
            }
          else printf("You need to specify which door.\n");
          }

/* ***************************************************** */
/* ******************** CLOSE door ********************* */
/* ***************************************************** */
      else if (numTokens == 3 && tokens[0] == V_CLOSE && tokens[2] == V_DOOR &&
               (tokens[1] == V_NORTH || tokens[1] == V_N ||
                tokens[1] == V_SOUTH || tokens[1] == V_S ||
                tokens[1] == V_EAST || tokens[1] == V_E ||
                tokens[1] == V_WEST || tokens[1] == V_W ||
                tokens[1] == V_NE || tokens[1] == V_NW ||
                tokens[1] == V_SE || tokens[1] == V_SW)) {
        j = -1;
        room = player.location;
        if (tokens[1] == V_NORTH && rooms[room]->north[1] >= 0) j = rooms[room]->north[1];
        if (tokens[1] == V_N && rooms[room]->north[1] >= 0) j = rooms[room]->north[1];
        if (tokens[1] == V_SOUTH && rooms[room]->south[1] >= 0) j = rooms[room]->south[1];
        if (tokens[1] == V_S && rooms[room]->south[1] >= 0) j = rooms[room]->south[1];
        if (tokens[1] == V_EAST && rooms[room]->east[1] >= 0) j = rooms[room]->east[1];
        if (tokens[1] == V_E && rooms[room]->east[1] >= 0) j = rooms[room]->east[1];
        if (tokens[1] == V_WEST && rooms[room]->west[1] >= 0) j = rooms[room]->west[1];
        if (tokens[1] == V_W && rooms[room]->west[1] >= 0) j = rooms[room]->west[1];
        if (tokens[1] == V_NE && rooms[room]->ne[1] >= 0) j = rooms[room]->ne[1];
        if (tokens[1] == V_NW && rooms[room]->nw[1] >= 0) j = rooms[room]->nw[1];
        if (tokens[1] == V_SE && rooms[room]->se[1] >= 0) j = rooms[room]->se[1];
        if (tokens[1] == V_SW && rooms[room]->sw[1] >= 0) j = rooms[room]->sw[1];
        if (j >= 0) {
          if (doors[j]->opened != 0) {
            doors[j]->opened = 0;
            printf("The door is now closed.\n");
            } else {
            printf("The door is already closed.\n");
            }
          }
        else printf("There is no door there.\n");
        }

/* ****************************************************** */
/* ******************** UNLOCK door ********************* */
/* ****************************************************** */
      else if (numTokens == 2 && tokens[0] == V_UNLOCK && tokens[1] == V_DOOR) {
        if (doorsInRoom(player.location,&j) == 1) {
          if (numTokens == 2 && tokens[1] == V_DOOR) {
            if (doors[j]->unlocked != 0) {
              printf("The door is already unlocked.\n");
              } else {
              f = -1;
              for (i=0; i< player.numItems; i++) {
                if (player.items[i] == items[doors[j]->key]) f = i;
                }
              if (f >= 0) {
                doors[j]->unlocked = 1;
                if (doors[j]->numOnUnlockSteps > 0)
                  performAction(doors[j]->onUnlockSteps,
                                doors[j]->numOnUnlockSteps);
                printf("The door has been unlocked.\n");
                } else {
                printf("You do not have the key for that door.\n");
                }
              }
            }
          }
        else printf("You need to specify which door.\n");
        }

/* ****************************************************** */
/* ******************** UNLOCK door ********************* */
/* ****************************************************** */
      else if (numTokens == 3 && tokens[0] == V_UNLOCK && tokens[2] == V_DOOR &&
               (tokens[1] == V_NORTH || tokens[1] == V_N ||
                tokens[1] == V_SOUTH || tokens[1] == V_S ||
                tokens[1] == V_EAST || tokens[1] == V_E ||
                tokens[1] == V_WEST || tokens[1] == V_W ||
                tokens[1] == V_NE || tokens[1] == V_NW ||
                tokens[1] == V_SE || tokens[1] == V_SW)) {
        j = -1;
        room = player.location;
        if (tokens[1] == V_NORTH && rooms[room]->north[1] >= 0) j = rooms[room]->north[1];
        if (tokens[1] == V_N && rooms[room]->north[1] >= 0) j = rooms[room]->north[1];
        if (tokens[1] == V_SOUTH && rooms[room]->south[1] >= 0) j = rooms[room]->south[1];
        if (tokens[1] == V_S && rooms[room]->south[1] >= 0) j = rooms[room]->south[1];
        if (tokens[1] == V_EAST && rooms[room]->east[1] >= 0) j = rooms[room]->east[1];
        if (tokens[1] == V_E && rooms[room]->east[1] >= 0) j = rooms[room]->east[1];
        if (tokens[1] == V_WEST && rooms[room]->west[1] >= 0) j = rooms[room]->west[1];
        if (tokens[1] == V_W && rooms[room]->west[1] >= 0) j = rooms[room]->west[1];
        if (tokens[1] == V_NE && rooms[room]->ne[1] >= 0) j = rooms[room]->ne[1];
        if (tokens[1] == V_NW && rooms[room]->nw[1] >= 0) j = rooms[room]->nw[1];
        if (tokens[1] == V_SE && rooms[room]->se[1] >= 0) j = rooms[room]->se[1];
        if (tokens[1] == V_SW && rooms[room]->sw[1] >= 0) j = rooms[room]->sw[1];
        if (j >= 0) {
          if (doors[j]->unlocked != 0) {
            printf("The door is already unlocked.\n");
            } else {
            f = -1;
            for (i=0; i< player.numItems; i++) {
              if (player.items[i] == items[doors[j]->key]) f = i;
              }
            if (f >= 0) {
              doors[j]->unlocked = 1;
              if (doors[j]->numOnUnlockSteps > 0)
                performAction(doors[j]->onUnlockSteps,
                              doors[j]->numOnUnlockSteps);
              printf("The door has been unlocked.\n");
              } else {
              printf("You do not have the key for that door.\n");
              }
            }
          }
        else printf("There is no door there.\n");
        }

/* ****************************************************** */
/* ******************** LOCK door *********************** */
/* ****************************************************** */
      else if (numTokens == 2 && tokens[0] == V_LOCK && tokens[1] == V_DOOR) {
        if (doorsInRoom(player.location,&j) == 1) {
          if (numTokens == 2 && tokens[1] == V_DOOR) {
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
                doors[j]->unlocked = 0;
                if (doors[j]->numOnLockSteps > 0)
                  performAction(doors[j]->onLockSteps,
                                doors[j]->numOnLockSteps);
                printf("The door has been locked.\n");
                } else {
                printf("You do not have the key for that door.\n");
                }
              }
            }
          }
        else printf("You need to specify which door.\n");
        }

/* **************************************************** */
/* ******************** LOCK door ********************* */
/* **************************************************** */
      else if (numTokens == 3 && tokens[0] == V_LOCK && tokens[2] == V_DOOR &&
               (tokens[1] == V_NORTH || tokens[1] == V_N ||
                tokens[1] == V_SOUTH || tokens[1] == V_S ||
                tokens[1] == V_EAST || tokens[1] == V_E ||
                tokens[1] == V_WEST || tokens[1] == V_W ||
                tokens[1] == V_NE || tokens[1] == V_NW ||
                tokens[1] == V_SE || tokens[1] == V_SW)) {
        j = -1;
        room = player.location;
        if (tokens[1] == V_NORTH && rooms[room]->north[1] >= 0) j = rooms[room]->north[1];
        if (tokens[1] == V_N && rooms[room]->north[1] >= 0) j = rooms[room]->north[1];
        if (tokens[1] == V_SOUTH && rooms[room]->south[1] >= 0) j = rooms[room]->south[1];
        if (tokens[1] == V_S && rooms[room]->south[1] >= 0) j = rooms[room]->south[1];
        if (tokens[1] == V_EAST && rooms[room]->east[1] >= 0) j = rooms[room]->east[1];
        if (tokens[1] == V_E && rooms[room]->east[1] >= 0) j = rooms[room]->east[1];
        if (tokens[1] == V_WEST && rooms[room]->west[1] >= 0) j = rooms[room]->west[1];
        if (tokens[1] == V_W && rooms[room]->west[1] >= 0) j = rooms[room]->west[1];
        if (tokens[1] == V_NE && rooms[room]->ne[1] >= 0) j = rooms[room]->ne[1];
        if (tokens[1] == V_NW && rooms[room]->nw[1] >= 0) j = rooms[room]->nw[1];
        if (tokens[1] == V_SE && rooms[room]->se[1] >= 0) j = rooms[room]->se[1];
        if (tokens[1] == V_SW && rooms[room]->sw[1] >= 0) j = rooms[room]->sw[1];
        if (j >= 0) {
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
              doors[j]->unlocked = 0;
              if (doors[j]->numOnLockSteps > 0)
                performAction(doors[j]->onLockSteps,
                              doors[j]->numOnLockSteps);
              printf("The door has been locked.\n");
              } else {
              printf("You do not have the key for that door.\n");
              }
            }
          }
        else printf("There is no door there.\n");
        }

/* ********************************************************* */
/* ******************** EXAMINE object ********************* */
/* ********************************************************* */
      else if (numTokens == 2 && tokens[0] == V_EXAMINE) {
        if (tokens[1] < 40000 || tokens[1] >= 50000) {
          printf("You must specify a valid item name\n");
          }
        else {
          a = tokens[1] - 40000;
          j = -1;
  /* ***** Check for item in inventory ***** */
          for (i=0; i<player.numItems; i++)
            if (player.items[i] == items[a])
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
                  rooms[player.location]->items[i] == items[a])
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
        }
/* **************************************************** */
/* ******************** Wear item ********************* */
/* **************************************************** */
      else if (numTokens == 2 && tokens[0] == V_WEAR) {
        if (tokens[1] < 40000 || tokens[1] >= 50000) {
          printf("You must specify a valid item name\n");
          }
        else {
          a = tokens[1] - 40000;
          j = -1;
          for (i=0; i<player.numItems; i++)
            if (player.items[i] == items[a])
              j = i;
          if (j < 0) {
            printf("You are not carrying the ");
            printToken(tokens[1]);
            printf("\n");
            }
          if (j >=0 && player.items[j]->wearable == 0) {
            printf("The ");
            printToken(tokens[1]);
            printf(" is not wearable\n");
            j = -1;
            }
          if (j >= 0 && player.items[j]->beingworn != 0) {
            printf("The ");
            printToken(tokens[1]);
            printf(" is already being worn\n");
            j = -1;
            }
          if (j >= 0) {
            player.items[j]->beingworn = 1;
            if (player.items[j]->numWornSteps > 0)
              performAction(player.items[j]->wornSteps,
                            player.items[j]->numWornSteps);
            printf("You are now wearing the ");
            printToken(tokens[1]);
            printf("\n");

            }
          printf("\n");
          }
        }
/* ************************************************** */
/* ******************** Wearing ********************* */
/* ************************************************** */
      else if (numTokens == 1 && tokens[0] == V_WEARING) {
        printf("You are wearing:\n");
        for (i=0; i<player.numItems; i++)
          if (player.items[i]->beingworn)
            printf("  %s\n",player.items[j]->description);
        printf("\n");
        }
/* ****************************************************** */
/* ******************** Remove item ********************* */
/* ****************************************************** */
      else if (numTokens == 2 && tokens[0] == V_REMOVE) {
        if (tokens[1] < 40000 || tokens[1] >= 50000) {
          printf("You must specify a valid item name\n");
          }
        else {
          a = tokens[1] - 40000;
          j = -1;
          for (i=0; i<player.numItems; i++)
            if (player.items[i] == items[a])
              j = i;
          if (j < 0) {
            printf("You are not wearing the ");
            printToken(tokens[1]);
            printf("\n");
            }
          if (j >= 0 && player.items[j]->beingworn == 0) {
            printf("The ");
            printToken(tokens[1]);
            printf(" is not being worn\n");
            j = -1;
            }
          if (j >= 0 && player.items[j]->cursed != 0) {
            printf("The ");
            printToken(tokens[1]);
            printf(" is cursed and cannot be removed\n");
            j = -1;
            }
          if (j >= 0) {
            player.items[j]->beingworn = 0;
            if (player.items[j]->numRemovedSteps > 0)
              performAction(player.items[j]->removedSteps,
                            player.items[j]->numRemovedSteps);
            printf("You have removed the ");
            printToken(tokens[1]);
            printf("\n");
            }
          printf("\n");
          }
        }
      }
    }
  }
