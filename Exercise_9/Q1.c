#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LOCATIONS 100
int graph[MAX_LOCATIONS][MAX_LOCATIONS];
int numLocations;
void initGraph(int locations) {
    numLocations = locations;
    for (int i = 0; i < numLocations; i++) {
        for (int j = 0; j < numLocations; j++) {
            if (i == j) {
                graph[i][j] = 0;  
            } else {
                graph[i][j] = INT_MAX;  
            }
        }
    }
}
void addRoute(int from, int to, int distance) {
    graph[from][to] = distance;
    graph[to][from] = distance; 
}
void dijkstra(int start) {
    int dist[MAX_LOCATIONS], visited[MAX_LOCATIONS];
    for (int i = 0; i < numLocations; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[start] = 0;

    for (int i = 0; i < numLocations - 1; i++) {
        int min = INT_MAX, u = -1;
        for (int v = 0; v < numLocations; v++) {
            if (!visited[v] && dist[v] < min) {
                min = dist[v];
                u = v;
            }
        }

        visited[u] = 1;
        for (int v = 0; v < numLocations; v++) {
            if (!visited[v] && graph[u][v] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    printf("Shortest distances from location %d:\n", start);
    for (int i = 0; i < numLocations; i++) {
        if (dist[i] == INT_MAX) {
            printf("Location %d is unreachable\n", i);
        } else {
            printf("Location %d: %d units\n", i, dist[i]);
        }
    }
}

int main() {
    int locations, routes;
    printf("Enter number of locations: ");
    scanf("%d", &locations);
    
    initGraph(locations);

    printf("Enter number of routes: ");
    scanf("%d", &routes);
    
    for (int i = 0; i < routes; i++) {
        int from, to, distance;
        printf("Enter route (from, to, distance): ");
        scanf("%d %d %d", &from, &to, &distance);
        addRoute(from, to, distance);
    }

    int startLocation;
    printf("Enter starting location: ");
    scanf("%d", &startLocation);

    dijkstra(startLocation);

    return 0;
}
