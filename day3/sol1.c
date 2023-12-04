#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_symbol(char c) {
  if (isalnum(c) || c == '.') {
    return 0;
  } else {
    return 1;
  }
}

int main() {
  char filename[16] = "testinput.txt";
  int rows = 10;
  int cols = 10;
  char line[cols];
  char engine[rows+2][cols+2];
  int line_number = 1;
  int sum = 0;
  char temp[cols];
  for (int i=0; i<cols+2; i++) {
    engine[0][i] = 'x';
    engine[rows+1][i] = 'x';
  }
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening file %s\n", filename);
    exit(1);
  }
  while (fgets(line, cols, fp) != NULL) {
    // strcat(line, "x");
    // strcat("x", line);
    strcpy(engine[line_number], line);
    // printf("%s", engine[line_number]);
    line_number++;
  }
  fclose(fp);
  // for (int i=0; i<rows+1; i++){
  //   printf("%s\n", engine[i]);
  // }
  printf("%s\n", engine[0]);
  printf("%s\n", engine[1]);

  return 0;
}
