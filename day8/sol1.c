#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void slice(const char *str, char *result, size_t start, size_t end) {
  strncpy(result, str + start, end - start);
  result[end - start] = '\0';
}

typedef struct Node {
  char name[4];
  struct Node *left;
  struct Node *right;
} Node;

Node *findNodeByName(char name[4], Node *graph[17576], int *graphIndex) {
  for (int i = 0; i < *graphIndex; i++) {
    if (strcmp(graph[i]->name, name) == 0) {
      return graph[i];
    }
  }
  return NULL;
}

Node *createNode(char name[4], Node *graph[17576], int *graphIndex) {
  for (int i = 0; i < *graphIndex+1; i++) {
    if (graph[i] != NULL && strcmp(graph[i]->name, name) == 0) {
      return graph[i];
    }
  }
  Node *node = (Node *)malloc(sizeof(Node));
  strcpy(node->name, name);
  node->left = NULL;
  node->right = NULL;
  graph[*graphIndex] = node;
  *graphIndex += 1;
  return node;
}


void addEdge(Node *sourceNode, Node *destNode, Node *graph[17576], int *graphIndex, char direction) {
  if (direction == 'L') {
    sourceNode->left = destNode;
  } else {
    sourceNode->right = destNode;
  }
}


void printGraph(Node *graph[17576], int *graphIndex) {
  for (int i = 0; i < *graphIndex; i++) {
    if (isalpha(graph[i]->name[0]) && isalpha(graph[i]->name[1]) &&
        isalpha(graph[i]->name[2])) {
      printf("%s\n", graph[i]->name);
      if (graph[i]->left != NULL) {
        printf(" left: %s\n", graph[i]->left->name);
      }
      if (graph[i]->right != NULL) {
        printf(" right: %s\n", graph[i]->right->name);
      }
    }
  }
}

int walkGraph(Node *graph[17576], char *instructions, Node *startNode, Node *endNode, int steps) {
  Node *currentNode = startNode;
  int len = strlen(instructions);
  int i = 0;
  // for (; i < strlen(instructions); i++) {
  for (; i < len; i++) {
    if (currentNode == endNode) {
      return steps;
    } else {
      printf("currentNode: %s\n", currentNode->name);
      if (instructions[i] == 'L') {
        printf("Direction: %c\n", instructions[i]);
        printf("Next: %s\n", currentNode->left->name);
        currentNode = currentNode->left;
        steps++;
      } else if (instructions[i] == 'R') {
        printf("Direction: %c\n", instructions[i]);
        printf("Next: %s\n", currentNode->right->name);
        currentNode = currentNode->right;
        steps++;
      }
    }
  }

  return walkGraph(graph, instructions, currentNode, endNode, steps);
}

int main() {
  // char filename[16] = "testinput2.txt";
  // char filename[16] = "testinput.txt";
  char filename[16] = "input.txt";
  char str[32];
  char instructions[512];
  Node *graph[17576];
  int graphIndex = 0;
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("File not found!\n");
    exit(1);
  }
  fgets(instructions, 512, fp);
  fgets(str, 32, fp);
  fgets(str, 32, fp);
  char nodeName[4];
  char rightNodeName[4];
  char leftNodeName[4];
  slice(str, nodeName, 0, 3);
  nodeName[3] = '\0';
  slice(str, leftNodeName, 7, 10);
  leftNodeName[3] = '\0';
  slice(str, rightNodeName, 12, 15);
  rightNodeName[3] = '\0';
  // printf("node: %s\n", nodeName);
  // printf(" left: %s\n", leftNodeName);
  // printf(" right: %s\n", rightNodeName);
  Node *node = createNode(nodeName, graph, &graphIndex);
  Node *LeftNode = createNode(leftNodeName, graph, &graphIndex);
  Node *RightNode = createNode(rightNodeName, graph, &graphIndex);
  addEdge(node, LeftNode, graph, &graphIndex, 'L');
  addEdge(node, RightNode, graph, &graphIndex, 'R');


  while (fgets(str, 32, fp) != NULL) {
    str[strlen(str) - 1] = '\0';
    // printf("%s\n", str);
    char nodeName[4];
    char rightNodeName[4];
    char leftNodeName[4];
    slice(str, nodeName, 0, 3);
    nodeName[3] = '\0';
    slice(str, leftNodeName, 7, 10);
    leftNodeName[3] = '\0';
    slice(str, rightNodeName, 12, 15);
    rightNodeName[3] = '\0';
    Node *node = createNode(nodeName, graph, &graphIndex);
    Node *LeftNode = createNode(leftNodeName, graph, &graphIndex);
    Node *RightNode = createNode(rightNodeName, graph, &graphIndex);
    addEdge(node, LeftNode, graph, &graphIndex, 'L');
    addEdge(node, RightNode, graph, &graphIndex, 'R');
    // printf("node: %s\n", nodeName);
    // printf(" left: %s\n", leftNodeName);
    // printf(" right: %s\n", rightNodeName);
  }
  printGraph(graph, &graphIndex);
  Node *startNode = findNodeByName("AAA", graph, &graphIndex);
  Node *endNode = findNodeByName("ZZZ", graph, &graphIndex);
  printf("Instructions: %s\n", instructions);
  int steps = walkGraph(graph, instructions, startNode, endNode, 0);
  printf("Steps: %d\n", steps);
  fclose(fp);
  return 0;
}
