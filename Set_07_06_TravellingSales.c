#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 20
#define INF 999999

int n; // number of cities
int dist[MAX][MAX];
int dp[1 << MAX][MAX]; // DP table

int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1)
        return dist[pos][0]; // return to starting city

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) { // city not visited
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            if (newAns < ans)
                ans = newAns;
        }
    }

    return dp[mask][pos] = ans;
}

int main() {
    printf("Enter number of cities (<=20): ");
    scanf("%d", &n);

    printf("Enter distance matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }

    for (int i = 0; i < (1 << n); i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = -1;

    clock_t start = clock();
    int ans = tsp(1, 0); // start from city 0
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nMinimum tour cost: %d\n", ans);
    printf("Execution time: %.6f seconds\n", time_taken);

    return 0;
}
