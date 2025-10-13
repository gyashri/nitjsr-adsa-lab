#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int n, e, m;
int adj[MAX][MAX];

// Function to check if a subset of vertices forms a clique
bool isClique(int subset[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (adj[subset[i]][subset[j]] == 0) {
                return false;
            }
        }
    }
    return true;
}

// Function to generate all subsets of size m and check for clique
bool findClique(int subset[], int index, int start) {
    if (index == m) {
        return isClique(subset, m);
    }

    for (int i = start; i < n; i++) {
        subset[index] = i;
        if (findClique(subset, index + 1, i + 1))
            return true;
    }
    return false;
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);
    printf("Enter size of clique to find: ");
    scanf("%d", &m);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter edges (u v) 0-indexed:\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    int subset[MAX];
    if (findClique(subset, 0, 0)) {
        printf("Graph contains a clique of size %d\n", m);
    } else {
        printf("Graph does NOT contain a clique of size %d\n", m);
    }

    return 0;
}
