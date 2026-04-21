#include <stdio.h>
#include <stdlib.h>

inline void panic(char *msg) {
  printf("Error: %s\n", msg);
  exit(1);
}
