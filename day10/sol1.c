#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define ROWS 5
// #define COLS 5

#define ROWS 140
#define COLS 140

typedef struct Tile {
  int id;
  char type;
  struct Tile *north;
  struct Tile *south;
  struct Tile *east;
  struct Tile *west;
} Tile;

typedef struct TileGraph {
  Tile *tiles[ROWS][COLS];
  int numtiles;
} TileGraph;

void *CreateTile(int id, char type) {
  Tile *tile = malloc(sizeof(Tile));
  tile->id = id;
  tile->type = type;
  tile->north = NULL;
  tile->south = NULL;
  tile->east = NULL;
  tile->west = NULL;
  return tile;
}

TileGraph *CreateTileGraph() {
  TileGraph *graph = malloc(sizeof(TileGraph));
  graph->numtiles = 0;
  return graph;
}

void AddTile(TileGraph *graph, Tile *tile) {
  graph->tiles[graph->numtiles / ROWS][graph->numtiles % COLS] = tile;
  graph->numtiles++;
}

TileGraph *ConstructTileGraph(TileGraph *graph, char grid[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      // printf(" grid value at row %d, column %d is %c", i, j, grid[i][j]);
      int id = i * ROWS + j;
      // printf(" id is %d\n", id);
      Tile *tile = CreateTile(id, grid[i][j]);
      // printf(" tile created\n");
      AddTile(graph, tile);
    }
  }
  return graph;
}

Tile *GetTile(TileGraph *graph, int id) {
  return graph->tiles[id / ROWS][id % COLS];
}

Tile *GetNorth(TileGraph *graph, int id) {
  if (id < ROWS) {
    return NULL;
  }
  return GetTile(graph, id - ROWS);
}

Tile *GetSouth(TileGraph *graph, int id) {
  if (id >= (ROWS - 1) * COLS) {
    return NULL;
  }
  return GetTile(graph, id + ROWS);
}

Tile *GetEast(TileGraph *graph, int id) {
  if (id % COLS == COLS - 1) {
    return NULL;
  }
  return GetTile(graph, id + 1);
}

Tile *GetWest(TileGraph *graph, int id) {
  if (id % COLS == 0) {
    return NULL;
  }
  return GetTile(graph, id - 1);
}

TileGraph *AddEdges(TileGraph *graph) {
  for (int i = 0; i < graph->numtiles; i++) {
    Tile *tile = GetTile(graph, i);
    if (tile->type == '|') {
      tile->north = GetNorth(graph, i);
      tile->south = GetSouth(graph, i);
    }
    if (tile->type == '-') {
      tile->east = GetEast(graph, i);
      tile->west = GetWest(graph, i);
    }
    if (tile->type == 'L') {
      tile->north = GetNorth(graph, i);
      tile->east = GetEast(graph, i);
    }
    if (tile->type == 'J') {
      tile->north = GetNorth(graph, i);
      tile->west = GetWest(graph, i);
    }
    if (tile->type == '7') {
      tile->south = GetSouth(graph, i);
      tile->west = GetWest(graph, i);
    }
    if (tile->type == 'F') {
      tile->south = GetSouth(graph, i);
      tile->east = GetEast(graph, i);
    }
    if (tile->type == 'S') {
      Tile *north = GetNorth(graph, i);
      Tile *south = GetSouth(graph, i);
      Tile *east = GetEast(graph, i);
      Tile *west = GetWest(graph, i);
      if (north != NULL && (north->type == '|' || north->type == '7' || north->type == 'F')) {
        tile->north = north;
      }
      if (south != NULL && (south->type == '|' || south->type == 'L' || south->type == 'J')) {
        tile->south = south;
      }
      if (east != NULL && (east->type == '-' || east->type == '7' || east->type == 'J')) {
        tile->east = east;
      }
      if (west != NULL && (west->type == '-' || west->type == 'L' || west->type == 'F')) {
        tile->west = west;
      }
    }
  }
  return graph;
}

void PrintTileGraph(TileGraph *graph) {
  for (int i = 0; i < graph->numtiles; i++) {
    Tile *tile = GetTile(graph, i);
    printf("Tile %d: %c\n", tile->id, tile->type);
    if (tile->north != NULL) {
      printf("  North: %d\n", tile->north->id);
    }
    if (tile->south != NULL) {
      printf("  South: %d\n", tile->south->id);
    }
    if (tile->east != NULL) {
      printf("  East: %d\n", tile->east->id);
    }
    if (tile->west != NULL) {
      printf("  West: %d\n", tile->west->id);
    }
  }
}

int WalkGraph(TileGraph *graph, Tile *start, Tile *end, Tile *parent) {
  Tile *current = start;
  int steps = 0;
  do {
    Tile *options[] = {current->north, current->south, current->east,
                       current->west};
    Tile *validOption;
    for (int i = 0; i < 4; i++) {
      if (options[i] != NULL && options[i] != parent) {
        validOption = options[i];
        break;
      }
    }
    if (validOption == NULL) {
      return 0;
    }
    parent = current;
    current = validOption;
    steps++;
  }
  while (current != end);
  return steps;
}

int main() {
  // char filename[16] = "testinput.txt";
  char filename[16] = "input.txt";
  char str[256];
  int numlines = 0;
  char grid[ROWS][COLS];
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Could not open file %s", filename);
    return 1;
  }
  int i = 0;
  while (fgets(str, sizeof(str), fp) != NULL) {
    str[strcspn(str, "\n")] = 0;
    // printf("%s\n", str);
    strcpy(grid[i], str);
    i++;
  }
  // for (int i = 0; i < ROWS; i++) {
  //   for (int j = 0; j < COLS; j++) {
  //     printf("%c", grid[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("-----------------\n");
  TileGraph *graph = CreateTileGraph();
  ConstructTileGraph(graph, grid);
  graph = AddEdges(graph);
  // PrintTileGraph(graph);
  Tile *start;
  for (int i = 0; i < graph->numtiles; i++) {
    Tile *tile = GetTile(graph, i);
    if (tile->type == 'S'){
      start = tile;
      break;

    }
  }
  int steps = WalkGraph(graph, start, start, NULL);
  int farthest = steps/2;
  printf("Farthest: %d\n", farthest);


  return 0;
}
