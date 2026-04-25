#define INF 1000000

int findTheCity(int n, int** edges, int edgesSize, int* edgesColSize, int distanceThreshold) {
    // Create distance matrix
    int dist[100][100];
    
    // Initialize distance matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
        }
    }
    
    // Fill direct edges (bidirectional)
    for (int i = 0; i < edgesSize; i++) {
        int from = edges[i][0];
        int to = edges[i][1];
        int weight = edges[i][2];
        
        if (weight < dist[from][to]) {  // Handle multiple edges between same cities
            dist[from][to] = weight;
            dist[to][from] = weight;
        }
    }
    
    // Floyd-Warshall algorithm to find all pairs shortest paths
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    // Count reachable cities within threshold for each city
    int minCount = n;
    int resultCity = 0;
    
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] <= distanceThreshold) {
                count++;
            }
        }
        
        // Update result: smaller count wins, if tie then greater city number
        if (count < minCount) {
            minCount = count;
            resultCity = i;
        } else if (count == minCount && i > resultCity) {
            resultCity = i;
        }
    }
    
    return resultCity;
}