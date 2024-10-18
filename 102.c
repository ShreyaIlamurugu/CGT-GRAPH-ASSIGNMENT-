#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int graph[MAX][MAX]; // Adjacency matrix for the graph
int degree[MAX];     // Array to store degrees of vertices
int visited[MAX];    // Array to mark visited edges

// Function to check if all vertices with non-zero degree are connected
void DFS(int vertex, int n)
{
    visited[vertex] = 1;
    for (int i = 0; i < n; i++)
    {
        if (graph[vertex][i] && !visited[i])
        {
            DFS(i, n);
        }
    }
}

// Check if the graph is connected for vertices with non-zero degree
int isConnected(int n)
{
    int i;
    for (i = 0; i < n; i++)
        visited[i] = 0;
    for (i = 0; i < n; i++)
    {
        if (degree[i] > 0)
        {
            break;
        }
    }
    if (i == n)
        return 1;
    DFS(i, n);
    for (i = 0; i < n; i++)
    {
        if (degree[i] > 0 && !visited[i])
        {
            return 0;
        }
    }
    return 1;
}

// Function to check if the graph has an Eulerian Path or Circuit
int isEulerian(int n)
{
    if (!isConnected(n))
    {
        return 0;
    }
    int odd = 0;
    for (int i = 0; i < n; i++)
    {
        if (degree[i] % 2 != 0)
        {
            odd++;
        }
    }
    // If odd is 0, then Eulerian Circuit exists, return 2
    if (odd == 0)
    {
        return 2;
    }
    // If odd is 2, then Eulerian Path exists, return 1
    if (odd == 2)
    {
        return 1;
    }
    return 0;
}

// Check if removing edge u-v would disconnect the graph
int isValidEdge(int u, int v, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (graph[u][i])
        {
            count++;
        }
    }
    if (count == 1)
    {
        return 1;
    }
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    DFS(u, n);
    int before_removal = visited[v];
    graph[u][v] = graph[v][u] = 0;
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    DFS(u, n);
    int after_removal = visited[v];
    graph[u][v] = graph[v][u] = 1;
    return before_removal == after_removal;
}

// Fleury's Algorithm to print Eulerian Path or Circuit
void printEulerian(int u, int n)
{
    for (int v = 0; v < n; v++)
    {
        if (graph[u][v] && isValidEdge(u, v, n))
        {
            printf("%d-%d ", u, v);
            graph[u][v] = graph[v][u] = 0;
            printEulerian(v, n);
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix of the graph:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
            if (graph[i][j])
            {
                degree[i]++;
            }
        }
    }
    int eulerianType = isEulerian(n);
    if (eulerianType == 0)
    {
        printf("The graph is not Eulerian.\n");
    }
    else if (eulerianType == 1)
    {
        printf("The graph has an Eulerian Path.\n");
        // Find a vertex with odd degree to start the Eulerian path
        int startVertex = 0;
        for (int i = 0; i < n; i++)
        {
            if (degree[i] % 2 != 0)
            {
                startVertex = i;
                break;
            }
        }
        printEulerian(startVertex, n);
        printf("\n");
    }
    else
    {
        printf("The graph has an Eulerian Circuit.\n");
        int startVertex = 0;
        for (int i = 0; i < n; i++)
        {
            if (degree[i] > 0)
            {
                startVertex = i;
                break;
            }
        }
        printEulerian(startVertex, n);
        printf("\n");
    }
    return 0;
}