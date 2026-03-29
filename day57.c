void flatten(struct TreeNode* root) {
    if (root == NULL) return;
    
    // Flatten left and right subtrees first
    flatten(root->left);
    flatten(root->right);
    
    // Store the right subtree
    struct TreeNode* rightSubtree = root->right;
    
    // Move left subtree to right
    root->right = root->left;
    root->left = NULL;
    
    // Find the end of the new right subtree (was left)
    struct TreeNode* curr = root;
    while (curr->right != NULL) {
        curr = curr->right;
    }
    
    // Attach the original right subtree
    curr->right = rightSubtree;
}