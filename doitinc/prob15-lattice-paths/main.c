#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define auto __auto_type
#define ull unsigned long long

const unsigned int MAX_SIZE = 25;
ull cache[MAX_SIZE][MAX_SIZE];

void intialize_cache() {
  for (int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++) {
      cache[i][j] = 0;
    }
  }
}

void debug(int i, int j) { printf("Path(%d, %d)\n", i, j); }

ull find_paths_dynamic() {
  // Size must be (n+1)x(n+1)
  auto SIZE = 21;
  ull graph[SIZE][SIZE];

  // edge points have path length 1
  for (int i = 0; i < SIZE; i++) {
    graph[SIZE - 1][i] = 1;
    graph[i][SIZE - 1] = 1;
  }

  for (int i = SIZE - 2; i >= 0; i--) {
    for (int j = SIZE - 2; j >= 0; j--) {
      graph[i][j] = graph[i + 1][j] + graph[i][j + 1];
    }
  }

  return graph[0][0];
}

ull find_paths(int i, int j, int max_row, int max_col) {
  if (cache[i][j] != 0)
    return cache[i][j];

  if (i == max_row && j == max_col) {
    return 1;
  }

  if (i == max_row || j == max_col) {
    return 1;
  }

  auto right_paths = find_paths(i, j + 1, max_row, max_col);
  auto down_paths = find_paths(i + 1, j, max_row, max_col);

  cache[i][j] = down_paths + right_paths;

  return down_paths + right_paths;
}

int main() {
  intialize_cache();
  auto start1 = clock();
  auto paths = find_paths(0, 0, 20, 20);
  auto end1 = clock();
  auto time1 = ((double)end1 - start1) / CLOCKS_PER_SEC;

  auto start2 = clock();
  auto bottom_up_paths = find_paths_dynamic();
  auto end2 = clock();
  auto time2 = ((double)end2 - start2) / CLOCKS_PER_SEC;

  printf("1st Time=(%f), Result=%lld\n", time1, paths);

  printf("2nd Time=(%f), Result=%lld\n", time2, bottom_up_paths);
}
