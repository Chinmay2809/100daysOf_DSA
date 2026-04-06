int search(int* inorder, int start, int end, int val)
{
    for(int i = start; i <= end; i++)
    {
        if(inorder[i] == val)
            return i;
    }
    return -1;
}

struct TreeNode* build(int* inorder, int* postorder, int start, int end, int* postIndex)
{
    if(start > end)
        return NULL;

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = postorder[*postIndex];
    root->left = root->right = NULL;

    (*postIndex)--;

    if(start == end)
        return root;

    int inIndex = search(inorder, start, end, root->val);

    // IMPORTANT: build right first
    root->right = build(inorder, postorder, inIndex + 1, end, postIndex);
    root->left = build(inorder, postorder, start, inIndex - 1, postIndex);

    return root;
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) 
{
    int postIndex = postorderSize - 1;
    return build(inorder, postorder, 0, inorderSize - 1, &postIndex);
}