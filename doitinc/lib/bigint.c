#include "bigint.h"
#include "stdio.h"
#include "util.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MakeBigInt(BigInt *n, char *num) {
  n->size = strlen(num);
  n->capacity = n->size;
  n->digits = malloc(sizeof(int) * n->capacity);

  if (n->digits == NULL) {
    panic("Error using malloc when initializing BigInt");
  }

  for (int i = 0; i < n->size; i++) {
    n->digits[i] = num[n->size - i - 1] - '0';
  }
}

BigInt add(BigInt *a, BigInt *b) {
  BigInt res;
  int max_s = (a->size > b->size ? a->size : b->size);
  res.digits = calloc(max_s + 1, sizeof(int));

  int carry = 0;

  for (int i = 0; i < max_s || carry; i++) {
    int val_a = (i < a->size ? a->digits[i] : 0);
    int val_b = (i < b->size ? b->digits[i] : 0);

    int sum = val_a + val_b + carry;
    res.digits[i] = sum % 10;
    carry = sum / 10;
    res.size = i + 1;
  }

  return res;
}

BigInt multiply(BigInt *a, BigInt *b) {
  BigInt res;
  int max_s = a->size + b->size;
  res.size = max_s;
  res.digits = calloc(max_s, sizeof(int));

  for (int i = 0; i < a->size; i++) {
    int carry = 0;
    for (int j = 0; j < b->size || carry; j++) {
      long long current =
          res.digits[i + j] +
          a->digits[i] * (long long)(j < b->size ? b->digits[j] : 0) + carry;

      res.digits[i + j] = current % 10;
      carry = current / 10;
    }
  }

  while (res.size > 1 && res.digits[res.size - 1] == 0) {
    res.size--;
  }

  return res;
}

// { 5, 2, 1 } Should print "521"
void PrintBigInt(BigInt *n) {
  for (int i = 0; i < n->size; i++) {
    int num = n->digits[n->size - i - 1];
    printf("%d", num);
  }
}

void DropBigInt(BigInt *first, ...) {
  va_list args;
  va_start(args, first);

  BigInt *current = first;

  while (current != NULL) {
    if (current->digits != NULL) {
      free(current->digits);
      current->digits = NULL;
    }
    current = va_arg(args, BigInt *);
  }

  va_end(args);
}
