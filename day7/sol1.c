#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_five_of_a_kind(char *hand) {
  char cards[14] = "AKQJT98765432";
  cards[13] = '\0';
  int counts[14] = {0};
  for (int i = 0; i<5; i++){
    for (int j = 0; j < 14; j++) {
      if (hand[i] == cards[j]) {
        if (hand[i] == cards[j]) {
          counts[j]++;
        }
      }
    }
  }
  for (int i = 0; i < 14; i++) {
    if (counts[i] == 5) {
      return 1;
    }
  }
  return 0;
}

int is_four_of_a_kind(char *hand) {
  char cards[14] = "AKQJT98765432";
  cards[13] = '\0';
  int counts[14] = {0};
  for (int i = 0; i<5; i++){
    for (int j = 0; j < 14; j++) {
      if (hand[i] == cards[j]) {
        if (hand[i] == cards[j]) {
          counts[j]++;
        }
      }
    }
  }
  for (int i = 0; i < 14; i++) {
    if (counts[i] == 4) {
      return 1;
    }
  }
  return 0;
}

int is_full_house(char *hand) {
  char cards[14] = "AKQJT98765432";
  int triple_found = 0;
  int double_found = 0;
  cards[13] = '\0';
  int counts[14] = {0};
  for (int i = 0; i<5; i++){
    for (int j = 0; j < 14; j++) {
      if (hand[i] == cards[j]) {
        if (hand[i] == cards[j]) {
          counts[j]++;
        }
      }
    }
  }
  for (int i = 0; i < 14; i++) {
    if (counts[i] == 3) {
      triple_found = 1;
    } else if (counts[i] == 2) {
      double_found = 1;
    }
  }
  if (triple_found && double_found) {
    return 1;
  }
  return 0;
}


int is_three_of_a_kind(char *hand) {
  char cards[14] = "AKQJT98765432";
  int triple_found = 0;
  int double_found = 0;
  cards[13] = '\0';
  int counts[14] = {0};
  for (int i = 0; i<5; i++){
    for (int j = 0; j < 14; j++) {
      if (hand[i] == cards[j]) {
        if (hand[i] == cards[j]) {
          counts[j]++;
        }
      }
    }
  }
  for (int i = 0; i < 14; i++) {
    if (counts[i] == 3) {
      triple_found = 1;
    } else if (counts[i] == 2) {
      double_found = 1;
    }
  }
  if (triple_found && !double_found) {
    return 1;
  }
  return 0;
}

int is_two_pairs(char *hand) {
  char cards[14] = "AKQJT98765432";
  cards[13] = '\0';
  int counts[14] = {0};
  int pairs_found = 0;
  for (int i = 0; i<5; i++){
    for (int j = 0; j < 14; j++) {
      if (hand[i] == cards[j]) {
        if (hand[i] == cards[j]) {
          counts[j]++;
        }
      }
    }
  }
  for (int i = 0; i < 14; i++) {
    if (counts[i] == 2) {
      pairs_found++;
    }
  }
  if (pairs_found == 2) {
    return 1;
  }
  return 0;

}

int is_one_pair(char *hand) {
  char cards[14] = "AKQJT98765432";
  cards[13] = '\0';
  int counts[14] = {0};
  int pairs_found = 0;
  for (int i = 0; i<5; i++){
    for (int j = 0; j < 14; j++) {
      if (hand[i] == cards[j]) {
        if (hand[i] == cards[j]) {
          counts[j]++;
        }
      }
    }
  }
  for (int i = 0; i < 14; i++) {
    if (counts[i] == 2) {
      pairs_found++;
    }
  }
  if (pairs_found == 1) {
    return 1;
  }
  return 0;
}


int is_high_card(char *hand) {
  char cards[14] = "AKQJT98765432";
  cards[13] = '\0';
  int counts[14] = {0};
  int distinct_cards = 0;
  for (int i = 0; i<5; i++){
    for (int j = 0; j < 14; j++) {
      if (hand[i] == cards[j]) {
        if (hand[i] == cards[j]) {
          counts[j]++;
        }
      }
    }
  }
  for (int i = 0; i < 14; i++) {
    if (counts[i] == 1) {
      distinct_cards++;
    }
  }
  if (distinct_cards == 5) {
    return 1;
  }

  return 0;
}

int compare_lines(const void *a, const void *b) {
  char *pa = *(char (*)[6])a;
  char *pb = *(char (*)[6])b;

  // printf("pa: %s\n", pa);
  // printf("pb: %s\n", pb);
  char pa_split[6];
  char pb_split[6];
  strncpy(pa_split, pa, 5);
  pa_split[5] = '\0';
  // printf(" pa_split: %s\n", pa_split);
  strncpy(pb_split, pb, 5);
  pb_split[5] = '\0';
  // printf(" pb_split: %s\n", pb_split);
  int pa_rank[7], pb_rank[7];
  char card_order[14] = "AKQJT98765432";
  card_order[13] = '\0';
  // char *pa_split = strtok(pa_split, " ");
  // char *pb_split = strtok(pb_split, " ");
  pa_rank[0] = is_five_of_a_kind(pa_split);
  pa_rank[1] = is_four_of_a_kind(pa_split);
  pa_rank[2] = is_full_house(pa_split);
  pa_rank[3] = is_three_of_a_kind(pa_split);
  pa_rank[4] = is_two_pairs(pa_split);
  pa_rank[5] = is_one_pair(pa_split);
  pa_rank[6] = is_high_card(pa_split);
  pb_rank[0] = is_five_of_a_kind(pb_split);
  pb_rank[1] = is_four_of_a_kind(pb_split);
  pb_rank[2] = is_full_house(pb_split);
  pb_rank[3] = is_three_of_a_kind(pb_split);
  pb_rank[4] = is_two_pairs(pb_split);
  pb_rank[5] = is_one_pair(pb_split);
  pb_rank[6] = is_high_card(pb_split);
  // for (int i = 0; i < 7; i++) {
  //   printf(" pa_rank[%d]: %d\n", i, pa_rank[i]);
  //   printf(" pb_rank[%d]: %d\n", i, pb_rank[i]);
  // }

  for (int i = 0; i < 7; i++) {
    if (pa_rank[i] > pb_rank[i]) {
      // printf("no ties found\n");
      return 1;
    } else if (pa_rank[i] < pb_rank[i]) {
      // printf("no ties found\n");
      return -1;
    }
  }
  // printf("ties found, breaking ties\n");
  for (int i = 0; i < 5; i++) {
    if (strchr(card_order, pa[i]) > strchr(card_order, pb[i])) {
      return -1;
    } else if (strchr(card_order, pa[i]) < strchr(card_order, pb[i])) {
      return 1;
    }
  }
  return 0; // never reached
}


int main() {
  // char filename[16] = "testinput.txt";
  // int num_lines = 5;
  char filename[16] = "input.txt";
  int num_lines = 1000;
  char str[16];
  char hand[6];
  int bid = 0;
  char hands[num_lines][6];
  int bids[num_lines];
  char lines[num_lines][16];
  int sum = 0;
  int rank = 0;
  int val = 0;
  int i = 0;
  int k = 0;
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("File not found!\n");
    return 0;
  }
  while (fgets(str, 16, fp) != NULL) {
    str[strcspn(str, "\n")] = 0;
    strcpy(lines[i], str);
    i++;
  }
  qsort(lines, num_lines, sizeof(lines[0]), compare_lines);
  for (int j = 0; j < num_lines; j++) {
    k = 0;
    printf("%s\n", lines[j]);
    char *token = strtok(lines[j], " ");

    while (k < 2) {
      if (k == 0) {
        strcpy(hand, token);
        // printf(" hand: %s\n", hand);
      } else if (k == 1) {
        bid = atoi(token);
        // printf(" bid: %d\n", bid);
      }
      token = strtok(NULL, " ");
      k++;
    }
    rank = j + 1;
    val = rank * bid;
    sum += val;
    printf(" hand: %s\n", hand);
    printf(" bid: %d\n", bid);
    printf(" rank: %d\n", rank);
    printf(" val: %d\n", val);
  }
  printf("sum: %d\n", sum);

  fclose(fp);

  return 0;
}
