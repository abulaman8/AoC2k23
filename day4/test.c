#include <stdio.h>

struct Card {
  int id;
  int common;
  int times;
};

void updateTimes(struct Card cards[], int cardIndex) {
  if (cards[cardIndex].common == 0) {
    return;
  }

  for (int j = 0; j < cards[cardIndex].times; j++) {
    for (int i = 1; i <= cards[cardIndex].common; i++) {
      int nextCardIndex = cardIndex + i;
      if (nextCardIndex < 6) {
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

int main() {
  struct Card cards[6];
  struct Card card1 = {1, 4, 1};
  struct Card card2 = {2, 2, 1};
  struct Card card3 = {3, 2, 1};
  struct Card card4 = {4, 1, 1};
  struct Card card5 = {5, 0, 1};
  struct Card card6 = {6, 0, 1};
  cards[0] = card1;
  cards[1] = card2;
  cards[2] = card3;
  cards[3] = card4;
  cards[4] = card5;
  cards[5] = card6;

  updateAllCards(cards, 6);
  int sum = 0;
  for (int i = 0; i < 6; i++) {
    printf("card %d: %d\n", cards[i].id, cards[i].times);
    sum += cards[i].times;
  }
  printf("sum: %d\n", sum);

  return 0;
}
