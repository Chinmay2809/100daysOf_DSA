#include <stdlib.h>
#include <string.h>
#define INF 1e9

int abs_val(int x) { return x < 0 ? -x : x; }

int manhattan(int* a, int* b) {
    return abs_val(a[0] - b[0]) + abs_val(a[1] - b[1]);
}

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize) {
    int n = pointsSize;
    if (n == 1) return 0;

    // minDist[i] = cheapest edge to add point i into MST
    int* minDist = (int*)malloc(n * sizeof(int));
    int* inMST   = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) minDist[i] = INF;
    minDist[0] = 0;  // start from point 0

    int totalCost = 0;

    for (int iter = 0; iter < n; iter++) {
        // 1. Pick the unvisited point with minimum distance
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!inMST[i] && (u == -1 || minDist[i] < minDist[u]))
                u = i;

        // 2. Add it to MST
        inMST[u] = 1;
        totalCost += minDist[u];

        // 3. Update neighbors' minDist
        for (int v = 0; v < n; v++) {
            if (!inMST[v]) {
                int d = manhattan(points[u], points[v]);
                if (d < minDist[v])
                    minDist[v] = d;
            }
        }
    }

    free(minDist);
    free(inMST);
    return totalCost;
}