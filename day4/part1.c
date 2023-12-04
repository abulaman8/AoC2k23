#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void slice(const char* str, char* result, size_t start, size_t end)
{
    strncpy(result, str + start, end - start);
}
int main() {
  // char filename[16] = "input.txt";
  char filename[16] = "testinput.txt";
  int prefix_len = 8;
  int str_len = 50;
  int card_num = 0;
  int winner_len = 14;
  int hand_len = 25;
  int cardstr_len = str_len - prefix_len;
  char str[str_len];
  char cardstr[cardstr_len];
  char winner[winner_len];
  char hand[hand_len];
  int sum = 0;
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: cannot open file %s\n", filename);
    return 1;
  }
  // printf("str len %d\n", str_len);
  // printf("card str len %d\n", cardstr_len);

  while (fgets(str, str_len, fp) != NULL) {
    str[strcspn(str, "\n")] = 0;
    strcpy(cardstr, str + prefix_len);
    slice(cardstr, winner, 0, winner_len);
    slice(cardstr, hand, winner_len + 4, winner_len + 2 + hand_len);
  }
  printf("winner %s\n", winner);
  printf("hand %s\n", hand);

  fclose(fp);
  return 0;
}

