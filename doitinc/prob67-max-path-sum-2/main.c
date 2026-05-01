#include <stdio.h>
#include <stdlib.h>

#define LENGTH 100
int **TRIANGLE;

int max(int a, int b) { return a >= b ? a : b; }

void initialize_triangle() {
  TRIANGLE = (int **)calloc(LENGTH, sizeof(int *));

  for (int i = 0; i < LENGTH; i++) {
    TRIANGLE[i] = (int *)calloc(LENGTH, sizeof(int));
  }

  FILE *file;
  file = fopen("./0067_triangle.txt", "r");

  if (file == NULL) {
    printf("ERROR OPENING FILE\n");
    return;
  }

  for (int i = 0; i < LENGTH; i++) {
    for (int j = 0; j <= i; j++) {
      fscanf(file, "%d", &TRIANGLE[i][j]);
    }
  }

  fclose(file);
}

void cleanup() {

  for (int i = 0; i < LENGTH; i++) {
    free(TRIANGLE[i]);
  }

  free(TRIANGLE);
}

unsigned long long max_path_sum(unsigned int size) {

  for (int i = size - 2; i >= 0; i--) {
    // start at 13th row
    // Sum of neighbors
    for (int j = 0; j <= i; j++) {
      int current_position = TRIANGLE[i][j];
      int left_neighbor = TRIANGLE[i + 1][j];
      int right_neighbor = TRIANGLE[i + 1][j + 1];

      TRIANGLE[i][j] = current_position + max(left_neighbor, right_neighbor);
    }
  }

  return TRIANGLE[0][0];
}

int main(int argc, char *argv[]) {
  initialize_triangle();
  unsigned long long sum = max_path_sum(LENGTH);

  printf("100x100 Sum: %lld", sum);

  cleanup();
}
