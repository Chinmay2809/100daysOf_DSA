#include <stdbool.h>
#include <stdlib.h>

int find(int parent[], int x) {
    if (parent[x] != x) {
        parent[x] = find(parent, parent[x]);
    }
    return parent[x];
}

bool isCycle(int V, int edges[][2], int E) {
    // Dynamically allocate parent array
    int* parent = (int*)malloc(V * sizeof(int));
    if (!parent) return false;
    
    // Initialize
    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }
    
    // Check for cycle
    for (int i = 0; i < E; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        
        int rootU = find(parent, u);
        int rootV = find(parent, v);
        
        if (rootU == rootV) {
            free(parent);
            return true;
        }
        
        parent[rootU] = rootV;
    }
    
    free(parent);
    return false;
}