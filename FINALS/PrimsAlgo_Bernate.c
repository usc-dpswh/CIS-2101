/************************************************************************
 * Prim's Algorithm : It grows a spanning tree, one edge at a time.     *
 * Given:                                                               *
 *   1)  Graph G = (V, E)                                               *
 *   2)  V = {0, 1, 2, 3, 4}                                            *
 *                                                                      *
 * Steps of Prim�s Algorithm:                                           *
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
primMST primAlgo(graphType graph, int startVertex);
void displayPrimMST(primMST tree);
void printGraph(graphType G);

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
 

primMST primAlgo(graphType graph, int startVertex)
{
	//Write code here
    primMST new;
    new.edgeCount = 0;
    new.minCost = 0;
    set visited; //Tracks vertices included in primMST, VU tracks vertices of V-U
    int i, x, y;

    int edgeCount = 0; //Tracks the number of edges
    int minWeight = 0; //Tracks the minimum cost of the new MST

    for(i = 0; i < MAX; i++){
        visited[i] = 0;
    }
    visited[startVertex] = 1;

    for(y = 0; y < MAX; y++){
        minWeight = INFINITY;
        int u = 0;
        int v = 0;

        for(i = 0; i < MAX; i++){
            if(visited[i]){ //Looks for 1 in the Bit Vector Set
                for(x = 0; x < MAX; x++){
                    if(!visited[x] && graph[i][x] < minWeight){ //Finds the minWeight
                        minWeight = graph[i][x];
                        u = i;
                        v = x;
                    }
                }
            }
        }

        if(minWeight != INFINITY){ 
            new.edges[y].u = u; //Assigns the edges
            new.edges[y].v = v;
            new.edges[y].weight = minWeight;
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






