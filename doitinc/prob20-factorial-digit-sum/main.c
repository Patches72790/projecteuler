#include "../lib/bigint.h"
#include <stdio.h>
#include <stdlib.h>

void factorial_digits_sum() {
  BigInt result = factorial(100);

  __auto_type digits = result.digits;

  // PrintBigInt(&result);

  int sum = 0;
  for (int i = 0; i < result.size; i++) {
    printf("%d\n", result.digits[i]);
    sum += result.digits[i];
  }

  printf("Sum of digits: %d\n", sum);
}

int main() { factorial_digits_sum(); }
