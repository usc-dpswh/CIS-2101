#include <stdio.h> 
#include <string.h>   
#include <limits.h>
#include <unistd.h>  
#include <stdlib.h>
                 
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

int min(int oldCost, int newCost);
void populateGraph(graphType G);
set* Dijkstras(graphType C, int start);
Kruskal KrusAlgo(graphType graph);
set* DjikstraAlgo(graphType graph, int startingPoint);
void displayKrus(Kruskal tree);
void printGraph(graphType G);
void displayKrus(Kruskal H);
graphType* FloydMayweather(graphType main, graphType A);
void Warshall(graphType main, graphType A);

int main() 
{ 
 	printf("\n\n\nDjikstra Algo by:: "); 
    printf("\n------------"); 

    graphType G, H;

    populateGraph(G);
    populateGraph(H);
//    set* smallestCosts = DjikstraAlgo(G, 0);
	set* smallestCosts = Dijkstras(G, 1);
    printGraph(G);
	int x,y,z;
	for (x = 0 ; x < MAX ; x++){
		printf("%d -> ", (*smallestCosts)[x]);
	}
	
	Warshall(G, H);
	
	printf("\n");
	
 	graphType floydGraph;
 	graphType* floyd = FloydMayweather(G, floydGraph);
 	
    return 0; 
} 

/************************************************************
 * Function Definitions                                     *
 ************************************************************/
 int min(int oldCost, int newCost){
	return (oldCost < newCost) ? oldCost : newCost;
}

graphType* FloydMayweather(graphType main, graphType A){
	int x, y, z;
	
	for (x = 0 ; x < MAX ; x++){
		for (y = 0 ; y < MAX ; y++){
			A[x][y] = main[x][y];		
		}
	}
	
	for (x = 0 ; x < MAX ; x++){
		A[x][x] = 0;
	}
	
	for (x = 0 ; x < MAX ; x++){
		for (y = 0 ; y < MAX ; y++){
			for (z = 0 ; z < MAX ; z++){
				if (A[y][x] + A[x][z] < A[y][z]){
					A[y][z] = A[y][x] + A[x][z];
				}
			}		
		}
	}
	
	printf("\nDisplaying FLOYD'S ALGORITHM");
	printGraph(A);
}


void populateGraph(graphType G)
{
	graphType graph = {
        INF, 1, 5, 4, 6, 5,
        1, INF, 5, INF, INF, 6,
        5, 5, INF, 2, INF, INF,
        4, INF, 2, INF, 1, INF,
        6, INF, INF, 1, INF, 6,
        5, 6, INF, INF, 3, INF
    };

	memcpy(G, graph, sizeof(graph));
}

set* Dijkstras(graphType graph, int start) {
    set* costs = (set*)malloc(sizeof(int) * MAX);
    set visited = {0};
	int x,y,minNdx;
	
	
	if (costs != NULL){
		for (x = 0 ; x < MAX ; x++){
			(*costs)[x] = INF;
		}
		(*costs)[start] = 0;
		
		for (x = 0 ; x < MAX ; x++){
			minNdx = -1;
			for (y = 0 ; y < MAX ; y++){
				if (!visited[y] && (minNdx == -1 || (*costs)[y] < (*costs)[minNdx])){
					minNdx = y;
				}
			}
			visited[minNdx] = 1;
			for (y = 0 ; y < MAX ; y++){
				if (!visited[y] && graph[minNdx][y] != INF){
//					AA + BB
//					BA + AB
//					minNdx minNdx y 	 y
//					y	   minNdx minNdx y
					
					if((*costs)[minNdx] + graph[minNdx][y] < (*costs)[y]){
						(*costs)[y] = (*costs)[minNdx] + graph[minNdx][y];					}
				}
			}
		}
	}
	return costs;
}

//set* Dijkstras(graphType graph, int start) {
//    set* costs = (set*)malloc(sizeof(int) * MAX);
//    set visited = {0};
//    int x, y, minNdx;
//    
//    if (costs != NULL){
//    	for (x = 0 ; x < MAX ; x++){
//    		(*costs)[x] = INF;
//		}
//		
//		(*costs)[start] = 0;
//		
//		for (x = 0 ; x < MAX ; x++){
//			minNdx = -1;
//			for (y = 0 ; y < MAX ; y++){
//				if (!visited[y] && (minNdx == -1 || (*costs)[y] < (*costs)[minNdx])){
//					minNdx = y;
//				}
//			}
//			visited[minNdx] = 1;
//			
//			for (y = 0 ; y < MAX ; y++){
//				if (!visited[y] && graph[minNdx][y] != INF){
//					if ((*costs)[minNdx] + graph[minNdx][y] < (*costs)[y]){
//						(*costs)[y] = (*costs)[minNdx] + graph[minNdx][y];
//					}
//				}
//			}
//		}	
//	}
//	return costs;
//}

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

void Warshall(graphType main, graphType A){
	int x,y,z;
	
	for (x = 0 ; x < MAX ; x++){
		for (y = 0 ; y < MAX ; y++){
			A[x][y] = (main[x][y] != INF) ? 1 : 0;
		}
	}
	
	for (x = 0 ; x < MAX ; x++){
		for (y = 0 ; y < MAX ; y++){
			for (z = 0 ; z < MAX ; z++){
				if (A[y][z] == 0){
					A[y][z] = A[y][x] && A[x][z];
				}
			}		
		}
	}
	
	printf("\nDisplaying Warshall Graph\n");
	printf("%-4s%-4d%-4d%-4d%-4d%-4d%-4d\n", "",0,1,2,3,4,5);
	for (x = 0 ; x < MAX ; x++){
		printf("%-4d", x);
		for (y = 0 ; y < MAX ; y++){
			printf("%-4d", A[x][y]);
		}
		printf("\n");
	}
}


