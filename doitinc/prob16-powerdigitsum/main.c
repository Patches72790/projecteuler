#include "../lib/bigint.h"
#include "stdio.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long sum_digits(BigInt *b) {

  long long sum = 0;
  for (int i = 0; i < b->size; i++) {
    sum += b->digits[i];
  }

  return sum;
}

int main() {
  int power = 1000;
  BigInt two;
  BigInt res;

  MakeBigInt(&two, "2");
  MakeBigInt(&res, "1");

  for (int i = 0; i < power; i++) {
    res = multiply(&two, &res);
  }

  PrintBigInt(&res);

  printf("Sum of digits: %lld", sum_digits(&res));
}
