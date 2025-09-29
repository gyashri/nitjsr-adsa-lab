#include <stdio.h>

int maxProfit = 0;   // to store the maximum profit found
int n;               // number of items
int W;               // capacity of knapsack

void knapsackBacktrack(int i, int currentWeight, int currentProfit, int wt[], int val[]) {
    // Base condition: all items considered
    if (i == n) {
        if (currentProfit > maxProfit && currentWeight <= W)
            maxProfit = currentProfit;
        return;
    }

    // Option 1: Include item i (if it fits)
    if (currentWeight + wt[i] <= W)
        knapsackBacktrack(i + 1, currentWeight + wt[i], currentProfit + val[i], wt, val);

    // Option 2: Exclude item i
    knapsackBacktrack(i + 1, currentWeight, currentProfit, wt, val);
}

int main() {
    printf("Enter number of items: ");
    scanf("%d", &n);

    int wt[n], val[n];

    printf("Enter values of items:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &val[i]);

    printf("Enter weights of items:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &wt[i]);

    printf("Enter capacity of knapsack: ");
    scanf("%d", &W);

    // Start backtracking from 0th item
    knapsackBacktrack(0, 0, 0, wt, val);

    printf("\nMaximum profit = %d\n", maxProfit);

    return 0;
}
