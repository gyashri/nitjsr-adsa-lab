#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20

int graph[MAX][MAX];
int V;
bool visited[MAX];
int path[MAX], pathIndex = 0;

// To track cycle lengths
int minCycle = 1e9, maxCycle = -1;

// Function to print a cycle
void printCycle(int start) {
    printf("Cycle found: ");
    for (int i = start; i < pathIndex; i++) {
        printf("%d ", path[i]);
    }
    printf("%d\n", path[start]); // close the cycle
}

// DFS to detect cycles
void DFS(int u, int parent, bool directed) {
    visited[u] = true;
    path[pathIndex++] = u;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                DFS(v, u, directed);
            }
            else {
                // For directed graph: back edge forms a cycle
                // For undirected: avoid considering parent edge
                if (directed || v != parent) {
                    // Find where cycle starts in path
                    for (int i = 0; i < pathIndex; i++) {
                        if (path[i] == v) {
                            int cycleLength = pathIndex - i;
                            if (cycleLength >= 2) {
                                if (cycleLength < minCycle) minCycle = cycleLength;
                                if (cycleLength > maxCycle) maxCycle = cycleLength;
                                printCycle(i);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    pathIndex--;
    visited[u] = false; // unmark for other paths
}

void findCycles(bool directed) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            visited[j] = false;
        }
        pathIndex = 0;
        DFS(i, -1, directed);
    }

    if (maxCycle == -1) {
        printf("No cycles found.\n");
    } else {
        printf("\nSmallest cycle length: %d\n", minCycle);
        printf("Largest cycle length: %d\n", maxCycle);
    }
}

int main() {
    int directed;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Is the graph directed? (1=Yes, 0=No): ");
    scanf("%d", &directed);

    printf("Enter adjacency matrix (%d x %d):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    findCycles(directed);

    return 0;
}
