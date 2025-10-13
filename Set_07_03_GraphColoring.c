#include <stdio.h>
#include <stdbool.h>

#define V 4   // Number of vertices in the graph

// Function to print the solution (color assignment)
void printSolution(int color[]) {
    printf("Color assignment for vertices:\n");
    for (int i = 0; i < V; i++)
        printf("Vertex %d ---> Color %d\n", i + 1, color[i]);
}

// Function to check if assigning color c to vertex v is valid
bool isSafe(int v, int graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && color[i] == c) // adjacent vertex has same color
            return false;
    return true;
}

// Recursive utility function to solve the graph coloring problem
bool graphColoringUtil(int graph[V][V], int m, int color[], int v) {
    // Base case: if all vertices are assigned a color
    if (v == V)
        return true;

    // Try assigning each color (1 to m)
    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c; // Assign color c

            // Recur to assign colors to the rest of the vertices
            if (graphColoringUtil(graph, m, color, v + 1))
                return true;

            // If assigning color c doesn't lead to a solution, backtrack
            color[v] = 0;
        }
    }

    return false; // If no color can be assigned
}

// Function to solve the m Coloring problem
void graphColoring(int graph[V][V], int m) {
    int color[V] = {0}; // Initialize all vertices as uncolored (0)

    if (graphColoringUtil(graph, m, color, 0))
        printSolution(color);
    else
        printf("No solution exists with %d colors.\n", m);
}

// Main function
int main() {
    int graph[V][V];

    printf("Enter the adjacency matrix for the graph (%dx%d):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int m;
    printf("Enter the number of colors available: ");
    scanf("%d", &m);

    graphColoring(graph, m);

    return 0;
}
