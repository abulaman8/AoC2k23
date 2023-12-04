#include <stdio.h>
#include <string.h>

int main() {
  char digitwords[9][5] = {"one", "two",   "three", "four", "five",
                           "six", "seven", "eight", "nine"};

  char numbers[9][1] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
  char *ptrarray[9];
  // char filename[] = "day1input1.txt";
  char filename[] = "testinput.txt";
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Could not open file %s", filename);
    return 1;
  }
  char str[512];
  char newstr[512];
  int twodigits[2] = {0, 0};
  int len = 0;
  int sum = 0;
  int value = 0;
  while (fgets(str, 512, fp) != NULL) {
    size_t length = strcspn(str, "\n");
    str[length] = '\0';

    len = strlen(str);
    strcpy(newstr, str);

    for (int i = 0; i < 9; i++) {
      char *ptr = strstr(newstr, digitwords[i]);
      if (ptr != NULL) {
        ptrarray[i] = ptr;
        printf("%s - %s\n", ptrarray[i], newstr);
      }
      else {
        ptrarray[i] = NULL;
        printf("NULL - %s\n", newstr);
      }
    }


    // printf("%s - %s\n", str, newstr);
    strcpy(str, newstr);
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
    // printf("%d - %d\n", value, sum);
  }
  fclose(fp);
  printf("%d\n", sum);
  return 0;
}
