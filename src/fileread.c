#include "header.h"

char* fileRead(char* buffer,FILE* file) {
  char* ret;
  char temp[1024];
  ret = fgets(buffer,1023,file);
  if (encrypted == 'Y' && ret != NULL) {
    decrypt(buffer,temp,&key);
    strcpy(buffer,temp);
    }
  while (strlen(buffer) > 0 && buffer[strlen(buffer)-1] <= ' ')
    buffer[strlen(buffer)-1] = 0;
  return ret;
  }

