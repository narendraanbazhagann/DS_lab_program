#include <stdio.h>
#include <stdlib.h>
#define MAX_EDGES 1000
#define MAX_VERTICES 100
typedef struct {
    int src, dest, weight;
} Edge;
typedef struct {
    int *parent, *rank;
    int numVertices;
} DisjointSet;
DisjointSet* createDisjointSet(int vertices) {
    DisjointSet* ds = (DisjointSet*)malloc(sizeof(DisjointSet));
    ds->parent = (int*)malloc(vertices * sizeof(int));
    ds->rank = (int*)malloc(vertices * sizeof(int));
    ds->numVertices = vertices;
    
    for (int i = 0; i < vertices; i++) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }
    
    return ds;
}
int find(DisjointSet* ds, int i) {
    if (ds->parent[i] != i) {
        ds->parent[i] = find(ds, ds->parent[i]);  // Path compression
    }
    return ds->parent[i];
}
void unionSets(DisjointSet* ds, int x, int y) {
    int rootX = find(ds, x);
    int rootY = find(ds, y);

    if (rootX != rootY) {
        // Union by rank
        if (ds->rank[rootX] < ds->rank[rootY]) {
            ds->parent[rootX] = rootY;
        } else if (ds->rank[rootX] > ds->rank[rootY]) {
            ds->parent[rootY] = rootX;
        } else {
            ds->parent[rootY] = rootX;
            ds->rank[rootX]++;
        }
    }
}
int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}
void kruskal(Edge* edges, int numEdges, int numVertices) {
    DisjointSet* ds = createDisjointSet(numVertices);
    qsort(edges, numEdges, sizeof(Edge), compareEdges);

    int mstWeight = 0;
    printf("Cables to be installed (Minimum Spanning Tree):\n");
    for (int i = 0; i < numEdges; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (find(ds, u) != find(ds, v)) {
            printf("Cable between office %d and office %d with length %d\n", u, v, weight);
            mstWeight += weight;
            unionSets(ds, u, v);
        }
    }

    printf("Total cable length for Minimum Spanning Tree: %d\n", mstWeight);

   
    free(ds->parent);
    free(ds->rank);
    free(ds);
}
void addEdge(Edge* edges, int* numEdges, int src, int dest, int weight) {
    edges[*numEdges].src = src;
    edges[*numEdges].dest = dest;
    edges[*numEdges].weight = weight;
    (*numEdges)++;
}

int main() {
    int numVertices, numEdges, choice;
    Edge edges[MAX_EDGES];
    int numEdgesAdded = 0;

    printf("Enter the number of offices (vertices): ");
    scanf("%d", &numVertices);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add a new cable between offices\n");
        printf("2. Calculate Minimum Spanning Tree (MST) for cables\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int src, dest, weight;
                printf("Enter source office index: ");
                scanf("%d", &src);
                printf("Enter destination office index: ");
                scanf("%d", &dest);
                printf("Enter cable length (weight): ");
                scanf("%d", &weight);

                addEdge(edges, &numEdgesAdded, src, dest, weight);
                break;
            }
            case 2:
                kruskal(edges, numEdgesAdded, numVertices);
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
