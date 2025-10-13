#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];  // adjacency matrix
int visited[MAX];
int stack[MAX];
int top = -1;
int n; // number of vertices

// Function to push a vertex onto the stack
void push(int v) {
    stack[++top] = v;
}

// DFS function for topological sorting
void dfs(int v) {
    visited[v] = 1;

    for (int i = 0; i < n; i++) {
        if (graph[v][i] && !visited[i]) {
            dfs(i);
        }
    }

    // After visiting all adjacent vertices, push current vertex to stack
    push(v);
}

// Function to perform topological sort
void topologicalSort() {
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i])
            dfs(i);
    }

    printf("\nTopological Order: ");
    while (top != -1)
        printf("%d ", stack[top--]);
    printf("\n");
}

// Main function
int main() {
    int edges, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Initialize graph
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v) meaning edge from u -> v:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
    }

    topologicalSort();

    return 0;
}
