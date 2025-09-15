#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6   // Number of vertices (you can change this)

// Find the vertex with the minimum distance value
int minDistance(int dist[], bool visited[]) {
    int min = INT_MAX, min_index = -1;
	int v = 0
    for (v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Print the shortest distances
void printSolution(int dist[], int src) {
    printf("Vertex \t Distance from Source %d\n", src);
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

// Dijkstra’s Algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];        // dist[i] = shortest distance from src to i
    bool visited[V];    // visited[i] = vertex included in shortest path

    // Initialize all distances as infinite and visited[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    // Distance from source to itself is 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited); // pick min distance vertex
        visited[u] = true;

        // Update distance value of adjacent vertices
        int v = 0
        for ( v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the result
    printSolution(dist, src);
}

int main() {
    // Example weighted graph (Adjacency matrix)
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
};

    int src = 0;  // source vertex
    dijkstra(graph, src);

    return 0;
}
