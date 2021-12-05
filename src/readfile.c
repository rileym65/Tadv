#include "header.h"

int readFile(char* filename) {
  FILE* inFile;
  char buffer[1024];
  if (prePass(filename) < 0) return -1;
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
  fclose(inFile);
  return 0;
  }

