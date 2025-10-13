#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int n, e;
int adj[MAX][MAX];
int path[MAX];

// Function to check if it is safe to add vertex v to the Hamiltonian path at position pos
bool isSafe(int v, int pos) {
    // Check if this vertex is adjacent to the previous vertex
    if (adj[path[pos - 1]][v] == 0)
        return false;

    // Check if this vertex has already been included in the path
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// Recursive function to find Hamiltonian Cycle
bool hamCycleUtil(int pos) {
    // Base case: all vertices are included
    if (pos == n) {
        // And there is an edge from last included vertex to the first vertex
        if (adj[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    // Try different vertices as the next candidate
    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            if (hamCycleUtil(pos + 1))
                return true;
            path[pos] = -1; // backtrack
        }
    }
    return false;
}

// Function to solve the Hamiltonian Cycle problem
bool hamCycle() {
    // Initialize path
    for (int i = 0; i < n; i++)
        path[i] = -1;

    // Start at vertex 0
    path[0] = 0;

    if (hamCycleUtil(1) == false) {
        return false;
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
        adj[v][u] = 1; // assuming undirected graph
    }

    if (hamCycle()) {
        printf("Graph contains a Hamiltonian Cycle\n");
        printf("Cycle: ");
        for (int i = 0; i < n; i++)
            printf("%d ", path[i]);
        printf("%d\n", path[0]); // complete the cycle
    } else {
        printf("Graph does NOT contain a Hamiltonian Cycle\n");
    }

    return 0;
}
