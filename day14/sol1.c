#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **tiltMeDaddy(char **grid, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] == 'O'){
        int k = i - 1;
        while (k >= 0 && grid[k][j] == '.'){
          // printf("  i: %d, j: %d, k: %d\n", i, j, k);
          k--;
        }
        // printf("i: %d, j: %d, k: %d\n", i, j, k);
        grid[i][j] = '.';
        grid[k+1][j] = 'O';

      }
    }
  }
  return grid;
}

int main() {
  // char filename[16] = "testinput.txt";
  // int num_rows = 10;
  // int num_cols = 10;
  // ---------------------------------
  char filename[16] = "input.txt";
  int num_rows = 100;
  int num_cols = 101;
  char str[128];
  int load = 0;

  char **grid = malloc(num_rows * sizeof(char *));
  for (int i = 0; i < num_rows; i++) {
    grid[i] = malloc(num_cols * sizeof(char));
  }
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("File open error\n");
    exit(1);
  }
  int i = 0;
  while (fgets(str, 128, fp) != NULL) {
    str[strlen(str) - 1] = '\0';
    strcpy(grid[i], str);
    i++;
  }
  for (int i = 0; i < num_rows; i++) {
    printf("%s\n", grid[i]);
  }

  char **tiltedGrid = tiltMeDaddy(grid, num_rows, num_cols);
  printf("\n");
  for (int i = 0; i < num_rows; i++) {
    printf("%s\n", tiltedGrid[i]);
  }
  for (int i = 0; i < num_rows; i++){
    for (int j = 0; j < num_cols; j++){
      if (tiltedGrid[i][j] == 'O'){
        int OmyLoad = num_rows - i;
        load += OmyLoad;
      }
    }
  }
  for (int i = 0; i < num_rows; i++) {
    free(grid[i]);
  }
  free(grid);
  printf("Load: %d\n", load);

  fclose(fp);
}
