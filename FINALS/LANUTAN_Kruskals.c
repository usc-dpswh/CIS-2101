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
    Kruskal new;
    new.edgeCount = 0;
    new.minCost = 0;
    set visited;
    int x,y,u,v,head,tail,minWeight;
    
    for (x = 0 ; x < MAX ; x++){
    	visited[x] = x;
	}
    
    while (new.edgeCount < MAX-1){
    	minWeight = INF;
    	u = -1;
    	v = -1;
    	
    	for (head = 0 ; head < MAX ; head++){
    		for (tail = 0 ; tail < MAX ; tail++){
    			if (graph[head][tail] < minWeight){
    				minWeight = graph[head][tail];
    				u = head;
    				v = tail;
				}
			}
		}
		
		for (x = u, y = v ; visited[x] != x || visited[y] != y ; x = visited[x], y = visited[y]){};
		
		if (x != y){
			new.edges[new.edgeCount].u = x;
			new.edges[new.edgeCount].v = y;
			new.edges[new.edgeCount].weight = minWeight;
			new.edgeCount++;
			new.minCost += minWeight;
			visited[y] = x;
		}
		graph[u][v] = INF;
		graph[v][u] = INF;
	}
	return new;
}


//Kruskal KrusAlgo(graphType graph){
//    Kruskal new;
//    set vertices;
//    int head, tail, minWeight;
//    int u, v;
//    
//    new.edgeCount = 0;
//    new.minCost = 0;
//    
//	int x, y;
////	Initialize the edge weights to INFINITY in your new.edges and set vertices to x
//	for (x = 0 ; x < MAX ; x++){
//		new.edges[x].weight = INF;
//		vertices[x] = x;
//	}
//
//	while (new.edgeCount < MAX-1){
//		minWeight = INF;
//		
//		for (head = 0 ; head < MAX ; head++){
//			for (tail = 0 ; tail < MAX ; tail++){
//				if (graph[head][tail] < minWeight){
//					minWeight = graph[head][tail];
//					u = head;
//					v = tail;
//				}
//			}
//		}
//		
////		Check if there is a cycle
//		for (x = u, y = v ; (vertices[x] != x) || (vertices[y] != y) ; x = vertices[x], y = vertices[y]){};
//		
//		if (x != y){
//			new.edges[new.edgeCount].u = x;
//			new.edges[new.edgeCount].v = y;
//			new.edges[new.edgeCount].weight = minWeight;
//			new.edgeCount++;
//			new.minCost += minWeight;
//			vertices[y] = x;
//		}
//		
//		graph[u][v] = INF;
//		graph[v][u] = INF;
//	}
//    return new;
//}

void displayKrus(Kruskal T){
    int x;
		
	printf("\n%5s%5s", "Edge", "Cost");
 
    //Write code here

    for(x = 0; x < MAX - 1; x++){
        printf("\n%d-%d%5d", T.edges[x].u, T.edges[x].v, T.edges[x].weight);
    }

    printf("\n\nMinCost: %d\n", T.minCost);
}
