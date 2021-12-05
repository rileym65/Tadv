#include "header.h"

int prePass(char* filename) {
  int   i;
  FILE* inFile;
  int   roomCount;
  int   itemCount;
  int   doorCount;
  char buffer[1024];
  char name[256];
  char *pBuffer;
  char *pBuf;
  char  entity;
  int   pos;
  if (debug) printf("Executing pre-pass\n"); fflush(stdout);
  if ((inFile = fopen(filename,"r")) == NULL) {
    printf("Could not open file\n");
    return -1;
    }
  roomCount = -1;
  itemCount = -1;
  doorCount = -1;
  entity = ' ';
  while (fileRead(buffer,inFile) != NULL) {
    while (strlen(buffer) > 0 && buffer[strlen(buffer)-1] <= ' ')
      buffer[strlen(buffer)-1] = 0;
    pBuf = buffer;
    while (*pBuf == ' ') pBuf++;
    if (strncasecmp(pBuf,"room ",5) == 0) {
      pBuffer = pBuf+4;
      while (*pBuffer == ' ') pBuffer++;
      roomCount++;
      entity = 'R';
      }
    if (strncasecmp(pBuf,"item ",5) == 0) {
      pBuffer = pBuf+4;
      while (*pBuffer == ' ') pBuffer++;
      itemCount++;
      entity = 'I';
      }
    if (strncasecmp(pBuf,"door ",5) == 0) {
      pBuffer = pBuf+4;
      while (*pBuffer == ' ') pBuffer++;
      doorCount++;
      entity = 'D';
      }
    if (strncasecmp(pBuf,"name ",5) == 0) {
      pBuffer = pBuf+4;
      while (*pBuffer == ' ') pBuffer++;
      pos = 0;
      while (*pBuffer != 0 && *pBuffer != ' ') name[pos++] = *pBuffer++;
      name[pos] = 0;
      if (entity == 'R') addEquate(name, roomCount);
      if (entity == 'I') addEquate(name, itemCount);
      if (entity == 'D') addEquate(name, doorCount);
      }
    }
  fclose(inFile);
  if (debug) printf("Done with pre-pass\n"); fflush(stdout);
  }
