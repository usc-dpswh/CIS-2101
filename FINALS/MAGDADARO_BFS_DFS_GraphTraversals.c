#include <stdio.h>
#include <stdlib.h>
#define V 7

typedef int set[V];

typedef struct edge {
	int dest;
	int weight;
} edgeType;

typedef struct node {
	edgeType edge;
	struct node *next;
}*LL, nodeType;

typedef struct graph {
	int edgeCount;
	LL adjList[V];
} Graph;

void LANUTAN_dfs(Graph main, int startingPoint, set visited){
	visited[startingPoint] = 1;
	LL trav;
	printf("%d -> ", startingPoint);
	for (trav = main.adjList[startingPoint] ; trav != NULL ; trav = trav->next){
		if (!visited[trav->edge.dest]){
			LANUTAN_dfs(main, trav->edge.dest, visited);
		}
	}
}

void initGraph(Graph *G);
void addEdge(Graph *G, int src, int dest, int weight);
void populateGraph(Graph *G);
void printAdjList(Graph G);
void depthFirstSearch(Graph G, int vertex, set visited);
void breadthFirstSearch(Graph G, int vertex, set visited);

int main() {
	Graph myGraph;
	initGraph(&myGraph);
	populateGraph(&myGraph);
	printAdjList(myGraph);
	
	set DFSvisited = {0};
	set Lanutan = {0};
//	depthFirstSearch(myGraph, 4, DFSvisited); 
//	depthFirstSearch(myGraph, 4, visited);
	LANUTAN_dfs(myGraph, 4, Lanutan);
	
	set BFSvisited = {0};
	breadthFirstSearch(myGraph, 4, BFSvisited);
	//breadthFirstSearch(myGraph, 4, BFSvisited);
	
	//According to sir if not all are visited call DFS/BFS again but which vertex to use depends on the problem (ex. biggest unvisited or smallest unvisited)
	//This shouldn't be a problem if undirected ang graph though (My Graph is directed)
	
}

void initGraph(Graph *G) {
	int i;
	for(i = 0; i < V; i++) {
		G->adjList[i] = NULL;
	}
	G->edgeCount = 0;
}

void addEdge(Graph *G, int src, int dest, int weight) {
	LL *trav, temp;
	for(trav = &G->adjList[src]; *trav != NULL; trav = &(*trav)->next) {}
	temp = (LL)malloc(sizeof(nodeType));
	if(temp != NULL) {
		temp->edge.dest = dest;
		temp->edge.weight = weight;
		temp->next = *trav;
		*trav = temp;
	}
}

void populateGraph(Graph *G) {
	edgeType edgeList[] = {
		{1, 10},
		{2, 3},
		{2, 6},
		{3,14},
		{0, 2},
		{0, 14},
		{2, 50},
		{5, 28},
		{6, 22},
		{1, 7},
		{3, 78},
		{5, 11}
	};

	int sourceList[] = {0, 0, 1, 1, 2, 3, 3, 4, 4, 5, 6, 6};
	int size = sizeof(sourceList)/sizeof(sourceList[0]);
	int i;
	for(i = 0; i < size; i++) {
		addEdge(G, sourceList[i], edgeList[i].dest, edgeList[i].weight);
	}
}

void printAdjList(Graph G) {
	printf("Source -> Dest[Weight]:\n\n");
	LL trav;
	int i;
	for(i = 0; i < V; i++) {
		printf("%d", i);
		for(trav = G.adjList[i]; trav != NULL; trav = trav->next) {
			printf(" -> %d", trav->edge.dest);
		}
		printf("\n\n");
	}
}

void depthFirstSearch(Graph G, int vertex, set visited) {
	visited[vertex] = 1;
	printf("DFS - On Vertex: %d\n", vertex);

	LL current = G.adjList[vertex];
	while(current != NULL) {
		int connection = current->edge.dest;
		if(!visited[connection]) {
			depthFirstSearch(G, connection, visited);
		}
		current = current->next;
	}
}

void breadthFirstSearch(Graph G, int vertex, set visited){
	int queue[V];
	int front = 0, rear = -1;
	
	rear++;
	queue[rear] = vertex;
	visited[vertex] = 1;
	
	while(front <= rear){
		int currentVertex = queue[front];
		front++;
		printf("\nBFS - Visited Vertex: %d\n", currentVertex);
		
		LL current = G.adjList[currentVertex];
		while(current != NULL){
			int connection = current->edge.dest;
			if(!visited[connection]){
				rear++;
				queue[rear] = connection;
				visited[connection] = 1;
			}
			current = current->next;
		}
	}
}

