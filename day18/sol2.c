#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void slice(const char *str, char *result, size_t start, size_t end) {
  strncpy(result, str + start, end - start);
  result[end - start] = '\0';
}

long long find_area(long **coordinates, long len) {
  long sum1 = 0;
  long sum2 = 0;
  long i = 0;
  for (; i < len; i++) {
    printf("starting coordinate: %ld\n", i);
    long temp1 = (coordinates[i][0]) * (coordinates[(i + 1) % len][1]);
    long temp2 = (coordinates[i][1]) * (coordinates[(i + 1) % len][0]);
    sum1 += temp1;
    sum2 += temp2;
    printf("done coordinate: %ld\n", i);
  }
  long long diff = llabs((long long)sum1 - (long long)sum2);

  long long area = diff / 2;
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

  long current_x = 0;
  long current_y = 0;
  long perimeter = 0;
  long **coordinates = malloc(sizeof(long *) * instruction_count);
  for (int i = 0; i < instruction_count; i++) {
    coordinates[i] = malloc(sizeof(long) * 2);
  }
  for (int i = 0; i < instruction_count; i++) {
    char *token = strtok(instructions[i], " ");
    // printf("first: %s", token);
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    char *hex = token;
    slice(hex, hex, 2, strlen(hex) - 1);
    // printf("%s\n", hex);
    int direction = atoi(hex+5);
    char *lenstr = (char*)malloc(6);
    strncpy(lenstr, hex, 5);
    // printf(" %s\n", lenstr);
    // printf(" %d\n", direction);
    long len = strtol(lenstr, &lenstr+5, 16);
    // printf("%ld\n", len);

    // printf("second: %s", token);
      switch (direction) {
      case 0:
        current_x += len;
        break;
      case 2:
        current_x -= len;
        break;
      case 3:
        current_y += len;
        break;
      case 1:
        current_y -= len;
        break;
      }
      coordinates[i][0] = current_x;
      coordinates[i][1] = current_y;
      perimeter += len;
      // printf("direction: %d, length: %ld\n", direction, len);
    // }
    // for (int i = 0; i < instruction_count; i++) {
    //
    //   printf("coordinate: %d, x: %d, y: %d\n", i, coordinates[i][0],
    //          coordinates[i][1]);
    // }
  }
    long long area = find_area(coordinates, instruction_count);
    long long ans = area + (((long long)perimeter)/2) + 1;
    printf("area: %lld", ans);
}
