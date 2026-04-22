#include "bigint.h"
#include "stdio.h"
#include "util.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GrowBigInt(BigInt *n) {
  int *digs = realloc(n->digits, n->capacity * 2 * sizeof(int));

  if (digs == NULL)
    panic("Error expanding BigInt size");

  // Update new digits
  n->digits = digs;
  n->capacity *= 2;
}

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

BigInt factorial(unsigned int n) {
  BigInt result;
  MakeBigInt(&result, "1");

  if (n <= 1) {
    return result;
  }

  for (unsigned int i = 2; i <= n; i++) {
    result = multiply_by_int(&result, i);
  }

  return result;
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

void SetToUint(BigInt *bi, unsigned int n) {
  for (int i = 0; i < bi->size; i++) {
    bi->digits[i] = 0;
  }

  // TODO!
  bi->digits[0] = n;
  bi->size = 1;
}

void mult_by_int_inplace(BigInt *result, int n) {
  unsigned long long carry = 0;
  for (int i = 0; i < result->size || carry > 0; i++) {
    // if reached capacity
    if (i == result->capacity) {
      GrowBigInt(result);
    }

    int current_digit = (i < result->size ? result->digits[i] : 0);
    unsigned long long product = (unsigned long long)current_digit * n + carry;

    result->digits[i] = product % 10;
    carry = product / 10;
    result->size = i + 1;
  }
}

void factorial_inplace(BigInt *a, unsigned int n) {
  SetToUint(a, 1);

  for (int i = 2; i <= n; i++) {
    mult_by_int_inplace(a, i);
  }
}

BigInt multiply_by_int(BigInt *a, int n) {
  char str[32];
  sprintf(str, "%d", n);
  BigInt b;
  MakeBigInt(&b, str);

  return multiply(a, &b);
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
