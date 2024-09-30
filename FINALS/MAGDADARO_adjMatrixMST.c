#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define V 6
#define INF INT_MAX


typedef struct {
	int u, v, weight;
} Edge;

typedef int Graph[V][V];
typedef int set[V];

typedef struct MST {
	Edge edgelist[V];
	int edgeCount;
	int minCost;
} MST;

void initGraph(Graph *graph);
void addEdge(Graph *graph, int u, int v, int weight);
void populateGraph(Graph *G);
void printGraph(Graph G);
MST primsAlgoMST(Graph G, int startIndex);
void sortKruskalEdges(Edge edges[], int n);
int checkCycle(set U, int vertex);
MST kruskalsAlgoMST(Graph G);
void printMST(MST T);

int main() {
	Graph G;
	initGraph(&G);
	populateGraph(&G);
	printGraph(G);
	
	MST TP = primsAlgoMST(G, 2);
	printMST(TP);
	
	MST TK = kruskalsAlgoMST(G);
	printMST(TK);

}

void initGraph(Graph *graph) {
	int i, j;
	for(i = 0; i < V; i++) {
		for(j = 0; j < V; j++) {
			(*graph)[i][j] = INF;
		}
	}
}

void addEdge(Graph *graph, int u, int v, int weight) {
	if((*graph)[u][v] == INF) {
		(*graph)[u][v] = weight;
		(*graph)[v][u] = weight;
		printf("Vertices %d -- %d connected with a weight of %d\n\n", u, v, weight);
	} else {
		printf("Vertices %d -- %d already have a weight of %d! Cannot connect!\n", u, v, (*graph)[u][v]);
	}
}

void populateGraph(Graph *G) {
	addEdge(G, 0, 1, 5);
	addEdge(G, 1, 2, 3);
	addEdge(G, 3, 4, 10);
	addEdge(G, 0, 4, 12);
	addEdge(G, 2, 0, 11);
	addEdge(G, 5, 2, 4);
	addEdge(G, 1, 5, 2);
	addEdge(G, 3, 1, 4);
}

void printGraph(Graph G) {
	printf("Graph Display:\n");
	printf("=========================\n\n");
	int i, j;
	printf("  ");
	for(i = 0; i < V; i++) {
		printf("%5d ", i);
	}
	printf("\n\n");
	for(i = 0; i < V; i++) {
		printf("%d ", i);
		for(j = 0; j < V; j++) {
			G[i][j] != INF ? printf("%5d ", G[i][j]) : printf("%5s ", "0");
		}
		printf("\n\n");
	}
}

MST primsAlgoMST(Graph G, int startIndex) {
	MST retval;
	retval.edgeCount = 0;
	retval.minCost = 0;
	set U = {0};

	U[startIndex] = 1;

	printf("Prim's Algorithm running...\n");
	while(retval.edgeCount < V - 1) {
		int head, tail, weight = INF;
		int i, j;
		for(i = 0; i < V; i++) {
			if(U[i]) {
				for(j = 0; j < V; j++) {
					if(!U[j] && G[i][j] < weight) {
						head = i;
						tail = j;
						weight = G[i][j];
					}
				}
			}
		}
		if(weight != INF) {
			U[tail] = 1;
			retval.edgelist[retval.edgeCount].u = head;
			retval.edgelist[retval.edgeCount].v = tail;
			retval.edgelist[retval.edgeCount].weight = weight;
			retval.edgeCount++;
			retval.minCost += weight;
		} else {
			weight = INF;
		}
	}
	return retval;
}

void sortKruskalEdges(Edge edges[], int n){
	int i, j;
	for(i = 0; i < n - 1; i++){
		for(j = 0; j < n - i - 1; j++){
			if(edges[j].weight > edges[j+1].weight){
				Edge temp = edges[j];
				edges[j] = edges[j+1];
				edges[j+1] = temp;
			}
		}
	}
}

int checkCycle(set U, int vertex) {
    if (U[vertex] == vertex) {
        return vertex;
    }
    U[vertex] = checkCycle(U, U[vertex]);
    return U[vertex];
}


MST kruskalsAlgoMST(Graph G){
	MST retval;
	retval.edgeCount = 0;
	retval.minCost = 0;
	
	Edge sortedEdges[V*V];
	int edgeCounter = 0;
	int i, j;
	for(i = 0; i < V; i++){
		for(j = 0; j < V; j++){
			if(G[i][j] != INF){
				sortedEdges[edgeCounter].u = i;
				sortedEdges[edgeCounter].v = j;
				sortedEdges[edgeCounter].weight = G[i][j];
				edgeCounter++;
			}
		}
	}
	sortKruskalEdges(sortedEdges, edgeCounter);
	set U;
	for(i = 0; i < V; i++){
		U[i] = i;
	}
	
	printf("Kruskal's Algorithm running...\n");
	for(i = 0; i < edgeCounter && retval.edgeCount < V - 1; i++){
		Edge newEdge = sortedEdges[i];
		int head = newEdge.u;
		int tail = newEdge.v;
		int weight = newEdge.weight;
		
		int headRoot = checkCycle(U, head);
		int tailRoot = checkCycle(U, tail);
		if(headRoot != tailRoot){
			retval.edgelist[retval.edgeCount] = newEdge;
			retval.edgeCount++;
			retval.minCost += weight;
			U[tailRoot] = headRoot;
		}
		
	}
	return retval;	
}

void printMST(MST T) {
	printf("Starting Vertex is %d\n", T.edgelist[0].u);
	printf("%-5s", "Edge");
	printf("%-5s", "Weight");
	int i, j;
	for(i = 0; i < T.edgeCount; i++) {
		printf("\n(%d,%d)", T.edgelist[i].u, T.edgelist[i].v);
		printf(" %3d", T.edgelist[i].weight);
	}
	printf("\nMinimum Cost: %d\n", T.minCost);
}


