/************************************************************************
 * Prim's Algorithm : It grows a spanning tree, one edge at a time.     *
 * Given:                                                               *
 *   1)  Graph G = (V, E)                                               *
 *   2)  V = {0, 1, 2, 3, 4}                                            *
 *                                                                      *
 * Steps of Prim’s Algorithm:                                           *
 *   1) Initialize set U to contain { 0 }                               *
 *      //In the program, starting vertex will be inputted by the user  *
 *   2) While (U != V)                                                  *
 *       a) Find the minimum cost edge (u, v) such that                 *
 *          u is an element  U and   v is not yet in U                  *
 *       b)  Add v to U                                                 *
 ************************************************************************/
 
#include <unistd.h>    // for sleep(), to add in code if display leaves blank screen  
#include <stdio.h> 
#include <string.h>   
#include <limits.h>

                 
#define MAX  6              // Number of vertices in the graph  
#define INFINITY  0XFFFF 
#define INF INT_MAX   
   
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

 void printGraph(graphType G);
void populateGraph(graphType G);
primMST primAlgo(graphType graph, int startVertex);
void displayPrimMST(primMST tree);

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
    primMST new = primAlgo(G, 3);

    displayPrimMST(new);

    printGraph(G);
 	
    return 0; 
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

 void printGraph(graphType G) {
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

primMST primAlgo(graphType graph, int start)
{
	primMST new;
	new.edgeCount = 0;
	new.minCost = 0;
	set visited = {0};
	visited[start] = 1;
	int x,u,v,head,tail,minWeight;
	
	for (x = 0 ; x < MAX ; x++){
		minWeight = INFINITY;
		u = -1;
		v = -1;
		
		for (head = 0 ; head < MAX ; head++){
			if (visited[head]){
				for (tail = 0 ; tail < MAX ; tail++){
					if (!visited[tail] && graph[head][tail] < minWeight){
						minWeight = graph[head][tail];
						u = head;
						v = tail;
					}
				}
			}
		}
		
		if (minWeight != INFINITY){
			new.edges[new.edgeCount].u = u;
			new.edges[new.edgeCount].v = v;
			new.edges[new.edgeCount].weight = minWeight;
			new.edgeCount++;
			new.minCost += minWeight;
			visited[v] = 1;
		}
	}
	return new;
}

void displayPrimMST(primMST T)
{
	int x;
		
	printf("\n%5s%5s", "Edge", "Cost");
 
    //Write code here

    for(x = 0; x < MAX - 1; x++){
        printf("\n%d-%d%5d", T.edges[x].u, T.edges[x].v, T.edges[x].weight);
    }

    printf("\n\nMinCost: %d\n", T.minCost);
}





