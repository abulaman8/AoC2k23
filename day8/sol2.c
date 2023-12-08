#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void slice(const char *str, char *result, size_t start, size_t end) {
  strncpy(result, str + start, end - start);
  result[end - start] = '\0';
}


long long __gcd(long long a, long long b) {
  if (b == 0)
    return a;
  return __gcd(b, a % b);
}

long long find_lcm(long long *arr, int n) {
  long long ans = arr[0];
  for (int i = 1; i < n; i++) {
    ans = (((arr[i] * ans)) / (__gcd(arr[i], ans)));
  }
  return ans;
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
    if (isalnum(graph[i]->name[0]) && isalnum(graph[i]->name[1]) &&
        isalnum(graph[i]->name[2])) {
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


int is_startNode(Node *node){
  char name[4];
  strcpy(name, node->name);
  name[3] = '\0';
  if (name[2] == 'A'){
    return 1;
  }
  return 0;
}


int is_endNode(Node *node){
  char name[4];
  strcpy(name, node->name);
  name[3] = '\0';
  if (name[2] == 'Z'){
    return 1;
  }
  return 0;
}

int walkGraph(Node *graph[17576], char *instructions, Node *startNode, int steps) {
  Node *currentNode = startNode;
  int len = strlen(instructions);
  int i = 0;
  // for (; i < strlen(instructions); i++) {
  for (; i < len; i++) {
    if (is_endNode((currentNode))) {
      return steps;
    } else {
      // printf("currentNode: %s\n", currentNode->name);
      if (instructions[i] == 'L') {
        // printf("Direction: %c\n", instructions[i]);
        // printf("Next: %s\n", currentNode->left->name);
        currentNode = currentNode->left;
        steps++;
      } else if (instructions[i] == 'R') {
        // printf("Direction: %c\n", instructions[i]);
        // printf("Next: %s\n", currentNode->right->name);
        currentNode = currentNode->right;
        steps++;
      }
    }
  }

  return walkGraph(graph, instructions, currentNode, steps);
}

int main() {
  // char filename[16] = "testinput2.txt";
  // char filename[16] = "testinput.txt";
  // char filename[16] = "testinput3.txt";
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
  // printf("----------------------------------------\n");
  // printf("node: %s\n", nodeName);
  // printf(" left: %s\n", leftNodeName);
  // printf(" right: %s\n", rightNodeName);
  // printf("----------------------------------------\n");
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
  // printf("----------------------------------------\n");
  //   printf("node: %s\n", nodeName);
  //   printf(" left: %s\n", leftNodeName);
  //   printf(" right: %s\n", rightNodeName);
  // printf("----------------------------------------\n");
  }
  // printf("---------printing full graph-------------\n");
  // printGraph(graph, &graphIndex);
  // printf("-------done printing full graph-----------\n");
  
  Node *start_nodes[10];
  int steps[10];
  int total_starts = 0;
  // printf("graphIndex: %d\n", graphIndex);
  for (int i = 0; i < graphIndex; i++){
    if (is_startNode(graph[i])){
      start_nodes[total_starts] = graph[i];
      total_starts++;
      // printf("start node: %s\n", start_nodes[i]->name);
    }
  }
  printf("Total starts: %d\n", total_starts);
  // printf("Instructions: %s\n", instructions);
  for (int i = 0; i < total_starts; i++){
    printf("Start node: %s\n", start_nodes[i]->name);
    steps[i] = walkGraph(graph, instructions, start_nodes[i], 0);
    printf("Steps: %d\n", steps[i]);
  }
  long long long_steps[10];
  for (int i = 0; i < total_starts; i++){
    long_steps[i] = (long long)steps[i];
  }
  long long lcm = find_lcm(long_steps, total_starts);
  printf("LCM: %lld\n", lcm);
  fclose(fp);
  return 0;
}
