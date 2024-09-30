#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define GRAPH_SIZE 6

typedef struct node {
	int elem;
	struct node* next;
} *List;

typedef List Graph[GRAPH_SIZE];

void initGraph(Graph main);
void connectVertices(Graph main, int dest, int newVertex);

int main(void) {
    Graph kruskal;
    
    initGraph(kruskal);
    connectVertices(kruskal, 0, 1);
    connectVertices(kruskal, 1, 2);
    
    return 0;
}

void initGraph(Graph main) {
	int x;

	for (x = 0; x < GRAPH_SIZE; x++) {
		main[x] = NULL;
	}

	printf("\nInitialized graph.");
}

void connectVertices(Graph main, int dest, int newVertex) {
	if (newVertex >= GRAPH_SIZE) {
		printf("\nThat is not a valid vertex!");
		return;
	}
	
	List* trav;
	
	for (trav = &main[dest] ; *trav != NULL ; trav = &(*trav)->next) {};
	
	if (*trav == NULL) {
		List new = (List)malloc(sizeof(struct node));
		
		if (new != NULL) {
			new->elem = newVertex;
			new->next = NULL;
			*trav = new;
			printf("\nConnected Vertex [%d] to Vertex [%d] !", dest, newVertex);
		}
	}
	
	for (trav = &main[newVertex] ; *trav != NULL ; trav = &(*trav)->next) {};
	
	if (*trav == NULL) {
		List new = (List)malloc(sizeof(struct node));

		if (new != NULL) {
			new->elem = dest;
			new->next = NULL;
			*trav = new;
			printf("\nConnected Vertex [%d] to Vertex [%d] !", newVertex, dest);
		}
	}
}

