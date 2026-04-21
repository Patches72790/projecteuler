#include <stdlib.h>

#define var __auto_type

unsigned long long collatz(unsigned long long n) {
  var current = n;
  var count = 1;

  if (current == 1)
    return count;

  while (current != 1) {
    if ((current & 2) == 0) {
      current = current / 2;
    } else {
      current = current * 3 + 1;
    }

    count += 1;
  }

  return count;
}

int main(int argc, char *argv[]) { return EXIT_SUCCESS; }
