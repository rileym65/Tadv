#include "header.h"

int getToken(char* buffer) {
  int i;
  for (i=0; i<numVocab; i++) {
    if (strcmp(upper(buffer),upper(vocab[i])) == 0) return i;
    }
  return -1;
  }


