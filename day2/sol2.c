#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char filename[16] = "input1.txt";
  // char filename[16] = "testinputs.txt";

  char gamestr[512];
  char setstr[512];
  char colorstr[3][16];
  char components[2][5];
  char gamesets[16][512];
  int i = 0;
  int j = 0;
  int c = 0;
  int r = 0;
  int sum = 0;
  int val = 0;

  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: cannot open file %s\n", filename);
    return 1;
  }
topwhile:
  while (fgets(gamestr, 512, fp) != NULL) {
    int red = 0;
    int green = 0;
    int blue = 0;
    int power = 0;
    i++;
    j = 0;
    c = 0;
    r = 0;
    int len = strlen(gamestr);
    if (gamestr[len - 1] == '\n') {
      gamestr[len - 1] = '\0';
    }

    char *o = strtok(gamestr, ":");
    int olen = strlen(o);
    strcpy(gamestr, gamestr + olen + 1);
    // printf("gamestring: %s\n", gamestr);

    char *p = strtok(gamestr, ";");
    while (p != NULL) {
      strcpy(gamesets[j], p);
      // printf(" gameset %d of gamestring %d: %s\n", j, i, gamesets[j]);
      p = strtok(NULL, ";");
      j++;
    }
    for (int k = 0; k < j; k++) {
      strcpy(setstr, gamesets[k]);
      char *q = strtok(setstr, ",");
      c=0;
      while (q != NULL) {
        strcpy(colorstr[c], q);
        // printf("  color %d of gameset %d of gamestring %d: %s\n", c, k, i,
               // colorstr[c]);
        q = strtok(NULL, ",");
        c++;
      }
      // c = 0;

      for (int l = 0; l < c; l++) {
        val = atoi(colorstr[l]);
        // printf("%d\n", val);
        char *cm = strtok(colorstr[l], " ");
        while (cm != NULL) {
          strcpy(components[r], cm);
          cm = strtok(NULL, " ");
          r++;
        }
        // printf("%s\n", components[1]);
        r = 0;
        if ((strcmp(components[1], "red") == 0 && val > red)){
          red = val;
        }
        if ((strcmp(components[1], "green") == 0 && val > green)){
          green = val;
        }
        if ((strcmp(components[1], "blue") == 0 && val > blue)){
          blue = val;
        }
      }

    }
    power = red * green * blue;
    // printf("power: %d\n", power);
    sum += power;
  }

  printf("%d\n", sum);

  fclose(fp);
  return 0;
}
