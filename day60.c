int cameras = 0;

int dfs(struct TreeNode* root)
{
    if(root == NULL)
        return 2; // NULL nodes are covered

    int left = dfs(root->left);
    int right = dfs(root->right);

    // If any child is not covered → place camera here
    if(left == 0 || right == 0)
    {
        cameras++;
        return 1; // has camera
    }

    // If any child has camera → this node is covered
    if(left == 1 || right == 1)
        return 2;

    // Otherwise → not covered
    return 0;
}

int minCameraCover(struct TreeNode* root) 
{
    cameras = 0;

    // If root is not covered, add one camera
    if(dfs(root) == 0)
        cameras++;

    return cameras;
}