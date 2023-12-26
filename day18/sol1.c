#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_area(int **coordinates, int len) {
  int sum1 = 0;
  int sum2 = 0;
  int i = 0;
  for (; i < len; i++) {
    printf("starting coordinate: %d\n", i);
    int temp1 = (coordinates[i][0]) * (coordinates[(i + 1)%len][1]);
    int temp2 = (coordinates[i][1]) * (coordinates[(i + 1)%len][0]);
    sum1 += temp1;
    sum2 += temp2;
    printf("done coordinate: %d\n", i);
  }
  int diff = abs(sum1 - sum2);

  int area = diff / 2;
  return area;
}

int main() {
  // char filename[16] = "testinput.txt";
  // int rows = 14;
  char filename[16] = "input.txt";
  int rows = 718;
  char str[16];
  FILE *fp = fopen(filename, "r");
  char instructions[rows][16];
  int instruction_count = 0;
  while (fgets(str, sizeof(str), fp) != NULL) {
    str[strlen(str) - 1] = '\0';
    // printf("%s\n", str);
    strcpy(instructions[instruction_count], str);
    instruction_count++;
  }
  fclose(fp);
  // printf("--------------------------------------\n");
  // for (int i = 0; i < instruction_count; i++){
  //   printf("%s\n", instructions[i]);
  // }

  int current_x = 0;
  int current_y = 0;
  int perimeter = 0;
  int **coordinates = malloc(sizeof(int *) * instruction_count);
  for (int i = 0; i < instruction_count; i++) {
    coordinates[i] = malloc(sizeof(int) * 2);
  }
  for (int i = 0; i < instruction_count; i++) {
    char *token = strtok(instructions[i], " ");
    // printf("first: %s", token);
    char direction = *token;
    token = strtok(NULL, " ");
    // printf("second: %s", token);
    int len = atoi(token);
    switch (direction) {
    case 'R':
      current_x += len;
      break;
    case 'L':
      current_x -= len;
      break;
    case 'U':
      current_y += len;
      break;
    case 'D':
      current_y -= len;
      break;
    }
    coordinates[i][0] = current_x;
    coordinates[i][1] = current_y;
    perimeter += len;
    // printf("direction: %c, length: %d\n", direction, len);
  }
  for (int i = 0; i < instruction_count; i++) {

    printf("coordinate: %d, x: %d, y: %d\n", i, coordinates[i][0],
           coordinates[i][1]);
  }
  int area = find_area(coordinates, instruction_count);
  int ans = area + (perimeter/2) + 1;
  printf("area: %d", ans);
}
