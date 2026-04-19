/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** criticalConnections(int n, int** connections, int connectionsSize, int* connectionsColSize, int* returnSize, int** returnColumnSizes) {
    // Build adjacency list
    int** graph = (int**)malloc(n * sizeof(int*));
    int* graphSize = (int*)calloc(n, sizeof(int));
    int* graphCapacity = (int*)calloc(n, sizeof(int));
    
    // Initialize each adjacency list
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(2 * sizeof(int)); // Initial capacity
        graphCapacity[i] = 2;
        graphSize[i] = 0;
    }
    
    // Add edges to adjacency list
    for (int i = 0; i < connectionsSize; i++) {
        int u = connections[i][0];
        int v = connections[i][1];
        
        // Add v to u's list
        if (graphSize[u] >= graphCapacity[u]) {
            graphCapacity[u] *= 2;
            graph[u] = (int*)realloc(graph[u], graphCapacity[u] * sizeof(int));
        }
        graph[u][graphSize[u]++] = v;
        
        // Add u to v's list
        if (graphSize[v] >= graphCapacity[v]) {
            graphCapacity[v] *= 2;
            graph[v] = (int*)realloc(graph[v], graphCapacity[v] * sizeof(int));
        }
        graph[v][graphSize[v]++] = u;
    }
    
    // Tracking arrays
    int* disc = (int*)malloc(n * sizeof(int));
    int* low = (int*)malloc(n * sizeof(int));
    int* parent = (int*)malloc(n * sizeof(int));
    int* visited = (int*)calloc(n, sizeof(int));
    
    // Initialize
    for (int i = 0; i < n; i++) {
        disc[i] = -1;
        low[i] = -1;
        parent[i] = -1;
    }
    
    // Result storage (max possible bridges = n-1)
    int** result = (int**)malloc((n - 1) * sizeof(int*));
    int resultSize = 0;
    int time = 0;
    
    // DFS function (recursive)
    void dfs(int u) {
        visited[u] = 1;
        disc[u] = low[u] = time++;
        
        for (int i = 0; i < graphSize[u]; i++) {
            int v = graph[u][i];
            
            if (!visited[v]) {
                parent[v] = u;
                dfs(v);
                
                // Update low value
                if (low[v] < low[u]) {
                    low[u] = low[v];
                }
                
                // Check if edge (u, v) is a bridge
                if (low[v] > disc[u]) {
                    // Add to result
                    result[resultSize] = (int*)malloc(2 * sizeof(int));
                    result[resultSize][0] = u;
                    result[resultSize][1] = v;
                    resultSize++;
                }
            }
            else if (v != parent[u]) {
                // Back edge
                if (disc[v] < low[u]) {
                    low[u] = disc[v];
                }
            }
        }
    }
    
    // Start DFS from node 0 (graph is connected as per problem)
    dfs(0);
    
    // Set return values
    *returnSize = resultSize;
    *returnColumnSizes = (int*)malloc(resultSize * sizeof(int));
    for (int i = 0; i < resultSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    
    // Free memory
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphSize);
    free(graphCapacity);
    free(disc);
    free(low);
    free(parent);
    free(visited);
    
    return result;
}