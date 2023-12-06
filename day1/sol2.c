#include <ctype.h>
#include <stdio.h>
#include <string.h>

int startswith(char *str, char *prefix) {
  return strncmp(str, prefix, strlen(prefix)) == 0;
}

int main() {

  char filename[] = "day1input1.txt";
  // char filename[] = "testinput.txt";
  char num_words[9][6] = {"one", "two",   "three", "four", "five",
                          "six", "seven", "eight", "nine"};
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
    int digits[16];
    size_t length = strcspn(str, "\n");
    str[length] = '\0';
    len = strlen(str);
    int j = 0;
    for (int i = 0; i < len; i++) {
      if (isdigit(str[i])) {
        digits[j] = str[i] - '0';

        j++;
      }
      for (int k = 0; k < 9; k++) {
        char copy[len];
        strcpy(copy, str+i);
        copy[len-i] = '\0';
        if (startswith(copy, num_words[k])) {
          digits[j] = k + 1;
          j++;
        }
      }
    }
    for (int i = 0; i < j; i++) {
      printf("%d", digits[i]);
    }
    printf("\n");

    twodigits[0] = digits[0];
    twodigits[1] = digits[j - 1];
    printf("%d - %d\n", twodigits[0], twodigits[1]);

    value = (twodigits[0] * 10) + twodigits[1];
    sum += value;
  }
  fclose(fp);
  printf("%d\n", sum);
  return 0;
}
