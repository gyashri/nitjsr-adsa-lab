#include <stdio.h>
#include <math.h>

#define MAX 20

int board[MAX];
int n;

// Function to print the board configuration
void printSolution() {
    printf("\nOne of the solutions:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i] == j)
                printf(" Q ");
            else
                printf(" . ");
        }
        printf("\n");
    }
}

// Function to check if a queen can be placed at row `r`, column `c`
int isSafe(int r, int c) {
    for (int i = 0; i < r; i++) {
        // Check column and diagonals
        if (board[i] == c || abs(board[i] - c) == abs(i - r))
            return 0;
    }
    return 1;
}

// Recursive backtracking function
void solveNQueens(int r) {
    if (r == n) {
        printSolution();
        return;
    }

    for (int c = 0; c < n; c++) {
        if (isSafe(r, c)) {
            board[r] = c;         // Place queen
            solveNQueens(r + 1);  // Recur for next row
            // Backtrack (no need to reset board[r] explicitly)
        }
    }
}

int main() {
    printf("Enter the number of queens: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of queens! (1 to %d allowed)\n", MAX);
        return 0;
    }

    solveNQueens(0);

    return 0;
}
