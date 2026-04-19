void dfs(int** isConnected, int n, int city, int* visited)
{
    for(int i = 0; i < n; i++)
    {
        if(isConnected[city][i] == 1 && !visited[i])
        {
            visited[i] = 1;
            dfs(isConnected, n, i, visited);
        }
    }
}

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize) 
{
    int n = isConnectedSize;
    int visited[n];
    
    for(int i = 0; i < n; i++)
        visited[i] = 0;

    int provinces = 0;

    for(int i = 0; i < n; i++)
    {
        if(!visited[i])
        {
            visited[i] = 1;
            dfs(isConnected, n, i, visited);
            provinces++;
        }
    }

    return provinces;
}