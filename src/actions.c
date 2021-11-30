#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int dropItem(int itemNum) {
  int i;
  int j;
  j = -1;
  for (i=0; i<player.numItems; i++)
    if (player.items[i] == items[itemNum]) j = i;
  if (j == -1) {
    printf("Your are not carrying $s\n",items[itemNum]->name);
    return 0;
    }
  if (++rooms[player.location]->numItems == 1)
    rooms[player.location]->items = (ITEM**)malloc(sizeof(ITEM*));
  else
    rooms[player.location]->items = (ITEM**)realloc(
      rooms[player.location]->items,
      sizeof(ITEM*) * rooms[player.location]->numItems);
  rooms[player.location]->items[rooms[player.location]->numItems-1] =
    items[itemNum];
  player.score -= items[itemNum]->score;
  for (i=j; i<player.numItems-1; i++)
    player.items[i] = player.items[i+1];
  if (--player.numItems == 0) free(player.items);
    else player.items = (ITEM**)realloc(player.items,
      sizeof(ITEM*) * player.numItems);
  return -1;
  }

int getItem(int itemNum) {
  int i;
  int j;
  j = -1;
  for (i=0; i<rooms[player.location]->numItems; i++)
    if (rooms[player.location]->items[i] == items[itemNum]) j = i;
  if (j == -1) {
    printf("There is no %s here\n",items[itemNum]->name);
    return 0;
    }
  if (items[itemNum]->weight < 0) {
    printf("You cannot pick up this item\n");
    return 0;
    }
  if (++player.numItems == 1)
    player.items = (ITEM**)malloc(sizeof(ITEM*));
  else
    player.items = (ITEM**)realloc(player.items,
                   sizeof(ITEM*)*player.numItems);
  player.items[player.numItems-1] = items[itemNum];
  for (i=j; i<rooms[player.location]->numItems-1; i++)
    rooms[player.location]->items[i] =
    rooms[player.location]->items[i+1];
  if (--rooms[player.location]->numItems == 0)
    free(rooms[player.location]->items);
  else rooms[player.location]->items = (ITEM**)realloc(
    rooms[player.location]->items,
    sizeof(ITEM*) * rooms[player.location]->numItems);
  player.score += items[itemNum]->score;
  return -1;
  }

int removeItem(int itemNum,int roomNumber) {
  int i;
  int j;
  j = -1;
  for (i=0; i<rooms[roomNumber]->numItems; i++)
    if (rooms[roomNumber]->items[i] == items[itemNum]) j = i;
  if (j == -1) {
    return 0;
    }
  for (i=j; i<rooms[roomNumber]->numItems-1; i++)
    rooms[roomNumber]->items[i] =
    rooms[roomNumber]->items[i+1];
  if (--rooms[roomNumber]->numItems == 0)
    free(rooms[roomNumber]->items);
  else rooms[roomNumber]->items = (ITEM**)realloc(
    rooms[roomNumber]->items,
    sizeof(ITEM*) * rooms[roomNumber]->numItems);
  return -1;
  }

int actionBlock(int* actions,int count) {
  int k;
  int i;
  int j;
  int t;
  int ip;
  int ifCount;
  char flag;
  char more[256];
  ip = 0;
  flag = 1;
  while (flag) {
  if (actions[ip]>=40000) {
    actionBlock(functions[actions[ip]-40000]->actionTokens,
                functions[actions[ip]-40000]->numActionTokens);
    }
  else switch (actions[ip]) {
    case CMD_EXTRACT:
         if (sp > 0) {
           k = stack[--sp];
           for (i=0; i<numRooms; i++) removeItem(k,i);
           }
         break;
    case CMD_LOCATION:
         if (sp > 0) {
           k = stack[--sp];
           t = -1;
           for (i=0; i<numRooms; i++)
             for (j=0; j<rooms[i]->numItems; j++)
               if (rooms[i]->items[j] == items[k]) {
                 t = i;
                 }
           stack[sp++] = t;
           }
         break;
    case CMD_SPACES:
         if (sp > 0) {
           k = stack[--sp];
           for (i=0; i<k; i++) printf(" ");
           }
         break;
    case CMD_EMIT:
         if (sp > 0) {
           k = stack[--sp];
           printf("%c",k);
           }
         break;
    case CMD_NOT:
         if (sp > 0) {
           k = stack[--sp];
           k = (k == 0) ? 1 : 0;
           stack[sp++] = k;
           }
         break;
    case CMD_LIGHT:
         if (sp > 0) {
           k = stack[--sp];
           player.light = k;
           }
         break;
    case CMD_OPEN:
         if (sp > 0) {
           k = stack[--sp];
           if (k <= numDoors) {
             doors[k]->opened = 1;
             }
           }
         break;
    case CMD_CLOSE:
         if (sp > 0) {
           k = stack[--sp];
           if (k <= numDoors) {
             doors[k]->opened = 0;
             }
           }
         break;
    case CMD_OPENED:
         if (sp > 0) {
           k = stack[--sp];
           if (k <= numDoors) {
             stack[sp++] = (doors[k]->opened != 0) ? 1 : 0 ;
             }
           }
         break;
    case CMD_LOCK:
         if (sp > 0) {
           k = stack[--sp];
           if (k <= numDoors) {
             doors[k]->unlocked = 0;
             }
           }
         break;
    case CMD_UNLOCK:
         if (sp > 0) {
           k = stack[--sp];
           if (k <= numDoors) {
             doors[k]->unlocked = 1;
             }
           }
         break;
    case CMD_UNLOCKED:
         if (sp > 0) {
           k = stack[--sp];
           if (k <= numDoors) {
             stack[sp++] = (doors[k]->unlocked != 0) ? 1 : 0 ;
             }
           }
         break;
    case CMD_MORE:
         printf("-More-");
         fgets(more,255,stdin);
         break;
    case CMD_ROOM_DESC:
         for (i=0; i<rooms[player.location]->numDesc; i++)
            printf("%s\n",rooms[player.location]->description[i]);
         break;
    case CMD_DO:
         if (sp > 1) {
           doStack[dsp++] = ip;
           doStack[dsp++] = stack[sp-2];
           doStack[dsp++] = stack[sp-1];
           sp -= 2;
           }
         break;
    case CMD_I:
         if (dsp > 0) {
           stack[sp++] = doStack[dsp-1];
           }
         break;
    case CMD_LOOP:
         if (dsp > 0) {
           doStack[dsp-1]++;
           if (doStack[dsp-1] < doStack[dsp-2]) ip = doStack[dsp-3];
           }
         break;
    case CMD_IF:
         if (sp > 0) {
           if (stack[--sp] == 0) {
             ifCount = 0;
             ip++;
             while (ip < count && ((actions[ip] != CMD_ELSE &&
                                    actions[ip] != CMD_THEN) ||
                                   ifCount > 0)) {
               if (actions[ip] == CMD_IF) ifCount++;
               if (actions[ip] == CMD_THEN) ifCount--;
               ip++;
               }
             }
           }
         break;
    case CMD_ELSE:
         ifCount = 0;
         ip++;
         while (ip < count && (actions[ip] != CMD_THEN || ifCount > 0)) {
           if (actions[ip] == CMD_IF) ifCount++;
           if (actions[ip] == CMD_THEN) ifCount--;
           ip++;
           }
         break;
    case CMD_THEN:
         break;
    case CMD_PICK:
         if (sp > 1) {
           i = stack[sp-1];
           if (sp > i) stack[sp-1] = stack[sp-(1+i)]; 
           }
         break;
    case CMD_AND:
         if (sp > 1) {
           stack[sp-2] = (stack[sp-2] & stack[sp-1]) ? 1 : 0;
           sp--;
           }
         break;
    case CMD_OR:
         if (sp > 1) {
           stack[sp-2] = (stack[sp-2] | stack[sp-1]) ? 1 : 0;
           sp--;
           }
         break;
    case CMD_XOR:
         if (sp > 1) {
           stack[sp-2] = (stack[sp-2] ^ stack[sp-1]) ? 1 : 0;
           sp--;
           }
         break;
    case CMD_ROT:
         if (sp > 2) {
           i = stack[sp-3];
           stack[sp-3] = stack[sp-2];
           stack[sp-2] = stack[sp-1];
           stack[sp-1] = i;
           }
         break;
    case CMD_MROT:
         if (sp > 2) {
           i = stack[sp-1];
           stack[sp-1] = stack[sp-2];
           stack[sp-2] = stack[sp-3];
           stack[sp-3] = i;
           }
         break;
    case CMD_OVER:
         if (sp > 1) {
           stack[sp] = stack[sp-2];
           sp++;
           }
         break;
    case CMD_CURRENT_ROOM:
         stack[sp++] = player.location;
         break;
    case CMD_GOING_NORTH:
         stack[sp++] = (lastDir == 'N') ? 1 : 0;
         break;
    case CMD_GOING_SOUTH:
         stack[sp++] = (lastDir == 'S') ? 1 : 0;
         break;
    case CMD_GOING_EAST:
         stack[sp++] = (lastDir == 'E') ? 1 : 0;
         break;
    case CMD_GOING_WEST:
         stack[sp++] = (lastDir == 'W') ? 1 : 0;
         break;
    case CMD_GOING_UP:
         stack[sp++] = (lastDir == 'U') ? 1 : 0;
         break;
    case CMD_GOING_DOWN:
         stack[sp++] = (lastDir == 'D') ? 1 : 0;
         break;
    case CMD_ENTERED:
         if (sp > 0) {
           stack[sp-1] = (player.lastLocation == stack[sp-1]) ? 1 : 0;
           }
         break;
    case CMD_DOT:
         if (sp > 0) printf(" %d ",stack[--sp]);
         break;
    case CMD_CR:
         printf("\n");
         break;
    case CMD_RANDOM:
         if (sp > 0) {
           stack[sp-1] = rcs_random(stack[sp-1]);
           }
         break;
    case CMD_HAS_LIGHT:
         stack[sp++] = (player.light != 0) ? 1 : 0;
         break;
    case CMD_EQ:
         if (sp > 1) {
           stack[sp-2] = (stack[sp-2] == stack[sp-1]) ? 1 : 0;
           sp--;
           }
         break;
    case CMD_NE:
         if (sp > 1) {
           stack[sp-2] = (stack[sp-2] != stack[sp-1]) ? 1 : 0;
           sp--;
           }
         break;
    case CMD_GT:
         if (sp > 1) {
           stack[sp-2] = (stack[sp-2] > stack[sp-1]) ? 1 : 0;
           sp--;
           }
         break;
    case CMD_LT:
         if (sp > 1) {
           stack[sp-2] = (stack[sp-2] < stack[sp-1]) ? 1 : 0;
           sp--;
           }
         break;
    case CMD_GE:
         if (sp > 1) {
           stack[sp-2] = (stack[sp-2] >= stack[sp-1]) ? 1 : 0;
           sp--;
           }
         break;
    case CMD_LE:
         if (sp > 1) {
           stack[sp-2] = (stack[sp-2] <= stack[sp-1]) ? 1 : 0;
           sp--;
           }
         break;
    case CMD_SET:
         if (sp > 1) {
           vars[stack[sp-2]] = stack[sp-1];
           sp -= 2;
           }
         break;
    case CMD_GET:
         if (sp > 0) {
           stack[sp-1] = vars[stack[sp-1]];
           }
         break;
    case CMD_ADD:
         if (sp > 1) {
           stack[sp-2] = stack[sp-1] + stack[sp-2];
           sp--;
           }
         break;
    case CMD_SUB:
         if (sp > 1) {
           stack[sp-2] = stack[sp-2] - stack[sp-1];
           sp--;
           }
         break;
    case CMD_MUL:
         if (sp > 1) {
           stack[sp-2] = stack[sp-2] * stack[sp-1];
           sp--;
           }
         break;
    case CMD_DIV:
         if (sp > 1) {
           stack[sp-2] = stack[sp-2] / stack[sp-1];
           sp--;
           }
         break;
    case CMD_MOD:
         if (sp > 1) {
           stack[sp-2] = stack[sp-2] % stack[sp-1];
           sp--;
           }
         break;
    case CMD_DUP:
         if (sp > 0) {
           stack[sp] = stack[sp-1];
           sp++;
           }
         break;
    case CMD_DROP:
         if (sp > 0) sp--;
         break;
    case CMD_SWAP:
         if (sp > 1) {
           i = stack[sp - 2];
           stack[sp - 2] = stack[sp - 1];
           stack[sp - 1] = i;
           }
         break;
    case CMD_WIN:
         printf("Congratulations!!! You have won!!!\n");
         gameFlag = '*';
         break;
    case CMD_LOSE:
         printf("I am sorry, but you have lost!!!\n");
         gameFlag = '*';
         break;
    case CMD_DIE:
         printf("It appears that you have died\n");
         gameFlag = '*';
         break;
    case CMD_PLACE_OBJECT:
         if (sp > 0) {
           if (++rooms[player.location]->numItems == 1)
               rooms[player.location]->items = 
                    (ITEM**)malloc(sizeof(ITEM*));
           else
               rooms[player.location]->items =
                    (ITEM**)realloc(rooms[player.location]->items,
                     sizeof(ITEM*) * rooms[player.location]->numItems);
  rooms[player.location]->items[rooms[player.location]->numItems-1] =
    items[stack[--sp]];
           }
         break;
    case CMD_CARRYING:
         if (sp > 0) {
           sp--;
           k = 0;
           for (i=0; i<player.numItems; i++)
             if (player.items[i] == items[stack[sp]]) k = 1;
           stack[sp++] = k;
           }
         break;
    case CMD_NOT_CARRYING:
         if (sp > 0) {
           sp--;
           k = 1;
           for (i=0; i<player.numItems; i++)
             if (player.items[i] == items[stack[sp]]) k = 0;
           stack[sp++] = k;
           }
         break;
    case CMD_TAKE_OBJECT:
         if (sp > 0) getItem(stack[--sp]);
         break;
    case CMD_DROP_OBJECT:
         if (sp > 0) dropItem(stack[--sp]);
         break;
    case CMD_REMOVE_ITEM:
         if (sp > 0) removeItem(stack[--sp],player.location);
         break;
    case CMD_OBJECT_IN_ROOM:
         if (sp > 0) {
           k = 0;
           sp--;
           for (i=0; i<rooms[player.location]->numItems; i++)
             if (rooms[player.location]->items[i] ==
                 items[stack[sp]]) k = 1;
           stack[sp++] = k;
           }
         break;
    case CMD_OBJECT_NOT_IN_ROOM:
         if (sp > 0) {
           k = 1;
           sp--;
           for (i=0; i<rooms[player.location]->numItems; i++)
             if (rooms[player.location]->items[i] ==
                 items[stack[sp]]) k = 0;
           stack[sp++] = k;
           }
         break;
    case CMD_IN_ROOM:
         if (sp > 0 ) {
           k = (player.location == stack[--sp]) ? 1 : 0;
           stack[sp++] = k;
           }
         break;
    case CMD_NOT_IN_ROOM:
         if (sp > 0) {
           k = (player.location != stack[--sp]) ? 1 : 0;
           stack[sp++] = k;
           }
         break;
    case CMD_SAY:
         if (sp > 0 ) {
           --sp;
           for (k=0; k<messages[stack[sp]]->numLines; k++)
             printf("%s\n",messages[stack[sp]]->message[k]);
           }
         break;
    case CMD_NSAY:
         if (sp > 0 ) {
           --sp;
           for (k=0; k<messages[stack[sp]]->numLines; k++)
             printf("%s",messages[stack[sp]]->message[k]);
           }
         break;
    case CMD_TELEPORT:
         player.location = stack[--sp];
         break;
    case CMD_FLAG_SET:
         if (sp > 0) {
           k = (flags[stack[--sp]] == 0) ? 0 : 1;
           stack[sp++] = k;
           }
         break;
    case CMD_FLAG_RESET:
         if (sp > 0) {
           k = (flags[stack[--sp]] != 0) ? 0 : 1;
           stack[sp++] = k;
           }
         break;
    case CMD_SET_FLAG:
         if (sp > 0) flags[stack[--sp]] = 1;
         break;
    case CMD_RESET_FLAG:
         if (sp > 0) flags[stack[--sp]] = 0;
         break;
    case CMD_ADD_SCORE:
         if (sp > 0) player.score += stack[--sp];
         break;
    case CMD_SUB_SCORE:
         if (sp > 0) player.score -= stack[--sp];
         break;
    case CMD_TRUE:
         return ACTION_TRUE;
    case CMD_FALSE:
         return ACTION_FALSE;
    case CMD_SCORE:
         stack[sp++] = player.score;
         break;
    case CMD_WEIGHT:
         j = 0;
         for (i=0; i<player.numItems; i++)
         j += player.items[i]->weight;
         stack[sp++] = j;
         break;
    case CMD_GET_EAST:
         stack[sp++] = rooms[player.location]->east[0];
         break;
    case CMD_GET_WEST:
         stack[sp++] = rooms[player.location]->west[0];
         break;
    case CMD_GET_NORTH:
         stack[sp++] = rooms[player.location]->north[0];
         break;
    case CMD_GET_SOUTH:
         stack[sp++] = rooms[player.location]->south[0];
         break;
    case CMD_GET_UP:
         stack[sp++] = rooms[player.location]->down[0];
         break;
    case CMD_GET_DOWN:
         stack[sp++] = rooms[player.location]->up[0];
         break;
    case CMD_TURNCOUNT:
         stack[sp++] = player.turnCount;
         break;
    case CMD_EXAMINEITEM:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numItems)
             printf("%s\n",items[k]->examine);
           }
         break;
    case CMD_OPEN_DOOR:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numDoors)
             doors[k]->opened = 1;
           }
         break;
    case CMD_CLOSE_DOOR:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numDoors)
             doors[k]->opened = 0;
           }
         break;
    case CMD_LOCK_DOOR:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numDoors)
             doors[k]->unlocked = 0;
           }
         break;
    case CMD_UNLOCK_DOOR:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numDoors)
             doors[k]->unlocked = 1;
           }
         break;
    case CMD_DOOR_CLOSED:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numDoors)
             stack[sp++] = (doors[k]->opened) ? 0 : 1;
           }
         break;
    case CMD_DOOR_LOCKED:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numDoors)
             stack[sp++] = (doors[k]->unlocked) ? 0 : 1;
           }
         break;
    case CMD_INV_COUNT:
         stack[sp++] = player.numItems;
         break;
    default: 
         stack[sp++] = actions[ip];
         break;
    }
/*
    if (flag == 0) {
      while (ip < count && actions[ip] != CMD_ELSE) ip++;
      if (actions[ip] == CMD_ELSE) flag = 1;
      }
*/
    ip++;
    if (ip >= count) flag = 0;
    }
  }

int performAction(int* actions,int count) {
  sp = 0;
  dsp = 0;
  return actionBlock(actions,count);
  }

int checkActions() {
  int i;
  int j;
  int k;
  int ip;
  char flag;
  for (i=0; i<numActions; i++)
    if (actions[i]->numPhraseTokens == numTokens) {
      flag = 1;
      for (j=0; j<numTokens; j++) {
        if (tokens[j] != actions[i]->phraseTokens[j]) flag = 0;
        }
      if (flag) {
        k = performAction(actions[i]->actionTokens,
                          actions[i]->numActionTokens);
        if (k == 100) return 0;
        if (k == 101) return -1;
        }
      }
  return 0;
  }

int checkRoomActions() {
  ROOM* room;
  int i;
  int j;
  int k;
  int ip;
  char flag;
  room = rooms[player.location];
  for (i=0; i<room->numActions; i++)
    if (room->actions[i]->numPhraseTokens == numTokens) {
      flag = 1;
      for (j=0; j<numTokens; j++) {
        if (tokens[j] != room->actions[i]->phraseTokens[j]) flag = 0;
        }
      if (flag) {
        k = performAction(room->actions[i]->actionTokens,
                          room->actions[i]->numActionTokens);
        if (k == 100) return 0;
        if (k == 101) return -1;
        }
      }
  return 0;
  }

int checkObjects() {
  ROOM* room;
  int i;
  int j;
  int k;
  int r;
  char flag;
  if (numTokens < 2) return 0;
  for (i=0; i<player.numItems; i++) {
    if (strcasecmp(player.items[i]->name,vocab[tokens[numTokens-1]]) == 0) {
      for (j=0; j<player.items[i]->numActions; j++) {
        flag = 1;
        for (k=0; k<numTokens-1; k++)
          if (tokens[k] != player.items[i]->actions[j]->phraseTokens[k])
            flag = 0;
        if (flag) {
          r = performAction(player.items[i]->actions[j]->actionTokens,
                            player.items[i]->actions[j]->numActionTokens);
          if (r == 100) return 0;
          if (r == 101) return -1;
          }
        }
      }
    }
  room = rooms[player.location];
  for (i=0; i<room->numItems; i++)
    if (strcasecmp(room->items[i]->name,vocab[tokens[numTokens-1]]) == 0) {
      for (j=0; j<room->items[i]->numActions; j++) {
        flag = 1;
        for (k=0; k<numTokens-1; k++)
          if (tokens[k] != room->items[i]->actions[j]->phraseTokens[k])
            flag = 0;
        if (flag) {
          r = performAction(room->items[i]->actions[j]->actionTokens,
                            room->items[i]->actions[j]->numActionTokens);
          if (r == 100) return 0;
          if (r == 101) return -1;
          }
        }
      }
  return 0;
  }
