using System;
using System.Collections.Generic;
using System.Linq;

public class Solution {
    private int time = 0;
    
    public List<int> articulationPoints(int v, List<int>[] adj) {
        bool[] visited = new bool[v];
        int[] disc = new int[v];
        int[] low = new int[v];
        int[] parent = new int[v];
        bool[] ap = new bool[v];
        
        // Initialize arrays
        for (int i = 0; i < v; i++) {
            disc[i] = -1;
            low[i] = -1;
            parent[i] = -1;
        }
        
        time = 0;
        
        // DFS from each unvisited node (graph might be disconnected)
        for (int i = 0; i < v; i++) {
            if (!visited[i]) {
                DFS(i, visited, disc, low, parent, ap, adj);
            }
        }
        
        // Collect articulation points
        List<int> result = new List<int>();
        for (int i = 0; i < v; i++) {
            if (ap[i]) {
                result.Add(i);
            }
        }
        
        return result;
    }
    
    private void DFS(int u, bool[] visited, int[] disc, int[] low, 
                     int[] parent, bool[] ap, List<int>[] adj) {
        int children = 0;
        visited[u] = true;
        disc[u] = low[u] = time++;
        
        foreach (int v_adj in adj[u]) {
            if (!visited[v_adj]) {
                children++;
                parent[v_adj] = u;
                DFS(v_adj, visited, disc, low, parent, ap, adj);
                
                // Update low value
                low[u] = Math.Min(low[u], low[v_adj]);
                
                // u is an articulation point if:
                // 1. u is root and has at least 2 children
                if (parent[u] == -1 && children > 1) {
                    ap[u] = true;
                }
                // 2. u is not root and low[v_adj] >= disc[u]
                if (parent[u] != -1 && low[v_adj] >= disc[u]) {
                    ap[u] = true;
                }
            }
            else if (v_adj != parent[u]) {
                // Back edge
                low[u] = Math.Min(low[u], disc[v_adj]);
            }
        }
    }
}