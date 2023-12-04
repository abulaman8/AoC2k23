#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------------------------------------------
char filename[16] = "input.txt";
int prefix_len = 10;
int str_len = 118;
int winner_len = 29;
int hand_len = 74;
const int winner_number_len = 10;
const int hand_number_len = 25;
// ----------------------------------------------
// char filename[16] = "testinput.txt";
// int prefix_len = 8;
// int str_len = 50;
// int winner_len = 14;
// int hand_len = 23;
// int winner_number_len = 5;
// int hand_number_len = 8;
// ----------------------------------------------

struct Card {
  int id;
  int common;
  int times;
};

struct Card cards[223];

void updateTimes(struct Card cards[], int cardIndex) {
  if (cards[cardIndex].common == 0) {
    return;
  }

  for (int j = 0; j < cards[cardIndex].times; j++) {
    for (int i = 1; i <= cards[cardIndex].common; i++) {
      int nextCardIndex = cardIndex + i;
      if (nextCardIndex < 223) {
        cards[nextCardIndex].times += 1;
      } else {
        break;
      }
    }
  }
}

void updateAllCards(struct Card cards[], int numCards) {
  for (int i = 0; i < numCards; i++) {
    updateTimes(cards, i);
  }
}

void slice(const char *str, char *result, size_t start, size_t end) {
  strncpy(result, str + start, end - start);
  result[end - start] = '\0';
}
int main() {
  int card_num = 0;
  int sum = 0;
  int common = 0;
  int points = 0;
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
    for (int i = 0; i < winner_number_len; i++) {
      winner_numbers[i] = atoi(winner + i * 3);
    }
    for (int i = 0; i < hand_number_len; i++) {
      hand_numbers[i] = atoi(hand + i * 3);
    }
    for (int i = 0; i < winner_number_len; i++) {
      for (int j = 0; j < hand_number_len; j++) {
        if (winner_numbers[i] == hand_numbers[j]) {
          common++;
        }
      }
    }
    struct Card card = {.id = card_num, .common = common, .times = 1};
    cards[card_num - 1] = card;
  }



  fclose(fp);
  updateAllCards(cards, 223);
  for (int i = 0; i < 223; i++) {
    printf("card %d: %d\n", cards[i].id, cards[i].times);
    sum += cards[i].times;
  }
  printf("sum: %d\n", sum);
  return 0;
}
