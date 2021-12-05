#include "header.h"

void printToken(int token) {
  if (token >=40000 && token < 50000) printf("%s",items[token-40000]->description);
  else printf("%s",vocab[token]);
  }

