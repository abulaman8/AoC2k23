#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char filename[16] = "testinput.txt";
  char str[64];
  FILE *fp = fopen(filename, "r");
  char input[64];
  char nums[64];
  int nums_arr[64];
  int nums_arr_len = 0;
  if (fp == NULL) {
    printf("File not found!\n");
    exit(1);
  }
  while (fgets(str, 64, fp) != NULL) {
    printf("%s", str);
    char *token = strtok(str, " ");
    strcpy(input, token);
    token = strtok(NULL, " ");
    strcpy(nums, token);
    printf(" Input: %s\n", input);
    printf(" Nums: %s\n", nums);
    char *num = strtok(nums, ",");
    while (num != NULL) {
      nums_arr[nums_arr_len] = atoi(num);
      nums_arr_len++;
      num = strtok(NULL, ",");
    }
    printf(" Nums array: ");
    for (int i = 0; i < nums_arr_len; i++) {
      printf("%d ", nums_arr[i]);
    }
    printf("\n");


  }
  fclose(fp);
  return 0;
}
