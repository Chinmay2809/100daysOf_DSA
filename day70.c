#include <string.h>
#define INF 1e9

int findCheapestPrice(int n, int** flights, int flightsSize, int* flightsColSize,
                      int src, int dst, int k) {
    // dist[i] = cheapest cost to reach city i
    float dist[101], temp[101];
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[src] = 0;

    // Run k+1 rounds (k stops = k+1 edges)
    for (int i = 0; i <= k; i++) {
        // Copy current dist — MUST use temp to avoid using
        // edges from same round (would exceed stop limit)
        memcpy(temp, dist, sizeof(float) * n);

        for (int j = 0; j < flightsSize; j++) {
            int u = flights[j][0];
            int v = flights[j][1];
            int w = flights[j][2];

            if (dist[u] < INF && dist[u] + w < temp[v]) {
                temp[v] = dist[u] + w;
            }
        }

        memcpy(dist, temp, sizeof(float) * n);
    }

    return dist[dst] >= INF ? -1 : (int)dist[dst];
}