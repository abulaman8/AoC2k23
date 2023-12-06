#include <stdio.h>
#include <string.h>

int main() {
  char filename[] = "day1input1.txt";
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Could not open file %s", filename);
    return 1;
  }
  char str[512];
  int twodigits[2] = {0, 0};
  int len = 0;
  int sum = 0;
  int value = 0;
  while (fgets(str, 512, fp) != NULL) {

    // for (int i = 0; i < 512; i++) {
    //   if (str[i] == '\n') {
    //     strlen = i;
    //     break;
    //   }
    // }
    len = strlen(str);
    for (int i = 0; i <= len; i++) {
      if (str[i] >= '0' && str[i] <= '9') {
        twodigits[0] = str[i] - '0';
        // printf("%d", twodigits[0]);
        break;
      }
    }
    for (int i = len; i >= 0; i--) {
      if (str[i] >= '0' && str[i] <= '9') {
        twodigits[1] = (int)str[i] - '0';
        // printf("%d\n", twodigits[1]);
        break;
      }
    }
    value = (twodigits[0] * 10) + twodigits[1];
    sum += value;
    printf("%d - %d\n", value, sum);
  }
  fclose(fp);
  printf("%d\n", sum);
  return 0;
}
