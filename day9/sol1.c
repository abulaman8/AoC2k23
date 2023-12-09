#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define NUM_LINES 3
#define NUM_LINES 200

int findNext(int seq[128], int seq_len) {
  // printf("entering findNext\n");
  // printf("input sequence:");
  // for (int i = 0; i < seq_len; i++) {
  //   printf(" %d", seq[i]);
  // }
  // printf("\n");
  // printf("seq_len: %d\n", seq_len);
  int first_int = seq[0];
  int last_int = seq[seq_len - 1];
  
  int count = 0;
  for (int i = 0; i < seq_len; i++) {
    if (seq[i] == first_int) {
      count++;
    } else {
      break;
    }
  }
  if (count == seq_len) {
    return first_int;
  }
  else{
    int *diff_seq = (int *)malloc(sizeof(int) * seq_len);
    for (int i = 0; i < seq_len - 1; i++) {
      diff_seq[i] = seq[i + 1] - seq[i];
    }
    int next = findNext(diff_seq, seq_len - 1);
    return last_int + next;
  }
}

int main() {
  // char filename[16] = "testinput.txt";
  char filename[16] = "input.txt";
  char str[128];
  int sum = 0;
  int line_lens[NUM_LINES] = {0};
  int dataset[NUM_LINES][128];
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("File open error\n");
    exit(1);
  }
  int i = 0;
  while (fgets(str, 128, fp) != NULL) {
    str[strlen(str) - 1] = '\0';
    // printf("%s\n", str);
    char *token = strtok(str, " ");
    int j = 0;
    while (token != NULL) {
      // printf("works till here1\n");
      dataset[i][j] = atoi(token);
      // printf("works till here2\n");
      token = strtok(NULL, " ");
      j++;
    }
    line_lens[i] = j;
    i++;
  }
  // printf("--------------------\n");
  // for (int i = 0; i < NUM_LINES; i++) {
  //   for (int j = 0; j < line_lens[i]; j++) {
  //     printf("%d ", dataset[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("--------------------\n");

  for (int i = 0; i < NUM_LINES; i++) {
    int next = findNext(dataset[i], line_lens[i]);
    sum += next;
    // printf("%d\n", next);
  }
  printf("sum: %d\n", sum);
  fclose(fp);
  return 0;
}
