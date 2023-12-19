#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int hashMeDaddy(char a, int current_value){
  int ascii = (int)a;
  current_value += ascii;
  current_value *= 17;
  current_value %= 256;
  return current_value;
}

int hashMeWholeDaddy(char* a){
  int current_value = 0;
  int len = strlen(a);
  for (int i = 0; i < len; i++){
    current_value = hashMeDaddy(a[i], current_value);
  }
  return current_value;
}


int main() {
  // char filename[16] = "testinput.txt";
  char filename[16] = "input.txt";
  char str[23000];
  int instruction_count = 0;
  FILE *fp = fopen(filename, "r");
  char **seq = NULL;
  // int *seq_hash_values = NULL;
  int sum = 0;
  if (fp == NULL) {
    printf("Could not open file");
    exit(-1);
  }
  fgets(str, sizeof(str), fp);
  str[strlen(str)-1] = '\0';
  // printf("%s\n", str);
  char *token = strtok(str, ",");
  while (token != NULL) {
    seq = realloc(seq,  (instruction_count + 1)* sizeof(char*));
    // seq_hash_values = realloc(seq_hash_values, (instruction_count + 1) * sizeof(int));
    seq[instruction_count] = malloc(strlen(token) + 1);
    strcpy(seq[instruction_count], token);
    // seq_hash_values[instruction_count] = 0;
    token = strtok(NULL, ",");
    instruction_count++;
  }
  // for (int i = 0; i < instruction_count; i++){
  //   printf("%s ", seq[i]);
  // }
  // char test[5]= "HASH";
  // int test_hash = hashMeWholeDaddy(test);
  //
  // printf("%d\n", test_hash);
  for(int i = 0; i < instruction_count; i++){
    int val = hashMeWholeDaddy(seq[i]);
    sum += val;

  }
  printf("sum: %d\n", sum);


}
