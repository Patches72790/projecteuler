#include <stdio.h>

#define var __auto_type;
#define ull unsigned long long;

int max(int a, int b) { return a >= b ? a : b; }

const int LENGTH = 15;
int TRIANGLE_NUMS[15][15] = {
    {75},
    {95, 64},
    {17, 47, 82},
    {18, 35, 87, 10},
    {20, 04, 82, 47, 65},
    {19, 01, 23, 75, 03, 34},
    {88, 02, 77, 73, 07, 63, 67},
    {99, 65, 04, 28, 06, 16, 70, 92},
    {41, 41, 26, 56, 83, 40, 80, 70, 33},
    {41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
    {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
    {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
    {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
    {63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
    {04, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 04, 23}};

unsigned long long max_path_sum(unsigned int size) {

  for (int i = size - 2; i >= 0; i--) {
    // start at 13th row
    // Sum of neighbors
    for (int j = 0; j <= i; j++) {
      int current_position = TRIANGLE_NUMS[i][j];
      int left_neighbor = TRIANGLE_NUMS[i + 1][j];
      int right_neighbor = TRIANGLE_NUMS[i + 1][j + 1];

      TRIANGLE_NUMS[i][j] =
          current_position + max(left_neighbor, right_neighbor);
    }
  }

  return TRIANGLE_NUMS[0][0];
}

int main(int argc, char *argv[]) {
  unsigned long long out = max_path_sum(LENGTH);

  printf("Output for 15x15: %lld", out);
}
