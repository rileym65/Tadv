#include "header.h"

int showStack() {
  int i;
  char buffer[1024];
  char tmp[32];
  strcpy(buffer,"[");
  for (i=0; i<sp; i++) {
    if (i != 0) strcat(buffer, " ");
    sprintf(tmp,"%d",stack[i]);
    strcat(buffer,tmp);
    }
  strcat(buffer,"]");
  printf("%s",buffer);
  return strlen(buffer);
  }

int actionBlock(int* actions,int count) {
  int k;
  int i;
  int j;
  int t;
  int ip;
  int a,b;
  int pad;
  int ifCount;
  float r;
  char flag;
  char more[256];
  pad = 15;
  ip = 0;
  flag = 1;
  while (flag) {
  if (actions[ip]>=40000) {
    actionBlock(functions[actions[ip]-40000]->actionTokens,
                functions[actions[ip]-40000]->numActionTokens);
    }
  else {
    if (tron == 1) {
      i = showStack();
      while (i<15) {
        printf(" ");
        i++;
        }
      printf("  ");
      }
    switch (actions[ip]) {
      case CMD_QT:
           ip++;
           while (actions[ip] != CMD_QT) {
             if ((actions[ip] & 0xff000000) != 0)
               printf("%c",(actions[ip] >> 24) & 0xff);
             if ((actions[ip] & 0x00ff0000) != 0)
               printf("%c",(actions[ip] >> 16) & 0xff);
             if ((actions[ip] & 0x0000ff00) != 0)
               printf("%c",(actions[ip] >> 8) & 0xff);
             if ((actions[ip] & 0x000000ff) != 0)
               printf("%c",actions[ip] & 0xff);
             ip++;
             }
           break;
      case CMD_EXTRACT:
           if (tron == 1) printf("%-*s",pad,"extract");
           if (sp > 0) {
             k = stack[--sp];
             extract(k);
             }
           break;
      case CMD_PUT_INTO:
           if (tron == 1) printf("%-*s",pad,"putinto");
           a = pop();
           b = pop();
           extract(a);
           putIntoContainer(b, a);
           break;
      case CMD_TAKE_FROM:
           if (tron == 1) printf("%-*s",pad,"takefrom");
           a = pop();
           b = pop();
           takeFromContainer(b, a);
           break;
      case CMD_CONTAINS:
           if (tron == 1) printf("%-*s",pad,"contains?");
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
           if (tron == 1) printf("%-*s",pad,"location");
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
           if (tron == 1) printf("%-*s",pad,"spaces");
           if (sp > 0) {
             k = stack[--sp];
             for (i=0; i<k; i++) printf(" ");
             }
           break;
      case CMD_SPACE:
           if (tron == 1) printf("%-*s",pad,"space");
           printf(" ");
           break;
      case CMD_EMIT:
           if (tron == 1) printf("%-*s",pad,"emit");
           if (sp > 0) {
             k = stack[--sp];
             printf("%c",k);
             }
           break;
      case CMD_NOT:
           if (tron == 1) printf("%-*s",pad,"not");
           if (sp > 0) {
             k = stack[--sp];
             k = (k == 0) ? 1 : 0;
             stack[sp++] = k;
             }
           break;
      case CMD_LIGHT:
           if (tron == 1) printf("%-*s",pad,"light");
           if (sp > 0) {
             k = stack[--sp];
             player.light = k;
             }
           break;
      case CMD_OPEN:
           if (tron == 1) printf("%-*s",pad,"open");
           if (sp > 0) {
             k = stack[--sp];
             if (k <= numDoors) {
               doors[k]->opened = 1;
               }
             }
           break;
      case CMD_CLOSE:
           if (tron == 1) printf("%-*s",pad,"close");
           if (sp > 0) {
             k = stack[--sp];
             if (k <= numDoors) {
               doors[k]->opened = 0;
               }
             }
           break;
      case CMD_OPENED:
           if (tron == 1) printf("%-*s",pad,"opened?");
           if (sp > 0) {
             k = stack[--sp];
             if (k <= numDoors) {
               stack[sp++] = (doors[k]->opened != 0) ? 1 : 0 ;
               }
             }
           break;
      case CMD_LOCK:
           if (tron == 1) printf("%-*s",pad,"lock");
           if (sp > 0) {
             k = stack[--sp];
             if (k <= numDoors) {
               doors[k]->unlocked = 0;
               }
             }
           break;
      case CMD_UNLOCK:
           if (tron == 1) printf("%-*s",pad,"unlock");
           if (sp > 0) {
             k = stack[--sp];
             if (k <= numDoors) {
               doors[k]->unlocked = 1;
               }
             }
           break;
      case CMD_UNLOCKED:
           if (tron == 1) printf("%-*s",pad,"unlocked?");
           if (sp > 0) {
             k = stack[--sp];
             if (k <= numDoors) {
               stack[sp++] = (doors[k]->unlocked != 0) ? 1 : 0 ;
               }
             }
           break;
      case CMD_MORE:
           if (tron == 1) printf("%-*s",pad,"more");
           printf("-More-");
           fgets(more,255,stdin);
           break;
      case CMD_ROOM_DESC:
           if (tron == 1) printf("%-*s",pad,"roomdesc");
           for (i=0; i<rooms[player.location]->numDesc; i++)
              printf("%s\n",rooms[player.location]->description[i]);
           break;
      case CMD_DO:
           if (tron == 1) printf("%-*s",pad,"do");
           if (sp > 1) {
             doStack[dsp++] = ip;
             doStack[dsp++] = stack[sp-2];
             doStack[dsp++] = stack[sp-1];
             sp -= 2;
             }
           break;
      case CMD_I:
           if (tron == 1) printf("%-*s",pad,"i");
           if (dsp > 0) {
             stack[sp++] = doStack[dsp-1];
             }
           break;
      case CMD_LOOP:
           if (tron == 1) printf("%-*s",pad,"loop");
           if (dsp > 0) {
             doStack[dsp-1]++;
             if (doStack[dsp-1] < doStack[dsp-2]) ip = doStack[dsp-3];
             }
           break;
      case CMD_IF:
           if (tron == 1) strcpy(more,"if");
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
               if (tron == 1 && actions[ip] == CMD_ELSE) strcat(more," else");
               if (tron == 1 && actions[ip] == CMD_THEN) strcat(more," then");
               }
             }
           if (tron == 1) printf("%-*s",pad,more);
           break;
      case CMD_ELSE:
           if (tron == 1) strcpy(more,"else");
           ifCount = 0;
           ip++;
           while (ip < count && (actions[ip] != CMD_THEN || ifCount > 0)) {
             if (actions[ip] == CMD_IF) ifCount++;
             if (actions[ip] == CMD_THEN) ifCount--;
             ip++;
             }
           if (tron == 1 && actions[ip] == CMD_THEN) strcat(more," then");
           if (tron == 1) printf("%-*s",pad,more);
           break;
      case CMD_THEN:
           if (tron == 1) printf("%-*s",pad,"then");
           break;
      case CMD_WHILE:
           if (tron == 1) printf("%-*s",pad,"while");
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
           if (tron == 1) printf("%-*s",pad,"repeat");
           ip = doStack[--dsp];
           break;
      case CMD_BEGIN:
           if (tron == 1) printf("%-*s",pad,"begin");
           doStack[dsp++] = ip-1;
           break;
      case CMD_UNTIL:
           if (tron == 1) printf("%-*s",pad,"until");
           j = stack[--sp];
           if (j != 0) ip = doStack[--dsp];
             else dsp--;
           break;
      case CMD_PICK:
           if (tron == 1) printf("%-*s",pad,"pick");
           if (sp > 1) {
             i = stack[sp-1];
             if (sp > i) stack[sp-1] = stack[sp-(1+i)]; 
             }
           break;
      case CMD_AND:
           if (tron == 1) printf("%-*s",pad,"and");
           if (sp > 1) {
             stack[sp-2] = (stack[sp-2] & stack[sp-1]) ? 1 : 0;
             sp--;
             }
           break;
      case CMD_OR:
           if (tron == 1) printf("%-*s",pad,"or");
           if (sp > 1) {
             stack[sp-2] = (stack[sp-2] | stack[sp-1]) ? 1 : 0;
             sp--;
             }
           break;
      case CMD_XOR:
           if (tron == 1) printf("%-*s",pad,"xor");
           if (sp > 1) {
             stack[sp-2] = (stack[sp-2] ^ stack[sp-1]) ? 1 : 0;
             sp--;
             }
           break;
      case CMD_ROT:
           if (tron == 1) printf("%-*s",pad,"rot");
           if (sp > 2) {
             i = stack[sp-3];
             stack[sp-3] = stack[sp-2];
             stack[sp-2] = stack[sp-1];
             stack[sp-1] = i;
             }
           break;
      case CMD_MROT:
           if (tron == 1) printf("%-*s",pad,"-rot");
           if (sp > 2) {
             i = stack[sp-1];
             stack[sp-1] = stack[sp-2];
             stack[sp-2] = stack[sp-3];
             stack[sp-3] = i;
             }
           break;
      case CMD_OVER:
           if (tron == 1) printf("%-*s",pad,"over");
           if (sp > 1) {
             stack[sp] = stack[sp-2];
             sp++;
             }
           break;
      case CMD_CURRENT_ROOM:
           if (tron == 1) printf("%-*s",pad,"currentroom");
           stack[sp++] = player.location;
           break;
      case CMD_GOING_NORTH:
           if (tron == 1) printf("%-*s",pad,"goingnorth?");
           stack[sp++] = (lastDir == 'N') ? 1 : 0;
           break;
      case CMD_GOING_SOUTH:
           if (tron == 1) printf("%-*s",pad,"goingsouth?");
           stack[sp++] = (lastDir == 'S') ? 1 : 0;
           break;
      case CMD_GOING_EAST:
           if (tron == 1) printf("%-*s",pad,"goingeast?");
           stack[sp++] = (lastDir == 'E') ? 1 : 0;
           break;
      case CMD_GOING_WEST:
           if (tron == 1) printf("%-*s",pad,"goingwest?");
           stack[sp++] = (lastDir == 'W') ? 1 : 0;
           break;
      case CMD_GOING_UP:
           if (tron == 1) printf("%-*s",pad,"goingup?");
           stack[sp++] = (lastDir == 'U') ? 1 : 0;
           break;
      case CMD_GOING_DOWN:
           if (tron == 1) printf("%-*s",pad,"goingdown?");
           stack[sp++] = (lastDir == 'D') ? 1 : 0;
           break;
      case CMD_ENTERED:
           if (tron == 1) printf("%-*s",pad,"enteredfrom?");
           if (sp > 0) {
             stack[sp-1] = (player.lastLocation == stack[sp-1]) ? 1 : 0;
             }
           break;
      case CMD_DOT:
           if (tron == 1) strcpy(more,".");
           if (sp > 0) {
             if (tron == 1) sprintf(more, ".         %d",stack[--sp]);
             else printf(" %d ",stack[--sp]);
             }
           if (tron == 1) printf("%-*s",pad,more);
           break;
      case CMD_CR:
           if (tron == 1) printf("%-*s",pad,"cr");
           printf("\n");
           break;
      case CMD_RANDOM:
           if (tron == 1) printf("%-*s",pad,"random");
           if (sp > 0) {
             r = rand();
             r /= RAND_MAX;
             r -= (int)r;
             r *= stack[sp-1];
             stack[sp-1] = (int)r;
             }
           break;
      case CMD_HAS_LIGHT:
           if (tron == 1) printf("%-*s",pad,"light?");
           stack[sp++] = (player.light != 0) ? 1 : 0;
           break;
      case CMD_EQ:
           if (tron == 1) printf("%-*s",pad,"=");
           if (sp > 1) {
             stack[sp-2] = (stack[sp-2] == stack[sp-1]) ? 1 : 0;
             sp--;
             }
           break;
      case CMD_NE:
           if (tron == 1) printf("%-*s",pad,"<>");
           if (sp > 1) {
             stack[sp-2] = (stack[sp-2] != stack[sp-1]) ? 1 : 0;
             sp--;
             }
           break;
      case CMD_GT:
           if (tron == 1) printf("%-*s",pad,">");
           if (sp > 1) {
             stack[sp-2] = (stack[sp-2] > stack[sp-1]) ? 1 : 0;
             sp--;
             }
           break;
      case CMD_LT:
           if (tron == 1) printf("%-*s",pad,"<");
           if (sp > 1) {
             stack[sp-2] = (stack[sp-2] < stack[sp-1]) ? 1 : 0;
             sp--;
             }
           break;
      case CMD_GE:
           if (tron == 1) printf("%-*s",pad,">=");
           if (sp > 1) {
             stack[sp-2] = (stack[sp-2] >= stack[sp-1]) ? 1 : 0;
             sp--;
             }
           break;
      case CMD_LE:
           if (tron == 1) printf("%-*s",pad,"<=");
           if (sp > 1) {
             stack[sp-2] = (stack[sp-2] <= stack[sp-1]) ? 1 : 0;
             sp--;
             }
           break;
      case CMD_SET:
           if (tron == 1) printf("%-*s",pad,"!");
           if (sp > 1) {
             vars[stack[sp-2]] = stack[sp-1];
             sp -= 2;
             }
           break;
      case CMD_GET:
           if (tron == 1) printf("%-*s",pad,"@");
           if (sp > 0) {
             stack[sp-1] = vars[stack[sp-1]];
             }
           break;
      case CMD_ADD:
           if (tron == 1) printf("%-*s",pad,"+");
           if (sp > 1) {
             stack[sp-2] = stack[sp-1] + stack[sp-2];
             sp--;
             }
           break;
      case CMD_SUB:
           if (tron == 1) printf("%-*s",pad,"-");
           if (sp > 1) {
             stack[sp-2] = stack[sp-2] - stack[sp-1];
             sp--;
             }
           break;
      case CMD_MUL:
           if (tron == 1) printf("%-*s",pad,"*");
           if (sp > 1) {
             stack[sp-2] = stack[sp-2] * stack[sp-1];
             sp--;
             }
           break;
      case CMD_DIV:
           if (tron == 1) printf("%-*s",pad,"/");
           if (sp > 1) {
             stack[sp-2] = stack[sp-2] / stack[sp-1];
             sp--;
             }
           break;
      case CMD_MOD:
           if (tron == 1) printf("%-*s",pad,"mod");
           if (sp > 1) {
             stack[sp-2] = stack[sp-2] % stack[sp-1];
             sp--;
             }
           break;
      case CMD_L_AND:
           if (tron == 1) printf("%-*s",pad,"&");
           if (sp > 1) {
             stack[sp-2] = stack[sp-1] & stack[sp-2];
             sp--;
             }
           break;
      case CMD_L_OR:
           if (tron == 1) printf("%-*s",pad,"|");
           if (sp > 1) {
             stack[sp-2] = stack[sp-1] | stack[sp-2];
             sp--;
             }
           break;
      case CMD_L_XOR:
           if (tron == 1) printf("%-*s",pad,"^");
           if (sp > 1) {
             stack[sp-2] = stack[sp-1] ^ stack[sp-2];
             sp--;
             }
           break;
      case CMD_L_NOT:
           if (tron == 1) printf("%-*s",pad,"~");
           if (sp > 0) {
             stack[sp-1] = ~stack[sp-1];
             }
           break;
      case CMD_DUP:
           if (tron == 1) printf("%-*s",pad,"dup");
           if (sp > 0) {
             stack[sp] = stack[sp-1];
             sp++;
             }
           break;
      case CMD_DUPQ:
           if (tron == 1) printf("%-*s",pad,"dup?");
           if (sp > 0) {
             if (stack[sp-1] != 0) {
               stack[sp] = stack[sp-1];
               sp++;
               }
             }
           break;
      case CMD_DUP2:
           if (tron == 1) printf("%-*s",pad,"dup2");
           if (sp > 1) {
             stack[sp] = stack[sp-2];
             stack[sp+1] = stack[sp-1];
             sp += 2;
             }
           break;
      case CMD_DROP:
           if (tron == 1) printf("%-*s",pad,"drop");
           if (sp > 0) sp--;
           break;
      case CMD_SWAP:
           if (tron == 1) printf("%-*s",pad,"swap");
           if (sp > 1) {
             i = stack[sp - 2];
             stack[sp - 2] = stack[sp - 1];
             stack[sp - 1] = i;
             }
           break;
      case CMD_SWAP2:
           if (tron == 1) printf("%-*s",pad,"swap2");
           if (sp > 3) {
             a = stack[sp-1]; b = stack[sp-2];
             stack[sp-1] = stack[sp-3]; stack[sp-2] = stack[sp-4];
             stack[sp-3] = a; stack[sp-4] = b;
             }
           break;
      case CMD_WIN:
           if (tron == 1) printf("%-*s",pad,"win");
           printf("Congratulations!!! You have won!!!\n");
           gameFlag = '*';
           break;
      case CMD_LOSE:
           if (tron == 1) printf("%-*s",pad,"lose");
           printf("I am sorry, but you have lost!!!\n");
           gameFlag = '*';
           break;
      case CMD_DIE:
           if (tron == 1) printf("%-*s",pad,"die");
           printf("It appears that you have died\n");
           gameFlag = '*';
           break;
      case CMD_PLACE_OBJECT:
           if (tron == 1) printf("%-*s",pad,"placeitem");
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
           if (tron == 1) printf("%-*s",pad,"carrying?");
           if (sp > 0) {
             k = pop();
             k = carrying(k);
             if (k) push(1); else push(0);
             }
           break;
      case CMD_NOT_CARRYING:
           if (tron == 1) printf("%-*s",pad,"notcarrying?");
           if (sp > 0) {
             k = pop();
             k = carrying(k);
             if (k) push(0); else push(1);
             }
           break;
      case CMD_TAKE_OBJECT:
           if (tron == 1) printf("%-*s",pad,"takeitem");
           if (sp > 0) getItem(stack[--sp]);
           break;
      case CMD_DROP_OBJECT:
           if (tron == 1) printf("%-*s",pad,"dropitem");
           if (sp > 0) dropItem(stack[--sp]);
           break;
      case CMD_REMOVE_ITEM:
           if (tron == 1) printf("%-*s",pad,"removeitem");
           if (sp > 0) removeItem(stack[--sp],player.location);
           break;
      case CMD_OBJECT_IN_ROOM:
           if (tron == 1) printf("%-*s",pad,"iteminroom?");
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
           if (tron == 1) printf("%-*s",pad,"itemnotinroom?");
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
           if (tron == 1) printf("%-*s",pad,"inroom?");
           if (sp > 0 ) {
             k = (player.location == stack[--sp]) ? 1 : 0;
             stack[sp++] = k;
             }
           break;
      case CMD_NOT_IN_ROOM:
           if (tron == 1) printf("%-*s",pad,"notinroom?");
           if (sp > 0) {
             k = (player.location != stack[--sp]) ? 1 : 0;
             stack[sp++] = k;
             }
           break;
      case CMD_SAY:
           if (tron == 1) printf("%-*s",pad,"say");
           if (sp > 0 ) {
             --sp;
             for (k=0; k<messages[stack[sp]]->numLines; k++)
               printf("%s\n",messages[stack[sp]]->message[k]);
             }
           break;
      case CMD_NSAY:
           if (tron == 1) printf("%-*s",pad,"nsay");
           if (sp > 0 ) {
             --sp;
             for (k=0; k<messages[stack[sp]]->numLines; k++)
               printf("%s",messages[stack[sp]]->message[k]);
             }
           break;
      case CMD_TELEPORT:
           if (tron == 1) printf("%-*s",pad,"teleport");
           player.location = stack[--sp];
           break;
      case CMD_FLAG_SET:
           if (tron == 1) printf("%-*s",pad,"flagset?");
           if (sp > 0) {
             k = (flags[stack[--sp]] == 0) ? 0 : 1;
             stack[sp++] = k;
             }
           break;
      case CMD_FLAG_RESET:
           if (tron == 1) printf("%-*s",pad,"flagreset?");
           if (sp > 0) {
             k = (flags[stack[--sp]] != 0) ? 0 : 1;
             stack[sp++] = k;
             }
           break;
      case CMD_SET_FLAG:
           if (tron == 1) printf("%-*s",pad,"setflag");
           if (sp > 0) flags[stack[--sp]] = 1;
           break;
      case CMD_RESET_FLAG:
           if (tron == 1) printf("%-*s",pad,"resetflag");
           if (sp > 0) flags[stack[--sp]] = 0;
           break;
      case CMD_ADD_SCORE:
           if (tron == 1) printf("%-*s",pad,"addscore");
           if (sp > 0) player.score += stack[--sp];
           break;
      case CMD_SUB_SCORE:
           if (tron == 1) printf("%-*s",pad,"subscore");
           if (sp > 0) player.score -= stack[--sp];
           break;
      case CMD_TRUE:
           if (tron == 1) printf("%-*s",pad,"true");
           return ACTION_TRUE;
      case CMD_FALSE:
           if (tron == 1) printf("%-*s",pad,"false");
           return ACTION_FALSE;
      case CMD_SCORE:
           if (tron == 1) printf("%-*s",pad,"score");
           stack[sp++] = score();
           break;
      case CMD_WEIGHT:
           if (tron == 1) printf("%-*s",pad,"weight");
           push(weight());
           break;
      case CMD_GET_EAST:
           if (tron == 1) printf("%-*s",pad,"geteast");
           stack[sp++] = rooms[player.location]->east[0];
           break;
      case CMD_GET_WEST:
           if (tron == 1) printf("%-*s",pad,"getwest");
           stack[sp++] = rooms[player.location]->west[0];
           break;
      case CMD_GET_NORTH:
           if (tron == 1) printf("%-*s",pad,"getnorth");
           stack[sp++] = rooms[player.location]->north[0];
           break;
      case CMD_GET_SOUTH:
           if (tron == 1) printf("%-*s",pad,"getsouth");
           stack[sp++] = rooms[player.location]->south[0];
           break;
      case CMD_GET_UP:
           if (tron == 1) printf("%-*s",pad,"getup");
           stack[sp++] = rooms[player.location]->down[0];
           break;
      case CMD_GET_DOWN:
           if (tron == 1) printf("%-*s",pad,"getdown");
           stack[sp++] = rooms[player.location]->up[0];
           break;
      case CMD_TURNCOUNT:
           if (tron == 1) printf("%-*s",pad,"turncount");
           stack[sp++] = player.turnCount;
           break;
      case CMD_EXAMINEITEM:
           if (tron == 1) printf("%-*s",pad,"examineitem");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numItems)
               printf("%s",items[k]->examine);
             }
           break;
      case CMD_DESC_ITEM:
           if (tron == 1) printf("%-*s",pad,"describeitem");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numItems)
               printf("%s",items[k]->description);
             }
           break;
      case CMD_BLESS:
           if (tron == 1) printf("%-*s",pad,"bless");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numItems)
               items[k]->cursed = 0;
             }
           break;
      case CMD_CURSE:
           if (tron == 1) printf("%-*s",pad,"curse");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numItems)
               items[k]->cursed = 1;
             }
           break;
      case CMD_CURSED:
           if (tron == 1) printf("%-*s",pad,"cursed?");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numItems)
               if (items[k]->cursed == 0) push(0); else push(1);
             }
           break;
      case CMD_ISCONTAINER:
           if (tron == 1) printf("%-*s",pad,"container?");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numItems)
               if (items[k]->container != 0) push(1); else push(0);
             }
           break;
      case CMD_CONTENTS:
           if (tron == 1) printf("%-*s",pad,"contents");
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
           if (tron == 1) printf("%-*s",pad,"wearable?");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numItems)
               stack[sp++] = items[k]->wearable;
             }
           break;
      case CMD_WEARING:
           if (tron == 1) printf("%-*s",pad,"wearing?");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numItems)
               stack[sp++] = items[k]->beingworn;
             }
           break;
      case CMD_OPEN_DOOR:
           if (tron == 1) printf("%-*s",pad,"opendoor");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numDoors)
               doors[k]->opened = 1;
             }
           break;
      case CMD_CLOSE_DOOR:
           if (tron == 1) printf("%-*s",pad,"closedoor");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numDoors)
               doors[k]->opened = 0;
             }
           break;
      case CMD_LOCK_DOOR:
           if (tron == 1) printf("%-*s",pad,"lockdoor");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numDoors)
               doors[k]->unlocked = 0;
             }
           break;
      case CMD_UNLOCK_DOOR:
           if (tron == 1) printf("%-*s",pad,"unlockdoor");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numDoors)
               doors[k]->unlocked = 1;
             }
           break;
      case CMD_DOOR_CLOSED:
           if (tron == 1) printf("%-*s",pad,"doorclosed?");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numDoors)
               stack[sp++] = (doors[k]->opened) ? 0 : 1;
             }
           break;
      case CMD_DOOR_LOCKED:
           if (tron == 1) printf("%-*s",pad,"doorlocked?");
           if (sp > 0) {
             k = stack[--sp];
             if (k >= 0 && k<numDoors)
               stack[sp++] = (doors[k]->unlocked) ? 0 : 1;
             }
           break;
      case CMD_INV_COUNT:
           if (tron == 1) printf("%-*s",pad,"invcount");
           stack[sp++] = player.numItems;
           break;
      case CMD_INVITEM:
           if (tron == 1) printf("%-*s",pad,"invitem");
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
           if (tron == 1) printf("%-*s",pad,"count");
           stack[sp] = sp;
           sp++;
           break;
      case CMD_CLEAR:
           if (tron == 1) printf("%-*s",pad,"clear");
           sp = 0;
           break;
      case CMD_NDOT:
           if (tron == 1) printf("%-*s",pad,"n.");
           j = stack[--sp];
           for (i=0; i<j; i++)
             printf(" %d",stack[--sp]);
           break;
      case CMD_STACK:
           if (tron == 1) printf("%-*s",pad,"stack");
           showStack();
           break;
      case CMD_ABS:
           if (tron == 1) printf("%-*s",pad,"abs");
           if (stack[sp-1] < 0) stack[sp-1] = -stack[sp-1];
           break;
      case CMD_SGN:
           if (tron == 1) printf("%-*s",pad,"sgn");
           if (stack[sp-1] < 0) stack[sp-1] = -1;
           else if (stack[sp-1] > 0) stack[sp-1] = 1;
           break;
      case CMD_INC:
           if (tron == 1) printf("%-*s",pad,"inc");
           stack[sp-1]++;
           break;
      case CMD_DEC:
           if (tron == 1) printf("%-*s",pad,"dec");
           stack[sp-1]--;
           break;
      case CMD_AUG:
           if (tron == 1) printf("%-*s",pad,"aug");
           if (stack[sp-1] < 0) stack[sp-1]--;
           else if (stack[sp-1] > 0) stack[sp-1]++;
           break;
      case CMD_DIM:
           if (tron == 1) printf("%-*s",pad,"dim");
           if (stack[sp-1] < 0) stack[sp-1]++;
           else if (stack[sp-1] > 0) stack[sp-1]--;
           break;
      case CMD_CHS:
           if (tron == 1) printf("%-*s",pad,"chs");
           stack[sp-1] = -stack[sp-1];
           break;
      case CMD_MIN:
           if (tron == 1) printf("%-*s",pad,"min");
           a = stack[--sp];
           b = stack[--sp];
           if (a < b) stack[sp++] = a;
             else stack[sp++] = b;
           break;
      case CMD_MAX:
           if (tron == 1) printf("%-*s",pad,"max");
           a = stack[--sp];
           b = stack[--sp];
           if (a > b) stack[sp++] = a;
             else stack[sp++] = b;
           break;
      case CMD_NMIN:
           if (tron == 1) printf("%-*s",pad,"nmin");
           j = stack[--sp];
           for (i=0; i<j; i++) {
             a = stack[--sp];
             if (i == 0 || a < b) b = a;
             }
           stack[sp++] = b;
           break;
      case CMD_NMAX:
           if (tron == 1) printf("%-*s",pad,"nmax");
           j = stack[--sp];
           for (i=0; i<j; i++) {
             a = stack[--sp];
             if (i == 0 || a > b) b = a;
             }
           stack[sp++] = b;
           break;
      case CMD_NDROP:
           if (tron == 1) printf("%-*s",pad,"ndrop");
           j = stack[--sp];
           sp -= j;
           if (sp < 0) sp = 0;
           break;
      case CMD_SUM:
           if (tron == 1) printf("%-*s",pad,"sum");
           j = stack[--sp];
           a = 0;
           for (i=0; i<j; i++) {
             a += stack[--sp];
             }
           stack[sp++] = a;
           break;
      case CMD_DROPUNTIL:
           if (tron == 1) printf("%-*s",pad,"dropuntil");
           j = stack[--sp];
           a = -j;
           while (a != j && sp > 0) {
             a = stack[--sp];
             }
           break;
      case CMD_QMARK:
           if (tron == 1) printf("%-*s",pad,"?");
           printf("? ");
           fgets(more,255,stdin);
           push(atoi(more));
           break;
      case CMD_ITEMCOUNT:
           if (tron == 1) printf("%-*s",pad,"itemcount");
           push(numItems);
           break;
      case CMD_S_DOT:
           if (tron == 1) printf("%-*s",pad,"s.");
           j = pop();
           printf("%s",sVarValues[j]);
           break;
      case CMD_S_QMARK:
           if (tron == 1) printf("%-*s",pad,"s?");
           j = pop();
           printf("? ");
           fgets(more,255,stdin);
           while (strlen(more) > 0 && more[strlen(more)-1] < ' ')
             more[strlen(more)-1] = 0;
           strcpy(sVarValues[j], more);
           break;
      case CMD_S_LEN:
           if (tron == 1) printf("%-*s",pad,"slen");
           j = pop();
           push(strlen(sVarValues[j]));
           break;
      case CMD_S_LEFT:
           if (tron == 1) printf("%-*s",pad,"sleft");
           j = pop();
           b = pop();
           a = pop();
           strcpy(sVarValues[a], sVarValues[b]);
           if (strlen(sVarValues[b]) > j) {
             sVarValues[a][j] = 0;
             }
           break;
      case CMD_S_RIGHT:
           if (tron == 1) printf("%-*s",pad,"sright");
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
           if (tron == 1) printf("%-*s",pad,"scopy");
           b = pop();
           a = pop();
           strcpy(sVarValues[a], sVarValues[b]);
           break;
      case CMD_S_PLUS:
           if (tron == 1) printf("%-*s",pad,"s+");
           b = pop();
           a = pop();
           strcat(sVarValues[a], sVarValues[b]);
           break;
      case CMD_S_AT:
           if (tron == 1) printf("%-*s",pad,"s@");
           a = pop();
           j = strlen(sVarValues[a]) - 1;
           push(0);
           while (j >= 0) {
             push(sVarValues[a][j]);
             j--;
             }
           break;
      case CMD_S_SET:
           if (tron == 1) printf("%-*s",pad,"s!");
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
           if (tron == 1) printf("%-*s",pad,"s=");
           a = pop();
           b = pop();
           if (strcasecmp(sVarValues[a], sVarValues[b]) == 0) push(1);
             else push(0);
           break;
      case CMD_S_NE:
           if (tron == 1) printf("%-*s",pad,"s<>");
           a = pop();
           b = pop();
           if (strcasecmp(sVarValues[a], sVarValues[b]) == 0) push(0);
             else push(1);
           break;
      case CMD_S_GT:
           if (tron == 1) printf("%-*s",pad,"s>");
           b = pop();
           a = pop();
           if (strcasecmp(sVarValues[a], sVarValues[b]) > 0) push(1);
             else push(0);
           break;
      case CMD_S_LT:
           if (tron == 1) printf("%-*s",pad,"s<");
           b = pop();
           a = pop();
           if (strcasecmp(sVarValues[a], sVarValues[b]) < 0) push(1);
             else push(0);
           break;
      case CMD_S_LE:
           if (tron == 1) printf("%-*s",pad,"s<=");
           b = pop();
           a = pop();
           if (strcasecmp(sVarValues[a], sVarValues[b]) <= 0) push(1);
             else push(0);
           break;
      case CMD_S_GE:
           if (tron == 1) printf("%-*s",pad,"s>=");
           b = pop();
           a = pop();
           if (strcasecmp(sVarValues[a], sVarValues[b]) >= 0) push(1);
             else push(0);
           break;
      case CMD_S_CLEAR:
           if (tron == 1) printf("%-*s",pad,"sclear");
           a = pop();
           strcpy(sVarValues[a], "");
           break;
      case CMD_S_TRIM:
           if (tron == 1) printf("%-*s",pad,"strim");
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
           if (tron == 1) printf("%-*s",pad,"slc");
           a = pop();
           b = pop();
           strcpy(more, sVarValues[a]);
           for (i=0; i<strlen(more); i++)
             if (more[i] >= 'A' && more[i] <= 'Z') more[i] += 32;
           strcpy(sVarValues[b], more);
           break;
      case CMD_S_UC:
           if (tron == 1) printf("%-*s",pad,"suc");
           a = pop();
           b = pop();
           strcpy(more, sVarValues[a]);
           for (i=0; i<strlen(more); i++)
             if (more[i] >= 'a' && more[i] <= 'z') more[i] -= 32;
           strcpy(sVarValues[b], more);
           break;
      case CMD_S_VAL:
           if (tron == 1) printf("%-*s",pad,"sval");
           a = pop();
           j = atoi(sVarValues[a]);
           push(j);
           break;
      case CMD_S_STR:
           if (tron == 1) printf("%-*s",pad,"sstr");
           j = pop();
           a = pop();
           sprintf(more,"%d",j);
           strcpy(sVarValues[a], more);
           break;
      case CMD_HEALTH:
           if (tron == 1) printf("%-*s",pad,"health");
           push(player.health);
           break;
      case CMD_HEALTH_PLUS:
           if (tron == 1) printf("%-*s",pad,"health+");
           a = pop();
           player.health += a;
           break;
      case CMD_HEALTH_MINUS:
           if (tron == 1) printf("%-*s",pad,"health-");
           a = pop();
           player.health -= a;
           break;
      case CMD_HEALTH_EQ:
           if (tron == 1) printf("%-*s",pad,"health=");
           a = pop();
           player.health = a;
           break;
      case CMD_LINK_NORTH:
           if (tron == 1) printf("%-*s",pad,"linknorth");
           if (sp > 1) {
             b = pop();
             a = pop();
             rooms[a]->north[0] = b;
             }
           break;
      case CMD_LINK_SOUTH:
           if (tron == 1) printf("%-*s",pad,"linksouth");
           if (sp > 1) {
             b = pop();
             a = pop();
             rooms[a]->south[0] = b;
             }
           break;
      case CMD_LINK_EAST:
           if (tron == 1) printf("%-*s",pad,"linkeast");
           if (sp > 1) {
             b = pop();
             a = pop();
             rooms[a]->east[0] = b;
             }
           break;
      case CMD_LINK_WEST:
           if (tron == 1) printf("%-*s",pad,"linkwest");
           if (sp > 1) {
             b = pop();
             a = pop();
             rooms[a]->west[0] = b;
             }
           break;
      case CMD_LINK_NE:
           if (tron == 1) printf("%-*s",pad,"linkne");
           if (sp > 1) {
             b = pop();
             a = pop();
             rooms[a]->ne[0] = b;
             }
           break;
      case CMD_LINK_NW:
           if (tron == 1) printf("%-*s",pad,"linknw");
           if (sp > 1) {
             b = pop();
             a = pop();
             rooms[a]->nw[0] = b;
             }
           break;
      case CMD_LINK_SE:
           if (tron == 1) printf("%-*s",pad,"linkse");
           if (sp > 1) {
             b = pop();
             a = pop();
             rooms[a]->se[0] = b;
             }
           break;
      case CMD_LINK_SW:
           if (tron == 1) printf("%-*s",pad,"linksw");
           if (sp > 1) {
             b = pop();
             a = pop();
             rooms[a]->sw[0] = b;
             }
           break;
      case CMD_LINK_UP:
           if (tron == 1) printf("%-*s",pad,"linkup");
           if (sp > 1) {
             b = pop();
             a = pop();
             rooms[a]->up[0] = b;
             }
           break;
      case CMD_LINK_DOWN:
           if (tron == 1) printf("%-*s",pad,"linkdown");
           if (sp > 1) {
             b = pop();
             a = pop();
             rooms[a]->down[0] = b;
             }
           break;
      case CMD_AT_EQ:
           if (tron == 1) printf("%-*s",pad,"@=");
           if (sp > 1) {
             a = pop();
             b = pop();
             if (vars[b] == a) push(1); else push(0);
             }
           break;
      case CMD_AT_PLUSPLUS:
           if (tron == 1) printf("%-*s",pad,"@++");
           if (sp > 0) {
             a = pop();
             vars[a]++;
             }
           break;
      case CMD_AT_MINUSMINUS:
           if (tron == 1) printf("%-*s",pad,"@--");
           if (sp > 0) {
             a = pop();
             vars[a]--;
             }
           break;
      case CMD_AT_PLUS_EQ:
           if (tron == 1) printf("%-*s",pad,"@+=");
           if (sp > 1) {
             a = pop();
             b = pop();
             vars[b] += a;
             }
           break;
      case CMD_AT_MINUS_EQ:
           if (tron == 1) printf("%-*s",pad,"@-=");
           if (sp > 1) {
             a = pop();
             b = pop();
             vars[b] -= a;
             }
           break;
      case CMD_AT_DOT:
           if (tron == 1) printf("%-*s",pad,"@.");
           if (sp > 0) {
             a = pop();
             printf(" %d ",vars[a]);
             }
           break;
      case CMD_LT_LT:
           if (tron == 1) printf("%-*s",pad,"<<");
           if (sp > 1) {
             stack[sp-2] = stack[sp-2] << stack[sp-1];
             sp--;
             }
           break;
      case CMD_GT_GT:
           if (tron == 1) printf("%-*s",pad,">>");
           if (sp > 1) {
             stack[sp-2] = stack[sp-2] >> stack[sp-1];
             sp--;
             }
           break;
      case CMD_TRON:
           if (tron == 1) printf("%-*s",pad,"tron");
           if (tracing != 0) tron = 1;
           break;
      case CMD_TROFF:
           if (tron == 1) printf("%-*s",pad,"troff");
           tron = 0;
           break;
      case CMD_NIP:
           if (tron == 1) printf("%-*s",pad,"nip");
           a = pop();
           b = pop();
           push(a);
           break;
      case CMD_TUCK:
           if (tron == 1) printf("%-*s",pad,"tuck");
           a = pop();
           b = pop();
           push(a); push(b); push(a);
           break;
      case CMD_INVENTORY:
           if (tron == 1) printf("%-*s",pad,"inventory");
           for (i=0; i<player.numItems; i++)
             push(player.items[i]->number);
           push(player.numItems);
           break;
      default: 
           if (tron == 1) printf("%-*d",pad,actions[ip]);
           stack[sp++] = actions[ip];
           break;
      }
    if (tron == 1) {
      printf("  ");
      showStack();
      printf("\n");
      }
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
