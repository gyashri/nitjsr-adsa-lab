#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4   // 4x4 puzzle

// Structure to store puzzle state
typedef struct Node {
    int mat[N][N];
    int x, y;          // Blank tile position
    int cost;          // Heuristic cost
    int level;         // Depth level
    struct Node* parent;
} Node;

// Target configuration
int final[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

// Possible moves: up, down, left, right
int row[] = {1, -1, 0, 0};
int col[] = {0, 0, -1, 1};

// Function to create a new node
Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));

    // Copy data from parent matrix to new matrix
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            node->mat[i][j] = mat[i][j];

    // Move tile
    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->x = newX;
    node->y = newY;
    node->parent = parent;
    node->level = level;
    node->cost = 0;

    return node;
}

// Heuristic: Manhattan Distance
int calculateCost(int initial[N][N], int final[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (initial[i][j] != 0) {
                int value = initial[i][j];
                int targetX = (value - 1) / N;
                int targetY = (value - 1) % N;
                cost += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return cost;
}

// Check if (x, y) is a valid cell
int isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Print matrix
void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%2d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

// Print path from root to solution
void printPath(Node* root) {
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);
}

// Comparator for priority queue (min-heap)
int compare(const void* a, const void* b) {
    Node* node1 = *(Node**)a;
    Node* node2 = *(Node**)b;
    return (node1->cost + node1->level) - (node2->cost + node2->level);
}

// Solve 15 Puzzle using Branch and Bound
void solve(int initial[N][N], int x, int y) {
    // Create initial node
    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);

    // Priority queue (array-based)
    Node* pq[10000];
    int size = 0;
    pq[size++] = root;

    while (size > 0) {
        // Sort queue by cost + level
        qsort(pq, size, sizeof(Node*), compare);

        // Get node with least cost
        Node* min = pq[0];

        // Remove from queue
        for (int i = 0; i < size - 1; i++)
            pq[i] = pq[i + 1];
        size--;

        // If cost is 0 → goal reached
        if (min->cost == 0) {
            printf("\nSolution found at level %d:\n", min->level);
            printPath(min);
            return;
        }

        // Explore possible moves
        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];

            if (isSafe(newX, newY)) {
                Node* child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = calculateCost(child->mat, final);
                pq[size++] = child;
            }
        }
    }
}

int main() {
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13, 14, 11, 15}
    };

    int x = 1, y = 2; // Blank tile position in initial state

    printf("Initial Puzzle:\n");
    printMatrix(initial);
    printf("\nSolving...\n");

    solve(initial, x, y);

    return 0;
}
