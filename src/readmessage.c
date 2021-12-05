#include "header.h"

void readMessage(FILE* inFile,char* buf) {
  int number;
  char     flag;
  char*    pBuffer;
  MESSAGE* message;
  char buffer[1024];
  char msg[1024];
  int  pos;
  sscanf(buf,"%s %d",buffer,&number);
  if (number != numMessages) {
    printf("Message number mismatch: %d, %s\n",numMessages,buf);
    exit(1);
    }
  numMessages++;
  message = (MESSAGE*)malloc(sizeof(MESSAGE));
  message->numLines = 0;
  if (messages == NULL) {
    messages = (MESSAGE**)malloc(sizeof(MESSAGE*));
    messages[0] = message;
    }
  else {
    messages = (MESSAGE**)realloc(messages,sizeof(MESSAGE*) * numMessages);
    messages[numMessages - 1] = message;
    }
  while (*buf != 0 && *buf != '{') buf++;
  buf++;
  while (*buf > 0 && *buf <= ' ') buf++;
  flag = ' ';
  pos = 0;
  while (flag == ' ') {
    if (*buf == 0) {
      if (fileRead(buffer,inFile) == NULL) flag = '*';
      buf = buffer;
      pos = 0;
      while (*buf > 0 && *buf <= ' ') buf++;
      }
    while (*buf != 0 && *buf != '}') msg[pos++] = *buf++;
    msg[pos] = 0;
    if (++message->numLines == 1)
      message->message = (char**)malloc(sizeof(char*));
    else
      message->message = (char**)realloc(message->message,
        sizeof(char*) * message->numLines);
    message->message[message->numLines-1]=(char*)malloc(strlen(msg)+1);
      strcpy(message->message[message->numLines-1],msg);
    if (*buf == '}') flag = '*';
    }

  }

