#include "header.h"

int pop() {
  if (sp == 0) {
    printf("--Stack Empty--\n");
    exit(1);
    }
  return stack[--sp];
  }

