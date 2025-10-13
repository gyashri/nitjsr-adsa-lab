#include <stdio.h>

// Function to find minimum number of coins using Greedy approach
void findMinCoins(int coins[], int n, int amount) {
    int count[10] = {0};  // to store count of each coin
    int i;

    printf("Coins used:\n");

    // Start from the largest denomination
    for (i = 0; i < n; i++) {
        if (amount >= coins[i]) {
            count[i] = amount / coins[i];   // Number of coins of this denomination
            amount = amount % coins[i];     // Remaining amount
        }
    }

    // Display result
    for (i = 0; i < n; i++) {
        if (count[i] != 0) {
            printf("%d coin(s) of %d\n", count[i], coins[i]);
        }
    }
}

int main() {
    int coins[] = {10, 5, 2, 1};  // Available denominations (sorted in descending order)
    int n = sizeof(coins) / sizeof(coins[0]);
    int amount;

    printf("Enter the amount to make change for: ");
    scanf("%d", &amount);

    findMinCoins(coins, n, amount);

    return 0;
}
