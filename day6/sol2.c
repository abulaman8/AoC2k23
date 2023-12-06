#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void slice(const char *str, char *result, size_t start, size_t end) {
  strncpy(result, str + start, end - start);
}

double get_first_quadratic_root(double a, double b, double c) {
  double root = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
  return root;
}

double get_second_quadratic_root(double a, double b, double c) {
  double root = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
  return root;
}

int main() {
  // ------------------------------------------
  // char filename[16] = "testinput.txt";
  // int total_n = 3;
  // ------------------------------------------
  char filename[16] = "input.txt";
  char time_digits[9];
  char dist_digits[16];
  // ------------------------------------------
  char str[64];
  double epsilon = 0.0000001;
  long long time;
  long long dist;
  int product = 1;
  int ways = 0;
  double min_root, max_root;
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("File not found!\n");
    return 1;
  }
  fgets(str, 64, fp);
  str[strcspn(str, "\n")] = 0;
  strcpy(str, str + 11);
  char *token = strtok(str, " ");
  int i = 0;
  while (token != NULL) {
    token[strcspn(token, "\n")] = 0;
    strcat(time_digits, token);
    printf("time_digits: %s\n", time_digits);
    token = strtok(NULL, " ");
    i++;
  }
  // add null terminator
  time_digits[8] = '\0';

  fgets(str, 64, fp);
  str[strcspn(str, "\n")] = 0;
  strcpy(str, str + 11);
  token = strtok(str, " ");
  i = 0;
  while (token != NULL) {
    token[strcspn(token, "\n")] = 0;
    strcat(dist_digits, token);
    token = strtok(NULL, " ");
    i++;
  }
  dist_digits[15] = '\0';
  printf("time_digits: %s\n", time_digits);
  printf("dist_digits: %s\n", dist_digits);
  time = atoll(time_digits);
  dist = atoll(dist_digits);

  double a = -1.0;
  double b = time;
  double c = -dist;
  min_root = get_first_quadratic_root(a, b, c);
  max_root = get_second_quadratic_root(a, b, c);
  min_root = min_root + epsilon;
  max_root = max_root - epsilon;
  min_root = ceil(min_root);
  max_root = floor(max_root);
  ways = max_root - min_root + 1;
  product = product * ways;
  printf("min_root, max_root: %lf %lf\n", min_root, max_root);
  printf("number of ways: %d\n", ways);

  fclose(fp);
  return 0;
}
