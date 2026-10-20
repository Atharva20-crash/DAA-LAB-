#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 1000000000000LL

long long **cost;
long long **dp;
int n;

long long tsp(int mask, int pos) {
    if (mask == (1 << n) - 1) {
        if (cost[pos][0] == -1)
            return INF;
        return cost[pos][0];
    }

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    long long ans = INF;

    for (int city = 0; city < n; city++) {
        if (!(mask & (1 << city)) && cost[pos][city] != -1) {
            long long nextCost = tsp(mask | (1 << city), city);

            if (nextCost != INF) {
                long long total = cost[pos][city] + nextCost;
                if (total < ans)
                    ans = total;
            }
        }
    }

    dp[mask][pos] = ans;
    return ans;
}

int main() {
    scanf("%d", &n);

    cost = (long long **)malloc(n * sizeof(long long *));
    for (int i = 0; i < n; i++)
        cost[i] = (long long *)malloc(n * sizeof(long long));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lld", &cost[i][j]);
        }
    }

    int states = 1 << n;

    dp = (long long **)malloc(states * sizeof(long long *));
    for (int i = 0; i < states; i++) {
        dp[i] = (long long *)malloc(n * sizeof(long long));
        for (int j = 0; j < n; j++)
            dp[i][j] = -1;
    }

    long long answer = tsp(1, 0);

    printf("%lld\n", answer);

    for (int i = 0; i < n; i++)
        free(cost[i]);
    free(cost);

    for (int i = 0; i < states; i++)
        free(dp[i]);
    free(dp);

    return 0;
} 
