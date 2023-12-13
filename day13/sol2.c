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


int try_bitflip_and_match(char str1[MAX_LINE_LEN], char str2[MAX_LINE_LEN],
                          int len) {
  int num_diff = 0;
  for (int i = 0; i < len; i++) {
    if (str1[i] != str2[i]) {
      num_diff++;
    }
    if (num_diff > 1) {
      return 0;
    }
  }
  return 1;
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
  return transposed;
}

int find_reflection_len_with_bit_flip(
    char block[MAX_LINES_PER_BLOCK][MAX_LINE_LEN], int rows, int cols) {
  int num_bit_flips = 0;
  int i = 0;
  for (; i < rows; i++) {
    int len_to_check = min(i + 1, rows - i - 1);
    for (int j = 0; j < len_to_check; j++) {
      block[i - j][cols] = '\0';
      block[i + j + 1][cols] = '\0';
      if (strcmp(block[i - j], block[i + j + 1]) != 0) {
        if (try_bitflip_and_match(block[i - j], block[i + j + 1],
                                  strlen(block[i - j])) == 0) {
          break;
        } else {
          num_bit_flips++;
        }
      }
      if (j == len_to_check - 1) {
        if (num_bit_flips == 1) {
          return i + 1;
        }

        return 0;
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
  int block_num = 0;
  char block[MAX_LINES_PER_BLOCK][MAX_LINE_LEN];
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: cannot open %s\n", filename);
    exit(1);
  }
  int i = 0;
  while (fgets(str, sizeof(str), fp) != NULL) {
    if (strlen(str) <= 1) {
      printf("starting block %d\n", block_num);
      int num_lines = i;
      int reflection_len_with_bit_flip =
          find_reflection_len_with_bit_flip(block, num_lines, strlen(block[0]));
      printf("reflection_len: %d\n", reflection_len_with_bit_flip);
      char **transposed = Transpose(block, num_lines, strlen(block[0]));
      char tblock[MAX_LINES_PER_BLOCK][MAX_LINE_LEN];
      for (int i = 0; i < strlen(block[0]); i++) {
        for (int j = 0; j < num_lines; j++) {
          tblock[i][j] = transposed[i][j];
        }
      }
      int reflection_len_transposed_with_bit_flip =
          find_reflection_len_with_bit_flip(tblock, strlen(block[0]),
                                            num_lines);
      int val = 0;
      sum += reflection_len_with_bit_flip * 100;
      sum += reflection_len_transposed_with_bit_flip;

      printf("reflection_len_transposed: %d\n",
             reflection_len_transposed_with_bit_flip);

      i = 0;
      block_num++;
      continue;
    }
    str[strlen(str) - 1] = '\0';
    strcpy(block[i], str);
    i++;
  }
  printf("starting block %d\n", block_num);
  int num_lines = i;
  int reflection_len_with_bit_flip =
      find_reflection_len_with_bit_flip(block, num_lines, strlen(block[0]));
  printf("reflection_len: %d\n", reflection_len_with_bit_flip);
  char **transposed = Transpose(block, num_lines, strlen(block[0]));
  char tblock[MAX_LINES_PER_BLOCK][MAX_LINE_LEN];
  for (int i = 0; i < strlen(block[0]); i++) {
    for (int j = 0; j < num_lines; j++) {
      tblock[i][j] = transposed[i][j];
    }
  }
  int reflection_len_transposed_with_bit_flip =
      find_reflection_len_with_bit_flip(tblock, strlen(block[0]), num_lines);
  int val = 0;
  sum += reflection_len_with_bit_flip * 100;
  sum += reflection_len_transposed_with_bit_flip;

  printf("reflection_len_transposed: %d\n",
         reflection_len_transposed_with_bit_flip);

  printf("sum: %d\n", sum);

  fclose(fp);
  return 0;
}
