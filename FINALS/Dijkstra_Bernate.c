#include <limits.h>
#include <unistd.h>    // for sleep(), to add in code if display leaves blank screen  
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>  

                 
#define MAX  6              // Number of vertices in the graph  
#define INFINITY  0XFFFF    
   
/***** Data Structure Definition *****/  
typedef int graphType[MAX][MAX];    // A[x][y] = INFINITY  if there is not edge ;  A[x][y] = weight of the edge (x,y)
typedef int set[MAX];               // Bit-vector implementation of Set

typedef struct {
	int u, v;     // (u,v) represents the edge  
	int weight;   // weight of the edge
}edgetype;

typedef struct {
    edgetype edges[MAX];
    int edgeCount;   //actual number of edges
	int minCost;	 //Cost of the MST
}primMST;

/***** Function Prototypes *****/

void populateGraph(graphType G);
int *dijkstraAlgo(graphType graph, int startVertex);
void printGraph(graphType G);
void printDijkstra(int *D);
set* Dijkstras(graphType C, int start);

int main() 
{ 
     /*---------------------------------------------------------------------------------
    * 	Problem #2 ::  a) Allows user to input from keyboard the starting vertex      *
    *                  b) Calls populateGraph() to populate the given graph           *
    *                  c) Calls primAlgo() and displayPrimMST()                       *
    *                                                                                 *
    * printf("\n\n\nProblem #2:: ");                                                  *  
    * printf("\n------------");                                                       *
    *---------------------------------------------------------------------------------*/
 	printf("\n\n\nProblem #2:: "); 
    printf("\n------------"); 

    graphType G;

    populateGraph(G);

//    int *dijkstra = dijkstraAlgo(G, 2);
    int *dijkstra = Dijkstras(G, 0);
	printGraph(G);

    printDijkstra(dijkstra);
 	
    return 0; 
} 

/************************************************************
 * Function Definitions                                     *
 ************************************************************/
void populateGraph(graphType G)
{
	graphType graph = {  INFINITY, 1, 5, 4, 6, 5, 1, INFINITY, 5, INFINITY, INFINITY, 6, 5, 5, INFINITY, 2, INFINITY, INFINITY, 4,
                             INFINITY, 2, INFINITY, 1, INFINITY, 6, INFINITY,INFINITY, 1, INFINITY, 3, 5, 6, INFINITY, INFINITY, 3, INFINITY} ;   //5

	memcpy(G, graph, sizeof(graph));
}

void printGraph(graphType G){
	int i, j;

    printf("\n     ");
    for (i = 0; i < MAX; i++) {
        printf("%-6d", i);
    }
    printf("\n");

    printf("\n");
	for(i = 0; i < MAX; i++) {
        printf("%-4d ", i);
		for(j = 0; j < MAX; j++) {
			G[i][j] != INFINITY ? printf("%-6d", G[i][j]) : printf("%-6s", "[ ]");
		}
		printf("\n");
	}
}

void printDijkstra(int *D){
    int i;
	printf("%5s", "Dest");
	printf("%5s", "Cost");
	for(i = 0; i < MAX; i++) {
		printf("\n%5d", i);
		printf("%5d", D[i]);
	}
}

set* Dijkstras(graphType C, int start) {
    set *D = (set*)malloc(sizeof(int) * MAX);
    int S[MAX] = {0}; 
    int count;
    int i,j;

    if (D != NULL) {
        for (i = 0; i < MAX; i++) {
            (*D)[i] = INFINITY;
        }

        (*D)[start] = 0;

  
        for (i = 0; i < MAX; i++) {
            int minIndex = -1;
            for (j = 0; j < MAX; j++) {
                if (!S[j] && (minIndex == -1 || (*D)[j] < (*D)[minIndex])) {
                    minIndex = j;
                }
            }

            S[minIndex] = 1;

            for (j = 0; j < MAX; j++) {
                if (!S[j] && C[minIndex][j] != INFINITY) {
                    if ((*D)[minIndex] + C[minIndex][j] < (*D)[j]) {
                        (*D)[j] = (*D)[minIndex] + C[minIndex][j];
                    }
                }
            }
        }
    }

    return D;
}

int *dijkstraAlgo(graphType G, int vertex){
    int *D = (int*)malloc(sizeof(int) * MAX); 

    if(D != NULL){
        set S = {0}; //Track visited and unvisited vertices
        int min = INFINITY, minNdx = 0; //Stores the index with minimum weight
        int i, x, j; //Traversal

        for(i = 0; i < MAX; i++){
            D[i] = INFINITY;
        }

        D[vertex] = 0;

        for(i = 0; i < MAX; i++){
            min = INFINITY;

            for(x = 0; x < MAX; x++){
                if(!S[x] && D[x] < min){
                    min = D[x];
                    minNdx = x;
                }
            }

            S[minNdx] = 1;

            for(j = 0; j < MAX; j++){
                if(!S[j] && G[minNdx][j] != INFINITY && D[minNdx] + G[minNdx][j] < D[j]){
                    D[j] = D[minNdx] + G[minNdx][j];
                }
            }
        }
    }
    return D;
}


