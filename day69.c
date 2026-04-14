#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 1e9

typedef struct {
    int to, w, next;
} Edge;

Edge edges[10005];
int head[105], cnt;
int dist[105];
int visited[105];

void addEdge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dijkstra(int src, int n) {
    for (int i = 1; i <= n; i++) dist[i] = INF, visited[i] = 0;
    dist[src] = 0;

    for (int iter = 0; iter < n; iter++) {
        // Pick unvisited node with min dist
        int u = -1;
        for (int i = 1; i <= n; i++)
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;

        if (u == -1 || dist[u] == INF) break;
        visited[u] = 1;

        // Relax neighbors
        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to, w = edges[e].w;
            if (dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }
}

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k) {
    memset(head, -1, sizeof(head));
    cnt = 0;

    for (int i = 0; i < timesSize; i++)
        addEdge(times[i][0], times[i][1], times[i][2]);

    dijkstra(k, n);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) return -1;  // unreachable node
        if (dist[i] > ans) ans = dist[i];
    }
    return ans;
}