#include "header.h"

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

