#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


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
  int total_n = 4;
  // ------------------------------------------
  char str[64];
  double epsilon = 0.0000001;
  int product = 1;
  int ways = 0;
  double min_root, max_root;
  int time[total_n];
  int dist[total_n];
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
    time[i] = atoi(token);
    token = strtok(NULL, " ");
    i++;
  }
  fgets(str, 64, fp);
  str[strcspn(str, "\n")] = 0;
  strcpy(str, str + 11);
  token = strtok(str, " ");
  i = 0;
  while (token != NULL) {
    dist[i] = atoi(token);
    token = strtok(NULL, " ");
    i++;
  }
  // printf("time: ");
  // for (int i = 0; i < total_n; i++) {
  //   printf("%d ", time[i]);
  // }
  // printf("\n");
  // printf("dist: ");
  // for (int i = 0; i < total_n; i++) {
  //   printf("%d ", dist[i]);
  // }
  // printf("\n");

  for (int i = 0; i < total_n; i++){
    double a = -1.0;
    double b = time[i];
    double c = -dist[i];
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
  }

  printf("product: %d\n", product);


  fclose(fp);
  return 0;
}
