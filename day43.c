#include <stdlib.h>
#include <stdio.h>

// NOTE: struct TreeNode is predefined in LeetCode
// Do NOT redefine it

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// Helper function to count nodes
int countNodes(struct TreeNode* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Helper function for recursive preorder traversal
void preorderHelper(struct TreeNode* root, int* result, int* index) {
    if (root == NULL) return;
    
    result[(*index)++] = root->val;          // Visit root
    preorderHelper(root->left, result, index); // Traverse left
    preorderHelper(root->right, result, index); // Traverse right
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    
    // Count nodes to allocate appropriate size
    int nodeCount = countNodes(root);
    int* result = (int*)malloc(nodeCount * sizeof(int));
    *returnSize = 0;
    
    // Perform preorder traversal
    preorderHelper(root, result, returnSize);
    
    return result;
}