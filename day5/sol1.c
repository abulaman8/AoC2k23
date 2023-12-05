#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long walk_x_to_y(long long x, char x_to_y[][256], int x_to_y_len) {
  // printf("starting walk_x_to_y with x: %lld\n", x);
  long long y_number_start, x_number_start, range, y_number_end, x_number_end,
      valid_y_number = -1;
  long long components[3];
  for (int i = 0; i < x_to_y_len; i++) {
    // printf("x_to_y[%d]: %s\n", i, x_to_y[i]);
    char *token = strtok(x_to_y[i], " ");
    int j = 0;
    while (token != NULL) {
      components[j] = atoll(token);
      token = strtok(NULL, " ");
      j++;
    }
    y_number_start = components[0];
    x_number_start = components[1];
    range = components[2];
    y_number_end = y_number_start + range - 1;
    x_number_end = x_number_start + range - 1;
    if (x >= x_number_start && x <= x_number_end) {
      // printf("y_number_start: %lld\n", y_number_start);
      // printf("x_number_start: %lld\n", x_number_start);

      valid_y_number = y_number_start + (x - x_number_start);
      // printf("valid_y_number: %lld\n", valid_y_number);
      break;
    } else
      continue;
  }
  if (valid_y_number == -1) {
    valid_y_number = x;
  }
  return valid_y_number;
}

int main() {
  // ------------------------------------------
  // char filename[16] = "testinput.txt";
  // int seed_2_soil_len = 2;
  // int soil_2_fert_len = 3;
  // int fert_2_water_len = 4;
  // int water_2_light_len = 2;
  // int light_2_temp_len = 3;
  // int temp_2_humid_len = 2;
  // int humid_2_loc_len = 2;
  // int num_seeds = 4;
  // ------------------------------------------
  char filename[16] = "input.txt";
  int seed_2_soil_len = 22;
  int soil_2_fert_len = 28;
  int fert_2_water_len = 48;
  int water_2_light_len = 38;
  int light_2_temp_len = 47;
  int temp_2_humid_len = 40;
  int humid_2_loc_len = 23;
  int num_seeds = 20;
  // ------------------------------------------
  char str[256];
  char seed_str[256];
  long long seeds[num_seeds];
  long long seed_locs[num_seeds];
  long long min_loc = INFINITY;
  char dummy[256];
  char seed_to_soil[seed_2_soil_len][256];
  char soil_to_fert[soil_2_fert_len][256];
  char fert_to_water[fert_2_water_len][256];
  char water_to_light[water_2_light_len][256];
  char light_to_temp[light_2_temp_len][256];
  char temp_to_humid[temp_2_humid_len][256];
  char humid_to_loc[humid_2_loc_len][256];
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: could not open %s\n", filename);
    exit(1);
  }
  fgets(str, 256, fp);
  str[strcspn(str, "\n")] = 0;
  strcpy(str, str + 7);
  strcpy(seed_str, str);
  // printf("%s\n", seed_str);
  char *token = strtok(seed_str, " ");
  int i = 0;
  while (token != NULL) {
    seeds[i] = atoll(token);
    token = strtok(NULL, " ");
    i++;
  }
  // for(int i = 0; i < num_seeds; i++){
  //   printf("%lld\n", seeds[i]);
  // }
  fgets(str, 256, fp);
  fgets(str, 256, fp);
  fgets(str, 256, fp);
  for (int i = 0; i < seed_2_soil_len; i++) {
    fgets(str, 256, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(seed_to_soil[i], str);
  }
  fgets(str, 256, fp);
  fgets(str, 256, fp);
  for (int i = 0; i < soil_2_fert_len; i++) {
    fgets(str, 256, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(soil_to_fert[i], str);
  }
  fgets(str, 256, fp);
  fgets(str, 256, fp);
  for (int i = 0; i < fert_2_water_len; i++) {
    fgets(str, 256, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(fert_to_water[i], str);
  }
  fgets(str, 256, fp);
  fgets(str, 256, fp);
  for (int i = 0; i < water_2_light_len; i++) {
    fgets(str, 256, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(water_to_light[i], str);
  }
  fgets(str, 256, fp);
  fgets(str, 256, fp);
  for (int i = 0; i < light_2_temp_len; i++) {
    fgets(str, 256, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(light_to_temp[i], str);
  }
  fgets(str, 256, fp);
  fgets(str, 256, fp);
  for (int i = 0; i < temp_2_humid_len; i++) {
    fgets(str, 256, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(temp_to_humid[i], str);
  }
  fgets(str, 256, fp);
  fgets(str, 256, fp);
  for (int i = 0; i < humid_2_loc_len; i++) {
    fgets(str, 256, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(humid_to_loc[i], str);
  }
  fclose(fp);
  // printf("seed_to_soil:\n");
  // for (int i = 0; i < seed_2_soil_len; i++) {
  //   printf(" %s\n", seed_to_soil[i]);
  // }
  // printf("soil_to_fert:\n");
  // for (int i = 0; i < soil_2_fert_len; i++) {
  //   printf(" %s\n", soil_to_fert[i]);
  // }
  // printf("fert_to_water:\n");
  // for (int i = 0; i < fert_2_water_len; i++) {
  //   printf(" %s\n", fert_to_water[i]);
  // }
  // printf("water_to_light:\n");
  // for (int i = 0; i < water_2_light_len; i++) {
  //   printf(" %s\n", water_to_light[i]);
  // }
  // printf("light_to_temp:\n");
  // for (int i = 0; i < light_2_temp_len; i++) {
  //   printf(" %s\n", light_to_temp[i]);
  // }
  // printf("temp_to_humid:\n");
  // for (int i = 0; i < temp_2_humid_len; i++) {
  //   printf(" %s\n", temp_to_humid[i]);
  // }
  // printf("humid_to_loc:\n");
  // for (int i = 0; i < humid_2_loc_len; i++) {
  //   printf(" %s\n", humid_to_loc[i]);
  // }

  for (int i = 0; i < num_seeds; i++) {
    char seed_to_soil_copy[seed_2_soil_len][256];
    char soil_to_fert_copy[soil_2_fert_len][256];
    char fert_to_water_copy[fert_2_water_len][256];
    char water_to_light_copy[water_2_light_len][256];
    char light_to_temp_copy[light_2_temp_len][256];
    char temp_to_humid_copy[temp_2_humid_len][256];
    char humid_to_loc_copy[humid_2_loc_len][256];
    for (int j = 0; j < seed_2_soil_len; j++) {
      strcpy(seed_to_soil_copy[j], seed_to_soil[j]);
    }
    for (int j = 0; j < soil_2_fert_len; j++) {
      strcpy(soil_to_fert_copy[j], soil_to_fert[j]);
    }
    for (int j = 0; j < fert_2_water_len; j++) {
      strcpy(fert_to_water_copy[j], fert_to_water[j]);
    }
    for (int j = 0; j < water_2_light_len; j++) {
      strcpy(water_to_light_copy[j], water_to_light[j]);
    }
    for (int j = 0; j < light_2_temp_len; j++) {
      strcpy(light_to_temp_copy[j], light_to_temp[j]);
    }
    for (int j = 0; j < temp_2_humid_len; j++) {
      strcpy(temp_to_humid_copy[j], temp_to_humid[j]);
    }
    for (int j = 0; j < humid_2_loc_len; j++) {
      strcpy(humid_to_loc_copy[j], humid_to_loc[j]);
    }

    // printf("seed: %lld\n", seeds[i]);
    seed_locs[i] = walk_x_to_y(seeds[i], seed_to_soil_copy, seed_2_soil_len);
    // printf(" soil: %lld\n", seed_locs[i]);
    seed_locs[i] =
        walk_x_to_y(seed_locs[i], soil_to_fert_copy, soil_2_fert_len);
    // printf(" fert: %lld\n", seed_locs[i]);
    seed_locs[i] =
        walk_x_to_y(seed_locs[i], fert_to_water_copy, fert_2_water_len);
    // printf(" water: %lld\n", seed_locs[i]);
    seed_locs[i] =
        walk_x_to_y(seed_locs[i], water_to_light_copy, water_2_light_len);
    // printf(" light: %lld\n", seed_locs[i]);
    seed_locs[i] =
        walk_x_to_y(seed_locs[i], light_to_temp_copy, light_2_temp_len);
    // printf(" temp: %lld\n", seed_locs[i]);
    seed_locs[i] =
        walk_x_to_y(seed_locs[i], temp_to_humid_copy, temp_2_humid_len);
    // printf(" humid: %lld\n", seed_locs[i]);
    seed_locs[i] =
        walk_x_to_y(seed_locs[i], humid_to_loc_copy, humid_2_loc_len);
    // printf(" loc: %lld\n", seed_locs[i]);
  }
  for (int i = 0; i < num_seeds; i++) {
    printf("seed: %lld => loc: %lld\n", seeds[i], seed_locs[i]);
  }

  for (int i = 0; i < num_seeds; i++) {
    if (seed_locs[i] < min_loc) {
      min_loc = seed_locs[i];
    }
  }

  printf("min_loc: %lld\n", min_loc);

  return 0;
}
