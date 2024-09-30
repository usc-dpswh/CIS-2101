#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define VISITED -1
#define UNVISITED -2
#define SENTINEL INT_MAX
#define INF INT_MAX
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
  int edgeCount;
  int minCost;
} MST;

Queue initQueue();
void initGraph(Graph *G);
void addEdge(Graph *G, adjType A);
void initGraph(Graph *G);
void displayGraph(Graph G);
void printMST(MST T);

MST kruskals(Graph G);

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
  MST T = kruskals(G);
  
  printMST(T);

  
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


MST kruskals(Graph graph) {
    MST new;
    new.edgeCount = 0;
    new.minCost = 0;
    int visited[MAX]; // Corrected initialization
    int x,y,z,u,v,head,tail,minWeight;
    ptr trav;

    for (x = 0; x < MAX; x++) {
        visited[x] = x; // Initialize visited set
    }

    while (new.edgeCount < MAX - 1) {
        minWeight = INF;
        u = -1;
        v = -1;
        
        for (head = 0; head < MAX; head++) {
            for (trav = graph.adjList[head]; trav != NULL; trav = trav->link) {
                if (trav->elem.weight < minWeight) {
                    minWeight = trav->elem.weight;
                    u = head;
                    v = trav->elem.head;
                }
            }
        }
        
        // Find the root of the sets containing u and v
        for (x = u, y = v; visited[x] != x || visited[y] != y; x = visited[x], y = visited[y]) {}

        if (x != y) {
            new.edgeList[new.edgeCount].head = x;
            new.edgeList[new.edgeCount].tail = y;
            new.edgeList[new.edgeCount].weight = minWeight;
            new.edgeCount++;
            new.minCost += minWeight;
            visited[trav->elem.head] = x;
        }
        
    }
    return new;
}



//MST kruskals(Graph G){
//    MST T; T.count = 0; T.minCost = 0;adjType edges[MAX], temp;int i, j,edgeCounter = 0, U[MAX];
//    ptr trav;
//    for(i = 0; i < MAX; i++){
//        for(trav = G.adjList[i];trav!=NULL;trav = trav->link){
//            if(trav->elem.head > i){
//                edges[edgeCounter].head = i;
//                edges[edgeCounter].tail = trav->elem.head;
//                edges[edgeCounter].weight = trav->elem.weight;
//                edgeCounter++;
//            }
//        }
//    }
//    for(i = 0; i < edgeCounter; i++){//Bubble Sort
//        for(j = 0; j < edgeCounter-i-1;j++){
//            if(edges[j].weight > edges[j+1].weight){
//                temp = edges[j];
//                edges[j] = edges[j+1];
//                edges[j+1] = temp;
//            }
//        }
//    }
//
//    for(i = 0;  i< MAX;i++){//Universal Set
//        U[i] = i;
//    }
//
//    for(i = 0; i < edgeCounter && T.count < MAX-1; i++){
//        adjType newEdge = edges[i];
//        int head = newEdge.head;
//        int tail = newEdge.tail;
//        int weight = newEdge.weight;
//        
//        while(U[head] != head){
//            head = U[head];
//        }
//        while(U[tail] != tail){
//            tail = U[tail];
//        }
//        if(head!=tail){
//            T.edgeList[T.count] = newEdge;
//            T.count++;
//            T.minCost +=weight;
//            U[tail] = head;
//        }
//    }
//    return T;
//}

void printMST(MST T) {
  printf("Starting Vertex is %d\n", T.edgeList[0].head);
  printf("%-5s", "Edge");
  printf("%-5s", "Weight");
  int i, j;
  for (i = 0; i < T.edgeCount; i++) {
    printf("\n(%d,%d)", T.edgeList[i].head, T.edgeList[i].tail);
    printf(" %3d", T.edgeList[i].weight);
  }
  printf("\nMinimum Cost: %d\n", T.minCost);
}
