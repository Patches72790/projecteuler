#include "../lib/util.h"
#include <stdio.h>
#include <stdlib.h>

#define ull unsigned long long
#define uint unsigned int
#ifndef var
#define var __auto_type
#endif /* ifndef var */

const uint MAX_CACHE_SIZE = 1000000;
ull cache[MAX_CACHE_SIZE];

void init_cache() {
  for (int i = 0; i < MAX_CACHE_SIZE; i++) {
    cache[i] = 0;
  }
}

void store(ull n, uint length) {
  if (n < MAX_CACHE_SIZE)
    cache[n] = length;
}

ull check(unsigned long long n) { return (n < MAX_CACHE_SIZE) ? cache[n] : 0; }

ull collatz_tail_recursive(ull n, ull count) {
  if (n == 1)
    return count;

  if (n % 2 == 0)
    return collatz_tail_recursive(n / 2, count + 1);
  else
    return collatz_tail_recursive(3 * n + 1, count + 1);
}

ull collatz_memoize_recursive(ull n) {
  var found = check(n);
  if (found)
    return found;

  if (n == 1)
    return 1;

  var next_length =
      1 + collatz_memoize_recursive((n % 2 == 0 ? n / 2 : 3 * n + 1));

  store(n, next_length);

  return next_length;
}

ull collatz(unsigned long long n) {
  var current = n;
  var count = 1;

  if (current == 1)
    return count;

  while (current > 1) {
    // Check first
    var found = check(current);
    if (found > 0) {
      store(current, count + found);
      return count + found;
    }

    if ((current % 2) == 0) {
      current /= 2;
    } else {
      current = current * 3 + 1;
    }

    count++;
  }

  // Memoize count for n
  store(n, count);

  return count;
}

long long FindMaxCollatzUnderOneMillion() {
  var one_million = 1000000;
  var n = 1;
  var max = 1;
  var max_n = n;

  while (n < one_million) {
    var next = collatz_memoize_recursive(n);
    if (max < next) {
      max = next;
      max_n = n;
    }

    n++;
  }

  return max_n;
}

void TestCollatz(int count) {
  ull results[1000001];
  for (var i = 1; i <= count; i++) {
    results[i] = collatz_memoize_recursive(i);
  }

  for (var i = 1; i < 1000001; i++) {
    printf("Collatz(%d): [%lld]\n", i, results[i]);
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2)
    panic("Usage: collatz [n]");

  var count = atoi(argv[1]);

  init_cache();

  printf("Collatz for n = %d\n", count);

  TestCollatz(count);

  var max = FindMaxCollatzUnderOneMillion();

  printf("Max: %lld", max);
}
