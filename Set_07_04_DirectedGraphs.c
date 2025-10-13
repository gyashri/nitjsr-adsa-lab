#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// ---------------- STRONGLY CONNECTED COMPONENTS (Kosaraju) ----------------

int visited[MAX];
int adj[MAX][MAX], rev[MAX][MAX];
int stack[MAX], top = -1;
int n;

void dfs1(int v) {
    visited[v] = 1;
    for (int i = 0; i < n; i++)
        if (adj[v][i] && !visited[i])
            dfs1(i);
    stack[++top] = v;
}

void dfs2(int v) {
    printf("%d ", v);
    visited[v] = 1;
    for (int i = 0; i < n; i++)
        if (rev[v][i] && !visited[i])
            dfs2(i);
}

void findSCCs() {
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs1(i);

    // Reverse graph
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            rev[i][j] = adj[j][i];

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("\nStrongly Connected Components:\n");
    while (top != -1) {
        int v = stack[top--];
        if (!visited[v]) {
            dfs2(v);
            printf("\n");
        }
    }
}

// ---------------- ARTICULATION POINTS & BRIDGES (Tarjan) ----------------

int timeCounter = 0;
int disc[MAX], low[MAX], parent[MAX];
bool ap[MAX]; // articulation points
int adjU[MAX][MAX]; // undirected graph

void APUtil(int u) {
    int children = 0;
    visited[u] = 1;
    disc[u] = low[u] = ++timeCounter;

    for (int v = 0; v < n; v++) {
        if (adjU[u][v]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                APUtil(v);

                low[u] = (low[u] < low[v]) ? low[u] : low[v];

                // Articulation Point condition
                if (parent[u] == -1 && children > 1)
                    ap[u] = true;
                if (parent[u] != -1 && low[v] >= disc[u])
                    ap[u] = true;

                // Bridge condition
                if (low[v] > disc[u])
                    printf("Bridge: (%d - %d)\n", u, v);
            }
            else if (v != parent[u])
                low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}

void findArticulationPointsAndBridges() {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
        ap[i] = false;
    }

    for (int i = 0; i < n; i++)
        if (!visited[i])
            APUtil(i);

    printf("\nArticulation Points:\n");
    for (int i = 0; i < n; i++)
        if (ap[i])
            printf("%d ", i);
    printf("\n");
}

// ---------------- BICONNECTED COMPONENTS (Tarjan) ----------------

typedef struct {
    int u, v;
} Edge;

Edge stackBCC[MAX];
int topBCC = -1;

void pushEdge(int u, int v) {
    stackBCC[++topBCC].u = u;
    stackBCC[topBCC].v = v;
}

void printBCC(int u, int v) {
    printf("Biconnected Component: ");
    while (topBCC >= 0) {
        Edge e = stackBCC[topBCC--];
        printf("(%d-%d) ", e.u, e.v);
        if (e.u == u && e.v == v)
            break;
    }
    printf("\n");
}

void BCCUtil(int u) {
    int children = 0;
    visited[u] = 1;
    disc[u] = low[u] = ++timeCounter;

    for (int v = 0; v < n; v++) {
        if (adjU[u][v]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                pushEdge(u, v);
                BCCUtil(v);

                low[u] = (low[u] < low[v]) ? low[u] : low[v];

                if ((parent[u] == -1 && children > 1) ||
                    (parent[u] != -1 && low[v] >= disc[u]))
                    printBCC(u, v);
            }
            else if (v != parent[u] && disc[v] < disc[u]) {
                low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
                pushEdge(u, v);
            }
        }
    }
}

void findBCCs() {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
    timeCounter = 0;
    topBCC = -1;

    for (int i = 0; i < n; i++)
        if (!visited[i])
            BCCUtil(i);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("\nEnter adjacency matrix for directed graph (for SCC):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);

    findSCCs();

    printf("\nEnter adjacency matrix for undirected graph (for BCC/AP/Bridges):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adjU[i][j]);

    findArticulationPointsAndBridges();
    findBCCs();

    return 0;
}
