#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int n, e;
int adj[MAX][MAX];
int color[MAX]; // 0 = uncolored, 1 = color1, -1 = color2

// Queue for BFS
int queue[MAX];
int front = 0, rear = 0;

void enqueue(int x) {
    queue[rear++] = x;
}

int dequeue() {
    return queue[front++];
}

bool isQueueEmpty() {
    return front == rear;
}

// Function to check if graph is bipartite using BFS
bool isBipartite() {
    for (int i = 0; i < n; i++)
        color[i] = 0; // initialize all vertices as uncolored

    for (int start = 0; start < n; start++) {
        if (color[start] != 0)
            continue; // already colored

        // Start BFS from this vertex
        enqueue(start);
        color[start] = 1;

        while (!isQueueEmpty()) {
            int u = dequeue();

            for (int v = 0; v < n; v++) {
                if (adj[u][v]) {
                    if (color[v] == 0) {
                        // Assign opposite color to adjacent vertex
                        color[v] = -color[u];
                        enqueue(v);
                    } else if (color[v] == color[u]) {
                        // Same color as neighbor → Not bipartite
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter edges (u v) 0-indexed:\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1; // undirected graph
    }

    if (isBipartite()) {
        printf("Graph is Bipartite\n");
    } else {
        printf("Graph is NOT Bipartite\n");
    }

    return 0;
}
