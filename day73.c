#include <stdlib.h>

int parent[1001];
int rank_[1001];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);  // path compression
    return parent[x];
}

// Returns 1 if union succeeded, 0 if already in same set (cycle!)
int unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return 0;  // CYCLE DETECTED

    // Union by rank
    if (rank_[px] < rank_[py])      parent[px] = py;
    else if (rank_[px] > rank_[py]) parent[py] = px;
    else { parent[py] = px; rank_[px]++; }

    return 1;
}

int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize,
                              int* returnSize) {
    // Initialize DSU
    for (int i = 1; i <= edgesSize; i++) {
        parent[i] = i;
        rank_[i] = 0;
    }

    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        if (!unite(u, v)) {
            // u and v already connected → this edge creates a cycle
            result[0] = u;
            result[1] = v;
        }
    }

    return result;  // last redundant edge (problem guarantees exactly one)
}