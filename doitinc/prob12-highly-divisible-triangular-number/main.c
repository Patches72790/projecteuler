#include <stdio.h>
#include <stdlib.h>

int divides(unsigned a, unsigned b);
unsigned int divisors(unsigned int n);
unsigned int divisors_v2(long long n);

void PrintTriangularNumbers(int n, unsigned int howbig) {

  long long sum = 0;
  for (int i = 1; i < n; i++) {
    sum += i;
    unsigned int div = divisors_v2(sum);
    printf("%d: %lld", i, sum);
    printf(" -> divisors: %d\n", div);

    if (div > howbig)
      break;
  }
}

unsigned int divisors(unsigned int n) {

  int count = 1;

  for (int i = 2; i < n; i++) {
    if (divides(i, n))
      count++;
  }

  return count;
}

int divides(unsigned a, unsigned b) { return b % a == 0; }

unsigned int divisors_v2(long long n) {
  int count = 0;
  for (long long i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      if (i * i == n) {
        count += 1;
      } else {
        count += 2;
      }
    }
  }
  return count;
}

int main(int argc, char *argv[]) { PrintTriangularNumbers(1000000, 1000); }
