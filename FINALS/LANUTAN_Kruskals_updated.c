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

typedef struct {
    edgetype edges[MAX];
    int edgeCount;   //actual number of edges
	int minCost;	 //Cost of the MST
}Djikstra;

/***** Function Prototypes *****/

int min(int costA, int costB, int costC){
	return (costA < (costB + costC)) ? costA : (costB + costC);
}
void populateGraph(graphType G);
Kruskal KrusAlgo(graphType graph);
Djikstra DjikstraAlgo(graphType graph);
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
    Djikstra new = DjikstraAlgo(H);

    printGraph(G);
 	
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

Djikstra DjikstraAlgo(graphType graph, int startingPoint){
		
}

Djikstra DjikstraAlgo(graphType graph, int startingPoint){
	Djikstra new;
	int head, path; 
	int minWeight = INF;
	int x, y, z;
	int row, column;
	set smallestCosts = {INF};
	set universal = {0,1,2,3,4};
	set D;
	
//	Initialize and declare a Set to your startingPoint
	set visited = {startingPoint};
	
//	Initialize D to the given costs of your chosen vertex v
	for (x = 1 ; x < MAX ; x++){
		D[x] = graph[startingPoint][x];
	}
	
//	Start the loop
	for (x = 1 ; x < MAX ; x++){
//		Choose a vertex HEAD from the difference of universal and visited that's least
//		Loop to find vertex HEAD where D[HEAD] is a minimum
		for (head = 0 ; head < MAX ; head++){	// get from universal set
			for (column = 0 ; column < MAX && universal[head] != visited[column] ; column++){};
			if (column == MAX && D[head] < minWeight){
				minWeight = D[head];		// assign minWeight
			}
		}
		for (y = 0 ; y < MAX && D[y] != minWeight ; y++){};
		if (y < MAX){
			visited[x] = y; 
		}
		for ()
	}
	
	
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
    Kruskal new;
    set vertices;
    int head, tail, minWeight;
    int u, v;
    
    new.edgeCount = 0;
    new.minCost = 0;
    
	int x, y;
//	Initialize the edge weights to INFINITY in your new.edges and set vertices to x
	for (x = 0 ; x < MAX ; x++){
		new.edges[x].weight = INF;
		vertices[x] = x;
	}

	while (new.edgeCount < MAX-1){
		minWeight = INF;
		
		for (head = 0 ; head < MAX ; head++){
			for (tail = 0 ; tail < MAX ; tail++){
				if (graph[head][tail] < minWeight){
					minWeight = graph[head][tail];
					u = head;
					v = tail;
				}
			}
		}
		
//		Check if there is a cycle
		for (x = u, y = v ; (vertices[x] != x) || (vertices[y] != y) ; x = vertices[x], y = vertices[y]){};
		
		if (x != y){
			new.edges[new.edgeCount].u = x;
			new.edges[new.edgeCount].v = y;
			new.edges[new.edgeCount].weight = minWeight;
			new.edgeCount++;
			new.minCost += minWeight;
			vertices[y] = x;
		}
		
		graph[u][v] = INF;
		graph[v][u] = INF;
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
