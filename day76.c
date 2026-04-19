/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numNeighbors;
 *     struct Node** neighbors;
 * };
 */

// Global visited array
struct Node* visited[101];

// DFS function
struct Node* dfs(struct Node* node) {
    if (node == NULL) return NULL;
    
    // If already cloned, return it
    if (visited[node->val] != NULL) {
        return visited[node->val];
    }
    
    // Create clone of current node
    struct Node* clone = (struct Node*)malloc(sizeof(struct Node));
    clone->val = node->val;
    clone->numNeighbors = node->numNeighbors;
    
    // Allocate memory for neighbors array
    if (node->numNeighbors > 0) {
        clone->neighbors = (struct Node**)malloc(node->numNeighbors * sizeof(struct Node*));
    } else {
        clone->neighbors = NULL;
    }
    
    // Mark as visited
    visited[node->val] = clone;
    
    // Recursively clone all neighbors
    for (int i = 0; i < node->numNeighbors; i++) {
        clone->neighbors[i] = dfs(node->neighbors[i]);
    }
    
    return clone;
}

struct Node* cloneGraph(struct Node* s) {
    // Initialize visited array to NULL
    for (int i = 0; i < 101; i++) {
        visited[i] = NULL;
    }
    
    return dfs(s);
}