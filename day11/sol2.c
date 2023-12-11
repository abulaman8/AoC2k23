#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define ROWS 10
// #define COLS 10

#define TEN 9
#define HUNDRED 99
#define MILLION 999999

#define ROWS 140
#define COLS 140



long long findManhattanDistance(long long x1, long long y1, long long x2, long long y2) {
  int distance = llabs(x1 - x2) + llabs(y1 - y2);
  return distance;
}

int **FindAllGalaxies(char universe[ROWS][COLS], int rows, int cols){
  char galaxy = '#';
  int galaxy_count = 0;
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      if (universe[i][j] == galaxy){
        galaxy_count++;
      }
    }
  }

  int **galaxy_coords = malloc(galaxy_count * sizeof(int *));
  for (int i = 0; i < galaxy_count; i++){
    galaxy_coords[i] = malloc(2 * sizeof(int));
  }
  int galaxy_index = 0;
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      if (universe[i][j] == galaxy){
        galaxy_coords[galaxy_index][0] = i;
        galaxy_coords[galaxy_index][1] = j;
        galaxy_index++;
      }
    }
  }
  return galaxy_coords;
}

int main() {
  // char filename[16] = "testinput.txt";
  char filename[16] = "input.txt";
  char str[256];
  char universe[ROWS][COLS];
  int empty_rows[ROWS];
  int empty_rows_len = 0;
  int empty_cols[COLS];
  int empty_cols_len = 0;
  int galaxy_count = 0;
  long long sum = 0;
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("File open error\n");
    exit(1);
  }
  int i = 0;
  while (fgets(str, 256, fp) != NULL) {
    str[strcspn(str, "\n")] = 0;
    strcpy(universe[i], str);
    i++;
  }
  fclose(fp);

  // for (int i = 0; i < ROWS; i++) {
  //   for (int j = 0; j < COLS; j++) {
  //     printf("%c", universe[i][j]);
  //   }
  //   printf("\n");
  // }
  for (int i = 0; i < ROWS; i++) {
    int empty = 0;
    for (int j = 0; j < COLS; j++) {
      if (universe[i][j] == '.') {
        empty++;
      }
      if (empty == COLS) {
        empty_rows[empty_rows_len] = i;
        empty_rows_len++;
      }
    }
  }
  for (int i = 0; i < COLS; i++) {
    int empty = 0;
    for (int j = 0; j < ROWS; j++) {
      if (universe[j][i] == '.') {
        empty++;
      }
      if (empty == ROWS) {
        empty_cols[empty_cols_len] = i;
        empty_cols_len++;
      }
    }
  }
  for (int i = 0; i < ROWS; i++){
    for (int j = 0; j < COLS; j++){
      if (universe[i][j] == '#'){
        galaxy_count++;
      }
    }
  }

  // printf("empty rows: %d\n", empty_rows_len);
  // printf("empty cols: %d\n", empty_cols_len);
  // printf("empty rows: ");
  // for (int i = 0; i < empty_rows_len; i++){
  //   printf(" %d", empty_rows[i]);
  // }
  // printf("\n");
  // printf("empty cols: ");
  // for (int i = 0; i < empty_cols_len; i++){
  //   printf(" %d", empty_cols[i]);
  // }
  //
  // printf("\n");
  //
  // printf("--------------------\n");
  // char **expanded_universe =
  //     ExpandUniverse(universe, empty_rows, empty_cols, empty_rows_len,
  //                    empty_cols_len);
  // for (int i = 0; i < (ROWS + (empty_rows_len * MILLION)); i++) {
  //   for (int j = 0; j < (COLS + (empty_cols_len * MILLION)); j++) {
  //     printf("%c", expanded_universe[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("--------------------\n");
  int **galaxy_coords = FindAllGalaxies(universe, ROWS, COLS);
  long long long_galaxy_coords[galaxy_count][2];
  for (int i = 0; i < galaxy_count; i++){
    long_galaxy_coords[i][0] = (long long)galaxy_coords[i][0];
    long_galaxy_coords[i][1] = (long long)galaxy_coords[i][1];
  }
  for (int i = 0; i < galaxy_count; i++){
    long long x = long_galaxy_coords[i][0];
    long long y = long_galaxy_coords[i][1];
    int row_offset = 0;
    int col_offset = 0;
    for (int r = 0; r < empty_rows_len; r++){
      if (empty_rows[r] < x){
        row_offset += MILLION;
      }
    }
    for (int c = 0; c < empty_cols_len; c++){
      if (empty_cols[c] < y){
        col_offset += MILLION;
      }
    }
    long_galaxy_coords[i][0] += row_offset;
    long_galaxy_coords[i][1] += col_offset;
  }
  for (int i = 0; i < galaxy_count; i++){
    // printf("galaxy %d: %lld, %lld\n", i, long_galaxy_coords[i][0], long_galaxy_coords[i][1]);
  }

  // for (int i = 0; i < galaxy_count; i++){
  //   printf("galaxy %d: %d, %d\n", i, galaxy_coords[i][0], galaxy_coords[i][1]);
  // }
  // printf("--------------------\n");
  for (int i = 0; i < galaxy_count; i++){
    for (int j = 0; j < galaxy_count; j++){
      if (i != j){
        long long distance = findManhattanDistance(long_galaxy_coords[i][0], long_galaxy_coords[i][1], long_galaxy_coords[j][0], long_galaxy_coords[j][1]);
        // printf("galaxy %d to galaxy %d: %d\n", i, j, distance);
        sum += distance;
      }
    }
  }
  long long total_distance = sum / 2;
  printf("total distance: %lld\n", total_distance);
  return 0;
}
