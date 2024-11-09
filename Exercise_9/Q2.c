#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define MAX_GRID_SIZE 100
#define INF INT_MAX
int rows, cols;
int dirX[] = {0, 0, -1, 1};
int dirY[] = {-1, 1, 0, 0};

typedef struct {
    int x, y;
} Node;

int grid[MAX_GRID_SIZE][MAX_GRID_SIZE];  // 0 for empty space, 1 for obstacle
int heuristic(Node a, Node b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}
void aStarSearch(Node start, Node goal) {
    int openList[MAX_GRID_SIZE][MAX_GRID_SIZE] = {0}; // 1 if node is in open list
    int gCost[MAX_GRID_SIZE][MAX_GRID_SIZE], fCost[MAX_GRID_SIZE][MAX_GRID_SIZE];
    Node cameFrom[MAX_GRID_SIZE][MAX_GRID_SIZE]; // Keep track of the path

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            gCost[i][j] = INF;
            fCost[i][j] = INF;
        }
    }

    gCost[start.x][start.y] = 0;
    fCost[start.x][start.y] = heuristic(start, goal);
    
    openList[start.x][start.y] = 1;

    while (1) {
        int minF = INF;
        Node current = {-1, -1};
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (openList[i][j] && fCost[i][j] < minF) {
                    minF = fCost[i][j];
                    current = (Node){i, j};
                }
            }
        }

        if (current.x == -1) {
            printf("No path found!\n");
            return;
        }
        if (current.x == goal.x && current.y == goal.y) {
            printf("Path found: ");
            Node pathNode = goal;
            while (pathNode.x != start.x || pathNode.y != start.y) {
                printf("(%d, %d) <- ", pathNode.x, pathNode.y);
                pathNode = cameFrom[pathNode.x][pathNode.y];
            }
            printf("(%d, %d)\n", start.x, start.y);
            return;
        }
        openList[current.x][current.y] = 0;
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dirX[i], ny = current.y + dirY[i];
            if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && grid[nx][ny] == 0) {
                int tentativeGCost = gCost[current.x][current.y] + 1;
                if (tentativeGCost < gCost[nx][ny]) {
                    cameFrom[nx][ny] = current;
                    gCost[nx][ny] = tentativeGCost;
                    fCost[nx][ny] = gCost[nx][ny] + heuristic((Node){nx, ny}, goal);
                    if (!openList[nx][ny]) {
                        openList[nx][ny] = 1;
                    }
                }
            }
        }
    }
}

int main() {
    printf("Enter grid size (rows cols): ");
    scanf("%d %d", &rows, &cols);

    printf("Enter grid (0 for empty, 1 for obstacle):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    Node start, goal;
    printf("Enter start position (x y): ");
    scanf("%d %d", &start.x, &start.y);
    printf("Enter goal position (x y): ");
    scanf("%d %d", &goal.x, &goal.y);

    aStarSearch(start, goal);
    return 0;
}
