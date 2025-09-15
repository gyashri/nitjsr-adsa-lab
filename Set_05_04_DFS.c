#include <stdio.h>
#include <stdlib.h>

#define MAX 20

// Graph represented as adjacency matrix
int graph[MAX][MAX];
int V;   // number of vertices

// Arrays for DFS
int visited[MAX], discovery[MAX], finish[MAX];
int timeCounter = 0;

// DFS function
void DFS(int u) {
    visited[u] = 1;
    discovery[u] = ++timeCounter;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) { // If edge u->v exists
            if (visited[v] == 0) {
                printf("Tree Edge: %d -> %d\n", u, v);
                DFS(v);
            }
            else if (visited[v] == 1) {
                printf("Back Edge: %d -> %d\n", u, v);
            }
            else if (visited[v] == 2) {
                if (discovery[u] < discovery[v]) {
                    printf("Forward Edge: %d -> %d\n", u, v);
                } else {
                    printf("Cross Edge: %d -> %d\n", u, v);
                }
            }
        }
    }

    visited[u] = 2;  // mark as finished
    finish[u] = ++timeCounter;
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter adjacency matrix (%d x %d):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    for (int i = 0; i < V; i++) {
        visited[i] = 0;
        discovery[i] = 0;
        finish[i] = 0;
    }

    printf("\nDFS Traversal and Edge Classification:\n");
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            DFS(i);
        }
    }

    printf("\nDiscovery and Finish times:\n");
    for (int i = 0; i < V; i++) {
        printf("Vertex %d: d=%d, f=%d\n", i, discovery[i], finish[i]);
    }

    return 0;
}
