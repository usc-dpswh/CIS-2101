#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INF INT_MAX
#define V 7

typedef struct {
  int arr[V];
  int count;
} Dijkstra;

typedef int Graph[V][V];
int *Dijkstras(Graph C, int start);
int main() {

  int graph[V][V] = {
      {INF, 19, 3, 17, INF, INF, INF},  {19, INF, 8, 10, INF, 4, INF},
      {3, 8, INF, 5, INF, INF, INF},    {17, 10, 5, INF, INF, INF, 1},
      {INF, INF, INF, INF, INF, 1, 10}, {INF, 4, INF, INF, 1, INF, 9},
      {INF, INF, INF, 1, 10, 9, INF}};
  int startVertex = 0;
  int *distances = Dijkstras(graph, startVertex);

  printf("Shortest distances from vertex %d:\n", startVertex);
  for (int i = 0; i < V; i++) {
    printf("Vertex %d: %d\n", i, distances[i]);
  }

  return 0;
}
int *Dijkstras(Graph C, int start) {
  int *D = (int *)malloc(sizeof(int) * V);
  int S[V] = {0}, i ,minNdx, j;
  int count;
  
  if(D!=NULL){
    for(i = 0; i < V; i++){
        D[i] = INF;
    }
    D[start] = 0;
    for(i = 0;i <V; i++){
        minNdx = -1;
        for(j = 0; j < V;j++){
            if(!S[j] && (minNdx == -1 || D[j] < D[minNdx])){
                minNdx = j;
            }
        }

        S[minNdx] = 1;

        for(j = 0; j < V;j++){
            if(!S[j] && C[minNdx][j] != INF){
                if(D[minNdx] + C[minNdx][j] < D[j]){
                    D[j] = D[minNdx] + C[minNdx][j];
                }
            }
        }
    }
  }

  return D;
}
