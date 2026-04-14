#include <string.h>
#define INF 1e9

int dp[1 << 15][15];

int travelling_salesman_problem(int** cost, int n) {
    int FULL = (1 << n) - 1;

    // Initialize all states to INF
    for (int mask = 0; mask <= FULL; mask++)
        for (int i = 0; i < n; i++)
            dp[mask][i] = INF;

    // Start at city 0, only city 0 visited
    dp[1][0] = 0;  // mask=0b0001, at city 0, cost=0

    for (int mask = 1; mask <= FULL; mask++) {
        for (int u = 0; u < n; u++) {
            // u must be in the current mask
            if (!(mask & (1 << u))) continue;
            if (dp[mask][u] == INF) continue;

            // Try going to every unvisited city v
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;  // already visited
                int newMask = mask | (1 << v);
                int newCost = dp[mask][u] + cost[u][v];
                if (newCost < dp[newMask][v])
                    dp[newMask][v] = newCost;
            }
        }
    }

    // All cities visited (mask = FULL), return to city 0
    int ans = INF;
    for (int u = 1; u < n; u++) {
        if (dp[FULL][u] == INF) continue;
        int total = dp[FULL][u] + cost[u][0];
        if (total < ans) ans = total;
    }

    return ans;
}