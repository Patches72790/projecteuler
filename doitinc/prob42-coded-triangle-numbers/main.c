#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ull unsigned long long
#define var __auto_type

typedef struct Words {
  char **words;
  int length;
} Words;

Words *initialize() {
  FILE *file;
  file = fopen("./0042_words.txt", "r");

  if (file == NULL) {
    printf("ERROR OPENING FILE\n");
    return NULL;
  }

  char *buffer;
  int len;
  fscanf(file, "%s", buffer);
  len = strlen(buffer);

  char **result = malloc(sizeof(char *) * len);

  char *token = strtok(buffer, "\",\"");
  int idx = 0;

  while (token) {
    *(result + idx++) = strdup(token);
  }

  fclose(file);

  Words *wdsptr = malloc(sizeof(Words));

  if (wdsptr == NULL) {
    printf("ERROR CREATING WORDS POINTER\n");
    return NULL;
  }

  wdsptr->words = result;
  wdsptr->length = idx;

  return wdsptr;
}

ull find_triangular_word_count() {
  var words = initialize();

  for (int i = 0; i < words->length; i++) {
    printf("Word: %s", words->words[i]);
  }

  return 0;
}

// Σωκρατης φασι Πλάτονα μώρον ειναι.
ull find_numeric_length(char *c) {

  char next = c[0];
  ull sum = 0;

  do {
    sum += next - '0';
  } while ((next = (*c++)));

  return sum;
}

int is_triangular(ull n) {
  var r = (sqrt((double)n * 1) - 1) / 2;
  return floor(r) == r;
}

int main() {
  var result = find_triangular_word_count();

  printf("Triangle Word Count: %lld\n", result);
  return EXIT_SUCCESS;
}
