#include "header.h"

int* readActionSteps(FILE* inFile,int* count, char* pBuf) {
  int*    steps;
  char    flag;
  char*   pWrd;
  char    wrd[255];
  char    buf2[1024];
  char    arg;
  int     token;
  int i;
  int j;
  int ch;
  int c;
  *count = 0;
  flag = ' ';
  while (*pBuf != 0 && *pBuf != '{') pBuf++;
  if (*pBuf == '{') pBuf++;
  while (flag == ' ') {
    if (*pBuf == 0) {
      fileRead(buf2,inFile);
      pBuf = buf2;
      }
    while (*pBuf > 0 && *pBuf <= ' ') pBuf++;
    if (*pBuf == 0) {
      fileRead(buf2,inFile);
      pBuf = buf2;
      while (*pBuf > 0 && *pBuf <= ' ') pBuf++;
      }
    pWrd = wrd;
    if (*pBuf == '}') flag = '*';
      else {
      if (*pBuf == '"') {
        *pWrd++ = *pBuf++;
        while (*pBuf != 0 && *pBuf != '"') *pWrd++ = *pBuf++;
        *pWrd++ = '"';
        *pWrd = 0;
        if (*pBuf == '"') pBuf++;

        if ((*count += 1) == 1)
          steps = (int*)malloc(sizeof(int));
        else
          steps = (int*)realloc(steps,sizeof(int) * *count);
        steps[*count - 1] = CMD_QT;
        ch = 0;
        c = 4;
        for (j=1; j<strlen(wrd)-1; j++) {
          ch |= (wrd[j] << ((c-1)*8));
          c--;
          if (c == 0) {
            *count += 1;
            steps = (int*)realloc(steps,sizeof(int) * *count);
            steps[*count-1] = ch;
            ch = 0;
            c = 4;
            }
          }
        if (c != 4) {
          *count += 1;
          steps = (int*)realloc(steps,sizeof(int) * *count);
          steps[*count-1] = ch;
          }
        *count += 1;
        steps = (int*)realloc(steps,sizeof(int) * *count);
        steps[*count-1] = CMD_QT;
        }
      else {
        while (*pBuf > ' ' && *pBuf <=126) *pWrd++ = *pBuf++;
        *pWrd = 0;
        token = getCode(wrd);
        if (token == CMD_ERROR) {
          printf("Syntax error in file: %s\n",buf2);
          exit(1);
          }
        if ((*count += 1) == 1)
          steps = (int*)malloc(sizeof(int));
        else
          steps = (int*)realloc(steps,sizeof(int) * *count);
        steps[*count - 1] = token;
        }
      }
    }
  return steps;
  }

