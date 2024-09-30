#include <stdio.h>
#include <stdlib.h>
#define MAX 7

typedef int set[MAX];
typedef int matrix[MAX][MAX];

typedef struct {
	int front;
	int rear;
	int elems[MAX];
} Queue;

typedef struct node {
	int vertex;
	struct node* next;
} *List;

typedef List adjList[MAX];

typedef struct {
	adjList headers;
} Graph;

//	Queue Functions
void enqueue(Queue* main, int newData){
	if (main->front == -1 && main->rear == -1){
		main->front++;
		main->rear = main->front;
		main->elems[main->front] = newData;
	} else if (main->rear < MAX){
		main->rear++;
		main->elems[main->rear] = newData;
	} else {
		printf("\nQueue overflow.");
	}
}
void dequeue(Queue* main){
	if (main->front == -1 && main->rear == -1){
		printf("\nNo elements to dequeue.");
	} else if (main->front == main->rear){
		main->front = -1;
		main->rear 	= -1;
	} else {
		main->front++;
	}
}
int front(Queue main){
	return (main.front != -1 && main.rear != -1) ? main.elems[main.front] : -1;
}

void printGraph(Graph main){
	List trav;
	int x, y;
	for (x = 0 ; x < MAX ; x++){
		printf("[%d]", x);
		for (trav = main.headers[x] ; trav != NULL ; trav = trav->next){
			printf("%5d", trav->vertex);
		}
		printf("\n");
	}
}
void initGraph(Graph* main){
	int x;
	for (x = 0 ; x < MAX ; x++){
		main->headers[x] = NULL;
	}
	printf("\nInitialized graph.");
}
void generateData(Graph* main){
	matrix graph = {
        {0, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0}
    };
	
	int x, y;
	List* trav;
	
	for (x = 0 ; x < MAX ; x++){
		for (y = 0 ; y < MAX ; y++){
			if (graph[x][y]){
				for (trav = &main->headers[x] ; *trav != NULL ; trav = &(*trav)->next){};
				List newNode = (List)malloc(sizeof(struct node));
				if (newNode != NULL){
					newNode->vertex = y;
					newNode->next = NULL;
					*trav = newNode;
//					printf("\nSuccessfully inserted pair (%d, %d) at index %d", x, y, x);
				}
			}
		}
	}
	printf("\nSuccessfully generated matrix.\n");
}
void DFS (Graph main, int start, set visited){
	visited[start] = 1;
	List trav;
	printf("%d -> ", start);
	for (trav = main.headers[start] ; trav != NULL ; trav = trav->next){
		if (!visited[trav->vertex]){
			DFS(main, trav->vertex, visited);
		}
	}
}
void BFS (Graph main, int start, set visited) {
    Queue A = {-1, -1};
    visited[start] = 1;
    List trav;
    enqueue(&A, start);
    int x;
    
    while (A.front != -1 && A.rear != -1){
    	x = A.elems[A.front];
    	printf("%d -> ", x);
    	dequeue(&A);
    	
    	for (trav = main.headers[x] ; trav != NULL ; trav = trav->next){
    		if (!visited[trav->vertex]){
    			visited[trav->vertex] = 1;
    			enqueue(&A, trav->vertex);
			}
		}
	}
}


int main(){
	Graph A;
	set visitedDFS = {0};
	set visitedBFS = {0};
	initGraph(&A);
	generateData(&A);
	printGraph(A);
	
//	DFS(A, 0, visitedDFS);
//	printf("\nDFS traversal finished starting at 0!\n");
	DFS(A, 4, visitedDFS);
	printf("\nDFS traversal finished starting at 4!\n");
	BFS(A, 4, visitedBFS);
	printf("\nBFS traversal finished starting at 4!\n");
	return 0;
}
