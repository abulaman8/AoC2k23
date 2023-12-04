#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void slice(const char *str, char *result, size_t start, size_t end) {
  strncpy(result, str + start, end - start);
  result[end - start] = '\0';
}
int main() {
  int card_num = 0;
  int sum = 0;
  int common = 0;
  int points = 0;
  // ----------------------------------------------
  char filename[16] = "input.txt";
  int prefix_len = 10;
  int str_len = 118;
  int winner_len = 29;
  int hand_len = 74;
  int winner_number_len = 10;
  int hand_number_len = 25;
  // ----------------------------------------------
  // char filename[16] = "testinput.txt";
  // int prefix_len = 8;
  // int str_len = 50;
  // int winner_len = 14;
  // int hand_len = 23;
  // int winner_number_len = 5;
  // int hand_number_len = 8;
  // ----------------------------------------------
  int winner_numbers[winner_number_len];
  int hand_numbers[hand_number_len];
  int cardstr_len = str_len - prefix_len;
  char str[str_len];
  char cardstr[cardstr_len];
  char winner[winner_len];
  char hand[hand_len];
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: cannot open file %s\n", filename);
    return 1;
  }

  while (fgets(str, str_len, fp)) {
    common = 0;
    points = 0;
    card_num++;
    str[strcspn(str, "\n")] = 0;
    strcpy(cardstr, str + prefix_len);
    slice(cardstr, winner, 0, winner_len);
    slice(cardstr, hand, winner_len + 3, winner_len + 3 + hand_len);
    // printf("winner: %s\n", winner);
    // printf("hand: %s\n", hand);
    for (int i = 0; i < winner_number_len; i++) {
      winner_numbers[i] = atoi(winner + i * 3);
    }
    for (int i = 0; i < hand_number_len; i++) {
      hand_numbers[i] = atoi(hand + i * 3);
    }
    // printf("winner numbers: ");
    // for (int i = 0; i < winner_number_len; i++) {
    //   printf("%d ", winner_numbers[i]);
    // }
    // printf("\n");
    // printf("hand numbers: ");
    // for (int i = 0; i < hand_number_len; i++) {
    //   printf("%d ", hand_numbers[i]);
    // }
    // printf("\n");
    for (int i = 0; i < winner_number_len; i++) {
      for (int j = 0; j < hand_number_len; j++) {
        if (winner_numbers[i] == hand_numbers[j]) {
          common++;
        }
      }
    }
    if (common > 0) {
      points = pow(2, common - 1);
    } else {
      points = 0;
    }
    printf("common: %d\n", common);
    printf("points: %d\n", points);
    sum += points;
  }
  printf("sum: %d\n", sum);
  printf("card_num: %d\n", card_num);


  fclose(fp);
  return 0;
}
