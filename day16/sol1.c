#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tile {
  // int x;
  // int y;
  char type;
  int energized;
  struct Tile *north;
  struct Tile *east;
  struct Tile *south;
  struct Tile *west;

} Tile;

typedef enum { NORTH, EAST, SOUTH, WEST } Direction;

void printGrid(Tile **grid, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      Tile tile = grid[i][j];
      printf("row: %d, col: %d, type: %c, energized: %d\n", i, j, tile.type,
             tile.energized);
    }
  }
}

Tile *get_north(Tile **grid, int row, int col, int max_row, int max_col) {
  if (row == 0) {
    return NULL;
  }
  return &grid[row - 1][col];
}
Tile *get_east(Tile **grid, int row, int col, int max_row, int max_col) {
  if (row == max_col) {
    return NULL;
  }
  return &grid[row][col + 1];
}
Tile *get_south(Tile **grid, int row, int col, int max_row, int max_col) {
  if (row == max_row) {
    return NULL;
  }
  return &grid[row + 1][col];
}
Tile *get_west(Tile **grid, int row, int col, int max_row, int max_col) {
  if (row == 0) {
    return NULL;
  }
  return &grid[row][col - 1];
}

void update_position(int *row, int *col, Direction d, int max_rows,
                     int max_cols) {
  switch (d) {
  case NORTH:
    if (*row != 0) {
      row--;
    }
    break;
  case EAST:
    if (*col != max_cols - 1) {
      col++;
    }
    break;
  case SOUTH:
    if (*row != max_rows - 1) {
      row++;
    }
    break;
  case WEST:
    if (*col != 0) {
      col--;
    }
    break;
  }
}

int find_energized_tile_count(Tile **grid, int start_row, int start_col, Direction start_direction, int rows, int cols,
                              Tile *processed_tiles, int num_processed) {
  int current_row = start_row;
  int current_col = start_col;
  Direction direction = start_direction;
  int tile_count = 0;
  int end = 0;
  char current_type = grid[current_row][current_col].type;
  do {
    if (current_type == '.') {
      tile_count++;
      update_position(&current_row, &current_col, direction, rows, cols);
    } else if (current_type == '\\') {
      switch (direction) {
      case NORTH:
        direction = WEST;
        update_position(&current_row, &current_col, direction, rows, cols);
        break;
      case EAST:
        direction = SOUTH;
        update_position(&current_row, &current_col, direction, rows, cols);
        break;
      case SOUTH:
        direction = EAST;
        update_position(&current_row, &current_col, direction, rows, cols);
        break;
      case WEST:
        direction = NORTH;
        update_position(&current_row, &current_col, direction, rows, cols);
        break;
      }
    }else if (current_type == '/') {
      switch (direction) {
      case NORTH:
        direction = EAST;
        update_position(&current_row, &current_col, direction, rows, cols);
        break;
      case EAST:
        direction = NORTH;
        update_position(&current_row, &current_col, direction, rows, cols);
        break;
      case SOUTH:
        direction = WEST;
        update_position(&current_row, &current_col, direction, rows, cols);
        break;
      case WEST:
        direction = SOUTH;
        update_position(&current_row, &current_col, direction, rows, cols);
        break;
      }
    }

  } while (!end);
  return tile_count;
}

int main() {
  char filename[16] = "testinput.txt";
  int rows = 10;
  int cols = 11;
  FILE *fp = fopen(filename, "r");
  char str[cols];
  int tile_count = 0;
  Tile **grid = NULL;
  int row_count = 0;
  while (fgets(str, cols + 1, fp) != NULL) {
    str[strlen(str) - 1] = '\0';
    int len = strlen(str);
    printf("%s\n", str);
    grid = realloc(grid, (row_count + 1) * sizeof(Tile *));
    grid[row_count] = realloc(grid[row_count], len * sizeof(Tile));
    for (int i = 0; i < strlen(str); i++) {
      Tile new_tile = {str[i], 0, NULL, NULL, NULL, NULL};
      grid[row_count][i] = new_tile;
      tile_count++;
    }
    row_count++;
  }
  printGrid(grid, row_count, cols - 1);
}
