#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAIN
#include "header.h"

int main(int argc,char* argv[]) {
  int i;
  char filename[256];
  char encode;
  time_t t;
  printf("TADV %s\n",VERSION);
  debug = 0;
  encode = 0;
  numFunctions = 0;
  t = time(&t);
  t&=0xfffff;
  srand(t);
  for (i=0; i<1024; i++) flags[i] = 0;
  strcpy(filename,"");
  for (i=0; i<argc; i++) {
    if (strcmp(argv[i], "-c") == 0) encode = 1;
    else if (strcmp(argv[i], "-d") == 0) debug = 1;
    else strcpy(filename, argv[i]);
    }
  if (strlen(filename) == 0) {
    printf("Usage: adv adventure-file\n");
    printf("   or  adv -c adventure-file\n");
    return 0;
    }
  if (encode != 0) {
    encodeFile(filename);
    return 0;
    }
  init();
  if (strstr(filename,".sav") != NULL) {
    if (debug) printf("Loading save file\n"); fflush(stdout);
    load(filename);
    player.lastLocation = -1;
    } else {
    if (debug) printf("Loading adventure file\n"); fflush(stdout);
    readFile(filename);
    reset(); 
    }
  printf("\n\n");
  gameFlag = ' ';
  if (numStartSteps > 0) performAction(startSteps, numStartSteps);
  if (gameFlag == ' ') mainLoop();
  printf("You scored a total of %d points in %ld turns\n",player.score,player.turnCount);
  return 0;
  }
