#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INF INT_MAX
#define V 7
typedef int Graph[V][V];
typedef int set[V];

typedef struct {
  int head, tail, weight;
} Edge;

typedef struct MST {
  Edge edgelist[V];
  int edgeCount;
  int minCost;
} MST;

MST kruskals(Graph G);
void printMST(MST T);
int main() {

  int graph[V][V] = {
      {INF, 19, 3, 17, INF, INF, INF},  {19, INF, 8, 10, INF, 4, INF},
      {3, 8, INF, 5, INF, INF, INF},    {17, 10, 5, INF, INF, INF, 1},
      {INF, INF, INF, INF, INF, 1, 10}, {INF, 4, INF, INF, 1, INF, 9},
      {INF, INF, INF, 1, 10, 9, INF}};

  MST T = kruskals(graph);
  printMST(T);

  return 0;
}

MST kruskals(Graph G) {
  MST T;T.edgeCount = 0;T.minCost = 0;
  int Edgcounter = 0, i, j, head, tail, weight;
  Edge edges[V * V];
  for (i = 0; i < V; i++) {
    for (j = 0; j < V; j++) {
      if (G[i][j] != INF) {
        edges[Edgcounter].head = i;
        edges[Edgcounter].tail = j;
        edges[Edgcounter].weight = G[i][j];
        Edgcounter++;
      }
    }
  }
  for (i = 0; i < V; i++) { // Bubble Sort
    for (j = 0; j < V; j++) {
      if (edges[j].weight > edges[j + 1].weight) {
        Edge temp = edges[j];
        edges[j] = edges[j + 1];
        edges[j + 1] = temp;
      }
    }
  }
  set U;
  for (i = 0; i < V; i++) { // Universal Set
    U[i] = i;
  }

  for (i = 0; i < Edgcounter && T.edgeCount < V - 1; i++) {
    Edge newEdge = edges[i];
    head = newEdge.head;
    tail = newEdge.tail;
    weight = newEdge.weight;
    while (U[head] != head) {
      head = U[head];
    }
    while (U[tail] != tail) {
      tail = U[tail];
    }

    if (head != tail) {
      T.edgelist[T.edgeCount] = newEdge;
      T.edgeCount++;
      T.minCost += weight;
      U[tail] = head;
    }
  }
  return T;
}
void printMST(MST T) {
  printf("Starting Vertex is %d\n", T.edgelist[0].head);
  printf("%-5s", "Edge");
  printf("%-5s", "Weight");
  int i, j;
  for (i = 0; i < T.edgeCount; i++) {
    printf("\n(%d,%d)", T.edgelist[i].head, T.edgelist[i].tail);
    printf(" %3d", T.edgelist[i].weight);
  }
  printf("\nMinimum Cost: %d\n", T.minCost);
}
