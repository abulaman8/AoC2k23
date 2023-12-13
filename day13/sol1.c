#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 32
#define MAX_LINES_PER_BLOCK 32

int min(int a, int b) {
  if (a < b)
    return a;
  return b;
}


char **Transpose(char block[MAX_LINES_PER_BLOCK][MAX_LINE_LEN], int rows,
                 int cols) {
  char **transposed = malloc(cols * sizeof(char *));
  for (int i = 0; i < cols; i++) {
    transposed[i] = malloc(rows * sizeof(char));
  }
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      transposed[i][j] = block[j][i];
    }
  }
  // for (int i = 0; i < cols; i++){
  //   for (int j = 0; j < rows; j++){
  //     printf("%c", transposed[i][j]);
  //   }
  //   printf("\n");
  // }
  return transposed;
}

int find_reflection_len(char block[MAX_LINES_PER_BLOCK][MAX_LINE_LEN], int rows,
                        int cols) {
  printf("rows: %d\n", rows);
  printf("cols: %d\n", cols);
  int i = 0;
  for (; i < rows; i++) {
    printf("i: %d", i);
    printf(" block[i]: %s\n", block[i]);
    int len_to_check = min(i + 1, rows - i - 1);
    printf(" len_to_check: %d\n", len_to_check);
    for (int j = 0; j < len_to_check; j++) {
      printf(" j: %d\n", j);
      block[i - j][cols] = '\0';
      block[i + j + 1][cols] = '\0';
      printf("  block[i-j]: %s\n", block[i - j]);
      printf("  block[i+j+1]: %s\n", block[i + j + 1]);
      if (strcmp(block[i - j], block[i + j + 1]) != 0) {
        printf("  break\n");
        break;
      }
      if (j == len_to_check - 1) {
        return i + 1;
      }
    }
  }
  return 0;
}

int main() {
  // char filename[16] = "testinput.txt";
  char filename[16] = "input.txt";
  int sum = 0;
  char str[32];
  char block[MAX_LINES_PER_BLOCK][MAX_LINE_LEN];
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: cannot open %s\n", filename);
    exit(1);
  }
  int i = 0;
  while (fgets(str, sizeof(str), fp) != NULL) {
    if (strlen(str) <= 1) {
      int num_lines = i;
      for (i = 0; i < num_lines; i++) {
        printf("%s\n", block[i]);
      }
      int reflection_len =
          find_reflection_len(block, num_lines, strlen(block[0]));
      printf("reflection_len: %d\n", reflection_len);
      printf("--------------------\n");
      // printf("num lines in transposed: %d\n", strlen(block[0]));
      char **transposed = Transpose(block, num_lines, strlen(block[0]));
      char tblock[MAX_LINES_PER_BLOCK][MAX_LINE_LEN];
      for (int i = 0; i < strlen(block[0]); i++) {
        for (int j = 0; j < num_lines; j++) {
          tblock[i][j] = transposed[i][j];
        }
      }
      // printf("Transposed:\n");
      // for (i = 0; i < strlen(block[0]); i++) {
      //   for (int j = 0; j < num_lines; j++) {
      //     printf("%c", transposed[i][j]);
      //   }
      //   printf("\n");
      // }
      printf("\n");
      printf("tblock:\n");
      for (i = 0; i < strlen(block[0]); i++) {
        for (int j = 0; j < num_lines; j++) {
          printf("%c", tblock[i][j]);
        }
        printf("\n");
      }
      int reflection_len_transposed =
          find_reflection_len(tblock, strlen(block[0]), num_lines);

      printf("reflection_len_transposed: %d\n", reflection_len_transposed);
      int val = (reflection_len * 100) + reflection_len_transposed;
      printf("val: %d\n", val);
      sum += val;

      printf("\n");
      printf("-------ONE BLOCK DONE-------\n");
      printf("\n");
      i = 0;
      continue;
    }
    str[strlen(str) - 1] = '\0';
    // printf("%s\n", str);
    strcpy(block[i], str);
    i++;
  }
  int num_lines = i;
  for (i = 0; i < num_lines; i++) {
    printf("%s\n", block[i]);
  }
  int reflection_len = find_reflection_len(block, num_lines, strlen(block[0]));
  printf("reflection_len: %d\n", reflection_len);
  printf("--------------------\n");
  // printf("num lines in transposed: %d\n", strlen(block[0]));
  char **transposed = Transpose(block, num_lines, strlen(block[0]));
  char tblock[MAX_LINES_PER_BLOCK][MAX_LINE_LEN];
  for (int i = 0; i < strlen(block[0]); i++) {
    for (int j = 0; j < num_lines; j++) {
      tblock[i][j] = transposed[i][j];
    }
  }
  // printf("Transposed:\n");
  // for (i = 0; i < strlen(block[0]); i++) {
  //   for (int j = 0; j < num_lines; j++) {
  //     printf("%c", transposed[i][j]);
  //   }
  //   printf("\n");
  // }
  printf("\n");
  printf("tblock:\n");
  for (i = 0; i < strlen(block[0]); i++) {
    for (int j = 0; j < num_lines; j++) {
      printf("%c", tblock[i][j]);
    }
    printf("\n");
  }
  int reflection_len_transposed =
      find_reflection_len(tblock, strlen(block[0]), num_lines);

  printf("reflection_len_transposed: %d\n", reflection_len_transposed);
  int val = (reflection_len * 100) + reflection_len_transposed;
  printf("val: %d\n", val);
  sum += val;

  printf("\n");
  printf("-------ONE BLOCK DONE-------\n");
  printf("\n");
  printf("sum: %d\n", sum);

  fclose(fp);
  return 0;
}
