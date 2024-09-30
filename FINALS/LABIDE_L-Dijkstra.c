#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define VISITED -1
#define UNVISITED -2
#define SENTINEL INT_MAX

typedef struct node {
    int vertex;
    int weight;
    struct node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

typedef struct {
    LinkedList* array;
    int vertexCount;
} Graph;

typedef struct {
    int* distances;
    int count;
} dijkstraResult;

Graph createGraph(int V);
void addEdge(Graph* graph, int src, int dest, int weight);
void displayGraph(Graph graph);
dijkstraResult dijkstraAlgo(Graph graph, int start);

int main() {
    Graph graph = createGraph(MAX);

    addEdge(&graph, 4, 5, 1);
    addEdge(&graph, 4, 6, 10);
    addEdge(&graph, 5, 1, 4);
    addEdge(&graph, 5, 6, 9);
    addEdge(&graph, 6, 3, 1);
    addEdge(&graph, 3, 2, 5);
    addEdge(&graph, 1, 3, 10);
    addEdge(&graph, 1, 2, 8);
    addEdge(&graph, 1, 0, 19);
    addEdge(&graph, 3, 0, 17);
    addEdge(&graph, 0, 2, 3);

    displayGraph(graph);

    dijkstraResult result = dijkstraAlgo(graph, 4);

    printf("\nShortest distances from vertex 4:\n");
    for (int i = 0; i < MAX; i++) {
        if(result.distances[i] ==  SENTINEL){
            printf("Vertex %d: NO PATH\n", i);
        }else{
            printf("Vertex %d: %d\n", i, result.distances[i]);
        }
    }
   

    return 0;
}

Graph createGraph(int V) {
    Graph graph;
    graph.vertexCount = V;
    graph.array = (LinkedList*)malloc(V * sizeof(LinkedList));
    for (int i = 0; i < V; ++i) {
        graph.array[i].head = NULL;
    }
    return graph;
}

Node* createNode(int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void displayGraph(Graph graph) {
    printf("\n\nThe Adjacency List ::\n");
    for (int i = 0; i < graph.vertexCount; ++i) {
        Node* trav = graph.array[i].head;
        printf("Vertex %d: ", i);
        while (trav) {
            printf("(%d, %d) ", trav->vertex, trav->weight);
            trav = trav->next;
        }
        printf("\n");
    }
}

dijkstraResult dijkstraAlgo(Graph graph, int start) {
    dijkstraResult result;
    result.count = graph.vertexCount;
    result.distances = (int*)malloc(graph.vertexCount * sizeof(int));

    for (int i = 0; i < graph.vertexCount; ++i) { //SET RET ARR ALL TO INF
        result.distances[i] = SENTINEL;
    }
    result.distances[start] = 0;

    int visited[MAX];
    for (int i = 0; i < graph.vertexCount; ++i) { //SET VISITED TO 0
        visited[i] = 0;
    }

    for (int i = 0; i < graph.vertexCount - 1; ++i) {
        int minIndex = -1;
        for (int j = 0; j < graph.vertexCount; ++j) {
            if (!visited[j] && (minIndex == -1 || result.distances[j] < result.distances[minIndex])) {
                minIndex = j;
            }
        }
        visited[minIndex] = 1;

   
        Node* trav = graph.array[minIndex].head;
        while (trav) {
            int dest = trav->vertex;
            int weight = trav->weight;
            if (!visited[dest] && result.distances[minIndex] != SENTINEL
             && result.distances[minIndex] + weight < result.distances[dest]) {
                result.distances[dest] = result.distances[minIndex] + weight;
            }
            trav = trav->next;
        }
    }
    return result;
}
