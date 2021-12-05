#include "header.h"

int actionBlock(int* actions,int count) {
  int k;
  int i;
  int j;
  int t;
  int ip;
  int a,b;
  int ifCount;
  float r;
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
           extract(k);
           }
         break;
    case CMD_PUT_INTO:
         a = pop();
         b = pop();
         extract(a);
         putIntoContainer(b, a);
         break;
    case CMD_TAKE_FROM:
         a = pop();
         b = pop();
         takeFromContainer(b, a);
         break;
    case CMD_CONTAINS:
         a = pop();
         b = pop();
         if (items[b]->container == 0) {
           push(0);
           }
         else {
           j = 0;
           for (i=0; i<items[b]->numContents; i++)
             if (items[b]->contents[i] == a) j = 1;
           push(j);
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
    case CMD_SPACE:
         printf(" ");
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
    case CMD_WHILE:
         j = stack[--sp];
         if (j == 0) {
           ip++;
           ifCount = 1;
           while (ip < count && actions[ip] != CMD_REPEAT && ifCount > 0) {
             if (actions[ip] == CMD_WHILE) ifCount++;
             if (actions[ip] == CMD_REPEAT) ifCount--;
             ip++;
             }
           } 
         else {
           doStack[dsp++] = ip-1;
           }
         break;
    case CMD_REPEAT:
         ip = doStack[--dsp];
         break;
    case CMD_BEGIN:
         doStack[dsp++] = ip-1;
         break;
    case CMD_UNTIL:
         j = stack[--sp];
         if (j != 0) ip = doStack[--dsp];
           else dsp--;
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
           r = rand();
           r /= RAND_MAX;
           r -= (int)r;
           r *= stack[sp-1];
           stack[sp-1] = (int)r;
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
    case CMD_L_AND:
         if (sp > 1) {
           stack[sp-2] = stack[sp-1] & stack[sp-2];
           sp--;
           }
         break;
    case CMD_L_OR:
         if (sp > 1) {
           stack[sp-2] = stack[sp-1] | stack[sp-2];
           sp--;
           }
         break;
    case CMD_L_XOR:
         if (sp > 1) {
           stack[sp-2] = stack[sp-1] ^ stack[sp-2];
           sp--;
           }
         break;
    case CMD_L_NOT:
         if (sp > 0) {
           stack[sp-1] = ~stack[sp-1];
           }
         break;
    case CMD_DUP:
         if (sp > 0) {
           stack[sp] = stack[sp-1];
           sp++;
           }
         break;
    case CMD_DUP2:
         if (sp > 1) {
           stack[sp] = stack[sp-2];
           stack[sp+1] = stack[sp-1];
           sp += 2;
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
    case CMD_SWAP2:
         if (sp > 3) {
           a = stack[sp-1]; b = stack[sp-2];
           stack[sp-1] = stack[sp-3]; stack[sp-2] = stack[sp-4];
           stack[sp-3] = a; stack[sp-4] = b;
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
         stack[sp++] = score();
         break;
    case CMD_WEIGHT:
         push(weight());
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
             printf("%s",items[k]->examine);
           }
         break;
    case CMD_DESC_ITEM:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numItems)
             printf("%s",items[k]->description);
           }
         break;
    case CMD_BLESS:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numItems)
             items[k]->cursed = 0;
           }
         break;
    case CMD_CURSE:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numItems)
             items[k]->cursed = 1;
           }
         break;
    case CMD_CURSED:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numItems)
             if (items[k]->cursed == 0) push(0); else push(1);
           }
         break;
    case CMD_ISCONTAINER:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numItems)
             if (items[k]->container != 0) push(1); else push(0);
           }
         break;
    case CMD_CONTENTS:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numItems)
             if (items[k]->container == 0) push(0);
             else {
               for (i=0; i<items[k]->numContents; i++)
                 push(items[k]->contents[i]);
               push(items[k]->numContents);
               }
           }
         break;
    case CMD_WEARABLE:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numItems)
             stack[sp++] = items[k]->wearable;
           }
         break;
    case CMD_WEARING:
         if (sp > 0) {
           k = stack[--sp];
           if (k >= 0 && k<numItems)
             stack[sp++] = items[k]->beingworn;
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
    case CMD_INVITEM:
         i = stack[--sp];
         j = -1;
         if (i >= player.numItems) {
           stack[sp++] = j;
           }
         else {
           stack[sp++] = numberForItem(player.items[i]);
           }
         break;
    case CMD_COUNT:
         stack[sp] = sp;
         sp++;
         break;
    case CMD_CLEAR:
         sp = 0;
         break;
    case CMD_NDOT:
         j = stack[--sp];
         for (i=0; i<j; i++)
           printf(" %d",stack[--sp]);
         break;
    case CMD_STACK:
         printf("[");
         for (i=0; i<sp; i++) {
           if (i != 0) printf(" ");
           printf("%d",stack[i]);
           }
         printf("]");
         break;
    case CMD_ABS:
         if (stack[sp-1] < 0) stack[sp-1] = -stack[sp-1];
         break;
    case CMD_SGN:
         if (stack[sp-1] < 0) stack[sp-1] = -1;
         else if (stack[sp-1] > 0) stack[sp-1] = 1;
         break;
    case CMD_INC:
         stack[sp-1]++;
         break;
    case CMD_DEC:
         stack[sp-1]--;
         break;
    case CMD_AUG:
         if (stack[sp-1] < 0) stack[sp-1]--;
         else if (stack[sp-1] > 0) stack[sp-1]++;
         break;
    case CMD_DIM:
         if (stack[sp-1] < 0) stack[sp-1]++;
         else if (stack[sp-1] > 0) stack[sp-1]--;
         break;
    case CMD_CHS:
         stack[sp-1] = -stack[sp-1];
         break;
    case CMD_MIN:
         a = stack[--sp];
         b = stack[--sp];
         if (a < b) stack[sp++] = a;
           else stack[sp++] = b;
         break;
    case CMD_MAX:
         a = stack[--sp];
         b = stack[--sp];
         if (a > b) stack[sp++] = a;
           else stack[sp++] = b;
         break;
    case CMD_NMIN:
         j = stack[--sp];
         for (i=0; i<j; i++) {
           a = stack[--sp];
           if (i == 0 || a < b) b = a;
           }
         stack[sp++] = b;
         break;
    case CMD_NMAX:
         j = stack[--sp];
         for (i=0; i<j; i++) {
           a = stack[--sp];
           if (i == 0 || a > b) b = a;
           }
         stack[sp++] = b;
         break;
    case CMD_NDROP:
         j = stack[--sp];
         sp -= j;
         if (sp < 0) sp = 0;
         break;
    case CMD_SUM:
         j = stack[--sp];
         a = 0;
         for (i=0; i<j; i++) {
           a += stack[--sp];
           }
         stack[sp++] = a;
         break;
    case CMD_DROPUNTIL:
         j = stack[--sp];
         a = -j;
         while (a != j && sp > 0) {
           a = stack[--sp];
           }
         break;
    case CMD_QMARK:
         printf("? ");
         fgets(more,255,stdin);
         push(atoi(more));
         break;
    case CMD_ITEMCOUNT:
         push(numItems);
         break;
    case CMD_S_DOT:
         j = pop();
         printf("%s",sVarValues[j]);
         break;
    case CMD_S_QMARK:
         j = pop();
         printf("? ");
         fgets(more,255,stdin);
         while (strlen(more) > 0 && more[strlen(more)-1] < ' ')
           more[strlen(more)-1] = 0;
         strcpy(sVarValues[j], more);
         break;
    case CMD_S_LEN:
         j = pop();
         push(strlen(sVarValues[j]));
         break;
    case CMD_S_LEFT:
         j = pop();
         b = pop();
         a = pop();
         strcpy(sVarValues[a], sVarValues[b]);
         if (strlen(sVarValues[b]) > j) {
           sVarValues[a][j] = 0;
           }
         break;
    case CMD_S_RIGHT:
         j = pop();
         b = pop();
         a = pop();
         if (strlen(sVarValues[b]) <= j) {
           strcpy(sVarValues[a], sVarValues[b]);
           }
         else {
           strcpy(sVarValues[a], sVarValues[b]+(strlen(sVarValues[b])-j));
           }
         break;
    case CMD_S_COPY:
         b = pop();
         a = pop();
         strcpy(sVarValues[a], sVarValues[b]);
         break;
    case CMD_S_PLUS:
         b = pop();
         a = pop();
         strcat(sVarValues[a], sVarValues[b]);
         break;
    case CMD_S_AT:
         a = pop();
         j = strlen(sVarValues[a]) - 1;
         push(0);
         while (j >= 0) {
           push(sVarValues[a][j]);
           j--;
           }
         break;
    case CMD_S_SET:
         a = pop();
         b = 99;
         j = 0;
         while (b != 0) {
           b = pop();
           more[j++] = b;
           }
         strcpy(sVarValues[a], more);
         break;
    case CMD_S_EQ:
         a = pop();
         b = pop();
         if (strcmp(sVarValues[a], sVarValues[b]) == 0) push(1);
           else push(0);
         break;
    case CMD_S_NE:
         a = pop();
         b = pop();
         if (strcmp(sVarValues[a], sVarValues[b]) == 0) push(0);
           else push(1);
         break;
    case CMD_S_GT:
         b = pop();
         a = pop();
         if (strcmp(sVarValues[a], sVarValues[b]) > 0) push(1);
           else push(0);
         break;
    case CMD_S_LT:
         b = pop();
         a = pop();
         if (strcmp(sVarValues[a], sVarValues[b]) < 0) push(1);
           else push(0);
         break;
    case CMD_S_LE:
         b = pop();
         a = pop();
         if (strcmp(sVarValues[a], sVarValues[b]) <= 0) push(1);
           else push(0);
         break;
    case CMD_S_GE:
         b = pop();
         a = pop();
         if (strcmp(sVarValues[a], sVarValues[b]) >= 0) push(1);
           else push(0);
         break;
    case CMD_S_CLEAR:
         a = pop();
         strcpy(sVarValues[a], "");
         break;
    case CMD_S_TRIM:
         a = pop();
         b = pop();
         i = 0;
         j = 0;
         while (sVarValues[a][i] > 0 && sVarValues[a][i] <= ' ') i++;
         while (sVarValues[a][i] != 0) more[j++] = sVarValues[a][i++];
         more[j] = 0;
         while (strlen(more) > 0 && more[strlen(more)-1] <= ' ')
           more[strlen(more)-1] = 0;
         strcpy(sVarValues[b], more);
         break;
    case CMD_S_LC:
         a = pop();
         b = pop();
         strcpy(more, sVarValues[a]);
         for (i=0; i<strlen(more); i++)
           if (more[i] >= 'A' && more[i] <= 'Z') more[i] += 32;
         strcpy(sVarValues[b], more);
         break;
    case CMD_S_UC:
         a = pop();
         b = pop();
         strcpy(more, sVarValues[a]);
         for (i=0; i<strlen(more); i++)
           if (more[i] >= 'a' && more[i] <= 'z') more[i] -= 32;
         strcpy(sVarValues[b], more);
         break;
    case CMD_S_VAL:
         a = pop();
         j = atoi(sVarValues[a]);
         push(j);
         break;
    case CMD_S_STR:
         j = pop();
         a = pop();
         sprintf(more,"%d",j);
         strcpy(sVarValues[a], more);
         break;
    case CMD_HEALTH:
         push(player.health);
         break;
    case CMD_HEALTH_PLUS:
         a = pop();
         player.health += a;
         break;
    case CMD_HEALTH_MINUS:
         a = pop();
         player.health -= a;
         break;
    case CMD_HEALTH_EQ:
         a = pop();
         player.health = a;
         break;
    case CMD_LINK_NORTH:
         if (sp > 1) {
           b = pop();
           a = pop();
           rooms[a]->north[0] = b;
           }
         break;
    case CMD_LINK_SOUTH:
         if (sp > 1) {
           b = pop();
           a = pop();
           rooms[a]->south[0] = b;
           }
         break;
    case CMD_LINK_EAST:
         if (sp > 1) {
           b = pop();
           a = pop();
           rooms[a]->east[0] = b;
           }
         break;
    case CMD_LINK_WEST:
         if (sp > 1) {
           b = pop();
           a = pop();
           rooms[a]->west[0] = b;
           }
         break;
    case CMD_LINK_NE:
         if (sp > 1) {
           b = pop();
           a = pop();
           rooms[a]->ne[0] = b;
           }
         break;
    case CMD_LINK_NW:
         if (sp > 1) {
           b = pop();
           a = pop();
           rooms[a]->nw[0] = b;
           }
         break;
    case CMD_LINK_SE:
         if (sp > 1) {
           b = pop();
           a = pop();
           rooms[a]->se[0] = b;
           }
         break;
    case CMD_LINK_SW:
         if (sp > 1) {
           b = pop();
           a = pop();
           rooms[a]->sw[0] = b;
           }
         break;
    case CMD_LINK_UP:
         if (sp > 1) {
           b = pop();
           a = pop();
           rooms[a]->up[0] = b;
           }
         break;
    case CMD_LINK_DOWN:
         if (sp > 1) {
           b = pop();
           a = pop();
           rooms[a]->down[0] = b;
           }
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
