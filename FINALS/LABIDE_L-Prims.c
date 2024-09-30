#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define VISITED -1
#define UNVISITED -2
#define SENTINEL INT_MAX
typedef int set[MAX];

typedef struct {
  int head;
  int tail;
  int weight;
} adjType;

typedef struct node {
  adjType elem;
  struct node *link;
} *ptr, nodeType;

typedef struct {
  int elem[MAX];
  int front, rear;
} Queue;

typedef struct {
  ptr adjList[MAX];
  int edgecount;
} Graph;

typedef struct {
  adjType edgeList[MAX];
  int count;
  int minCost;
} MST;

Queue initQueue();
void initGraph(Graph *G);
void addEdge(Graph *G, adjType A);
void initGraph(Graph *G);
void displayGraph(Graph G);
void printMST(MST T);
MST prims(Graph G, int start);

int main() {

    Graph G;
    initGraph(&G);

  adjType A = {4, 5, 1};
  adjType B = {4, 6, 10};
  adjType C = {5, 1, 4};
  adjType D = {5, 6, 9};
  adjType E = {6, 3, 1};
  adjType F = {3, 2, 5};
  adjType F1 = {1, 3, 10};
  adjType H = {1, 2, 8};
  adjType I = {1, 0, 19};
  adjType J = {3, 0, 17};
  adjType K = {0, 2, 3};

  addEdge(&G, A);
  addEdge(&G, B);
  addEdge(&G, C);
  addEdge(&G, D);
  addEdge(&G, E);
  addEdge(&G, F);
  addEdge(&G, F1);
  addEdge(&G, H);
  addEdge(&G, I);
  addEdge(&G, J);
  addEdge(&G, K);


  displayGraph(G);
  MST Tree = prims(G, 4);
  printMST(Tree);
  
}
Queue initQueue() {
  Queue Q;
  Q.front = 0;
  Q.rear = 0;

  return Q;
}

void initGraph(Graph *G) {
  int i;
  for (i = 0; i < MAX; i++) {
    G->adjList[i] = NULL;
  }
}

void addEdge(Graph *G, adjType A) {
  ptr newNode = (ptr)malloc(sizeof(nodeType));
  ptr newNode2 = (ptr)malloc(sizeof(nodeType));

  if (newNode != NULL && newNode2 != NULL) {
    newNode->elem.head = A.tail;
    newNode->elem.weight = A.weight;
    newNode->link = G->adjList[A.head];
    G->adjList[A.head] = newNode;

    newNode2->elem.head = A.head;
    newNode2->elem.weight = A.weight;
    newNode2->link = G->adjList[A.tail];
    G->adjList[A.tail] = newNode2;

    G->edgecount++;
  }
}
void displayGraph(Graph G) {
  printf("\n\nThe Adjacency List ::");
  printf("\n%-8s", "VERTEX");
  printf("%-20s", "Adjacent vertices (weight)");
  printf("\n%-8s", "------");
  printf("%-20s", "------------------------");

  ptr trav;
  int i;
  for (i = 0; i < MAX; i++) {
    printf("\n%-8d", i);
    for (trav = G.adjList[i]; trav != NULL; trav = trav->link) {
      printf(" -> [(%d)(%d)]", trav->elem.head, trav->elem.weight);
    }
  }
}

MST prims(Graph G, int start){
    MST T; T.count = 0; T.minCost=0;
    int U[MAX];
    ptr trav; int i;
    for(i = 0; i < MAX; i++){ //Universal Set set to all 0
        U[i] = 0;
    }
    U[start] = 1;

    while(T.count < MAX-1){
        int head= - 1, tail = -1, weight = SENTINEL;
        for(i = 1; i < MAX; i++){
            if(U[i]){
                for(trav = G.adjList[i]; trav!=NULL; trav = trav->link){
                    if(!U[trav->elem.head] && trav->elem.weight < weight){
                        head = i;
                        tail = trav->elem.head;
                        weight = trav->elem.weight;
                    }
                }
            }
        }
        if(weight != SENTINEL){
            U[tail] = 1;
            T.edgeList[T.count].head = head;
            T.edgeList[T.count].tail = tail;
            T.edgeList[T.count].weight = weight;
            T.count++;
            T.minCost+=weight;
        }else{
            break;
        }
    }
    return T;
}

void printMST(MST T) {
  printf("Starting Vertex is %d\n", T.edgeList[0].head);
  printf("%-5s", "Edge");
  printf("%-5s", "Weight");
  int i, j;
  for (i = 0; i < T.count; i++) {
    printf("\n(%d,%d)", T.edgeList[i].head, T.edgeList[i].tail);
    printf(" %3d", T.edgeList[i].weight);
  }
  printf("\nMinimum Cost: %d\n", T.minCost);
}