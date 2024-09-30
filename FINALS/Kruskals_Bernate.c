#include <stdio.h> 
#include <string.h>   
#include <limits.h>
#include <unistd.h>  
                 
#define MAX  6              // Number of vertices in the graph  
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
}Kruskal;

/***** Function Prototypes *****/

void populateGraph(graphType G);
Kruskal KrusAlgo(graphType graph);
void displayKrus(Kruskal tree);
void printGraph(graphType G);
void displayKrus(Kruskal H);
int main() 
{ 
 	printf("\n\n\nKruskal's Algo by Karylle:: "); 
    printf("\n------------"); 

    graphType G, H;

    populateGraph(G);
    populateGraph(H);
    Kruskal new = KrusAlgo(H);

    printGraph(G);
    displayKrus(new);
 	
    return 0; 
} 

/************************************************************
 * Function Definitions                                     *
 ************************************************************/
void populateGraph(graphType G)
{
	graphType graph = {  INF, 1, 5, 4, 6, 5, 1, INF, 5, INF, INF, 6, 5, 5, INF, 2, INF, INF, 4,
                             INF, 2, INF, 1, INF, 6, INF,INF, 1, INF, 3, 5, 6, INF, INF, 3, INF} ;   //5

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
			G[i][j] != INF ? printf("%-6d", G[i][j]) : printf("%-6s", "[ ]");
		}
		printf("\n");
	}
}

Kruskal KrusAlgo(graphType graph){
    set vertices;
    int v = 0, x = 0, minWeight; //Stores edges and the minimumWeight
    int i , j, a = 0, b = 0; //For Iteration
    Kruskal new; //Returned MST

    new.edgeCount = 0;
    new.minCost = 0;

    for(i = 0; i < MAX; i++){
        new.edges[i].weight = INF;
    }

    for(i = 0; i < MAX; i++){ 
        vertices[i] = i;
    }

    while(new.edgeCount < MAX - 1){
        minWeight = INF;

        for(i = 0; i < MAX; i++){
            for(j = 0; j < MAX; j++){
                if(graph[i][j] < minWeight){
                    minWeight = graph[i][j];
                    v = i;
                    x = j;
                }
            }
        }

        for(a = v, b = x; (vertices[a] != a) || (vertices[b] != b); a = vertices[a], b = vertices[b]){} //Checks for a cycle

        if(a != b){
            new.edges[new.edgeCount].u = v;
            new.edges[new.edgeCount].v = x;
            new.edges[new.edgeCount].weight = minWeight;
            new.edgeCount++;
            new.minCost += minWeight;
            vertices[b] = a;
        }

        graph[v][x] = INF;
        graph[x][v] = INF;
    }

    return new;
}

void displayKrus(Kruskal T){
    int x;
		
	printf("\n%5s%5s", "Edge", "Cost");
 
    //Write code here

    for(x = 0; x < MAX - 1; x++){
        printf("\n%d-%d%5d", T.edges[x].u, T.edges[x].v, T.edges[x].weight);
    }

    printf("\n\nMinCost: %d\n", T.minCost);
}
