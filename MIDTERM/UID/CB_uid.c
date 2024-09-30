#include <stdio.h>
#include <stdlib.h>
#define MAX 8

typedef int STACK;

typedef struct {
  int data;
  int link;
} NodeType;

typedef struct node {
  NodeType Nodes[MAX];
  int Avail;
} VirtualHeap;