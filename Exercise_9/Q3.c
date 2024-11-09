#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX
typedef struct {
    int dest;
    int weight;
    struct Edge* next;
} Edge;

typedef struct {
    Edge* adjList[MAX_VERTICES];
    int numVertices;
} Graph;

typedef struct {
    int vertex;
    int distance;
} MinHeapNode;

typedef struct {
    int size;
    int capacity;
    MinHeapNode* heapArray;
    int* pos;
} MinHeap;
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest, int weight);
void dijkstra(Graph* graph, int startVertex, int* dist, int* prev);
MinHeap* createMinHeap(int capacity);
void minHeapify(MinHeap* minHeap, int idx);
int extractMin(MinHeap* minHeap);
void decreaseKey(MinHeap* minHeap, int vertex, int dist);
int isInMinHeap(MinHeap* minHeap, int vertex);
void printShortestPath(int* prev, int start, int end);
void addNewLocation(Graph* graph);
void addNewRoute(Graph* graph);

int main() {
    Graph* graph = createGraph(MAX_VERTICES);
    int dist[MAX_VERTICES], prev[MAX_VERTICES];
    int choice, src, dest, weight;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add new location (warehouse/client)\n");
        printf("2. Add new route between locations\n");
        printf("3. Calculate shortest route (Dijkstra)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNewLocation(graph);
                break;
            case 2:
                printf("Enter source location index: ");
                scanf("%d", &src);
                printf("Enter destination location index: ");
                scanf("%d", &dest);
                printf("Enter route weight (distance/time): ");
                scanf("%d", &weight);
                addEdge(graph, src, dest, weight);
                break;
            case 3:
                printf("Enter the starting location index: ");
                scanf("%d", &src);
                dijkstra(graph, src, dist, prev);
                printf("Enter the destination location index: ");
                scanf("%d", &dest);
                printf("Shortest path from %d to %d is: ", src, dest);
                printShortestPath(prev, src, dest);
                break;
            case 4:
                free(graph);
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = 0;
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = graph->adjList[src];
    graph->adjList[src] = newEdge;

    // For undirected graph, add an edge in both directions
    newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = src;
    newEdge->weight = weight;
    newEdge->next = graph->adjList[dest];
    graph->adjList[dest] = newEdge;
}

void dijkstra(Graph* graph, int startVertex, int* dist, int* prev) {
    MinHeap* minHeap = createMinHeap(graph->numVertices);
    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = INF;
        prev[i] = -1;
        minHeap->heapArray[i].vertex = i;
        minHeap->heapArray[i].distance = dist[i];
        minHeap->pos[i] = i;
    }

    dist[startVertex] = 0;
    minHeap->heapArray[startVertex].distance = 0;
    decreaseKey(minHeap, startVertex, 0);

    while (minHeap->size) {
        int u = extractMin(minHeap);

        Edge* edge = graph->adjList[u];
        while (edge != NULL) {
            int v = edge->dest;

            if (isInMinHeap(minHeap, v) && dist[u] != INF && dist[u] + edge->weight < dist[v]) {
                dist[v] = dist[u] + edge->weight;
                prev[v] = u;
                decreaseKey(minHeap, v, dist[v]);
            }
            edge = edge->next;
        }
    }

    free(minHeap->heapArray);
    free(minHeap->pos);
    free(minHeap);
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->heapArray = (MinHeapNode*)malloc(capacity * sizeof(MinHeapNode));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    return minHeap;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->heapArray[left].distance < minHeap->heapArray[smallest].distance)
        smallest = left;
    if (right < minHeap->size && minHeap->heapArray[right].distance < minHeap->heapArray[smallest].distance)
        smallest = right;
    if (smallest != idx) {
        MinHeapNode temp = minHeap->heapArray[smallest];
        minHeap->heapArray[smallest] = minHeap->heapArray[idx];
        minHeap->heapArray[idx] = temp;

        minHeap->pos[minHeap->heapArray[smallest].vertex] = smallest;
        minHeap->pos[minHeap->heapArray[idx].vertex] = idx;

        minHeapify(minHeap, smallest);
    }
}

int extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0)
        return -1;

    MinHeapNode root = minHeap->heapArray[0];

    MinHeapNode lastNode = minHeap->heapArray[minHeap->size - 1];
    minHeap->heapArray[0] = lastNode;

    minHeap->pos[root.vertex] = minHeap->size - 1;
    minHeap->pos[lastNode.vertex] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root.vertex;
}

void decreaseKey(MinHeap* minHeap, int vertex, int dist) {
    int i = minHeap->pos[vertex];
    minHeap->heapArray[i].distance = dist;

    while (i && minHeap->heapArray[i].distance < minHeap->heapArray[(i - 1) / 2].distance) {
        minHeap->pos[minHeap->heapArray[i].vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->heapArray[(i - 1) / 2].vertex] = i;

        MinHeapNode temp = minHeap->heapArray[i];
        minHeap->heapArray[i] = minHeap->heapArray[(i - 1) / 2];
        minHeap->heapArray[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap* minHeap, int vertex) {
    if (minHeap->pos[vertex] < minHeap->size)
        return 1;
    return 0;
}

void printShortestPath(int* prev, int start, int end) {
    if (start == end) {
        printf("%d ", start);
        return;
    }
    if (prev[end] == -1) {
        printf("No path exists from %d to %d\n", start, end);
        return;
    }

    printShortestPath(prev, start, prev[end]);
    printf("%d ", end);
}

void addNewLocation(Graph* graph) {
    if (graph->numVertices < MAX_VERTICES) {
        printf("New location added. Total locations: %d\n", graph->numVertices + 1);
        graph->numVertices++;
    } else {
        printf("Maximum number of locations reached.\n");
    }
}

void addNewRoute(Graph* graph) {
    int src, dest, weight;
    printf("Enter source location index: ");
    scanf("%d", &src);
    printf("Enter destination location index: ");
    scanf("%d", &dest);
    printf("Enter route weight (distance/time): ");
    scanf("%d", &weight);
    addEdge(graph, src, dest, weight);
}
