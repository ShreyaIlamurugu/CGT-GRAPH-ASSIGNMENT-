
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

// Number of vertices in the graph
#define V 9
//Dijkstra
void printMatrix(int n,int **a) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}
int minDistance(int dist[], bool sptSet[],int n)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's shortest path algo
void dijkstra(int n,int graph[n][n], int src)
{
    int dist[n]; 
    bool sptSet[n];
    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;//Distance of src from itself is 0

    // Find shortest path for all vertices
    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, sptSet,n);

        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet,
            // there is an edge from u to v, and total
            // weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }


    printSolution(dist);
}

int** createGraph(int *degrees, int n) {
    int **a,i,j,k,m,d;
    a=(int**)malloc(sizeof(int*)*n);
    for(i=0;i<n;i++){
        a[i]=(int *)malloc(sizeof(int)*n);
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            a[i][j]=0;
        }
    }
    j=-1;
    while(1){
       // if(j>=n) return a;
        for(m=j+1;m<n;m++){
            if(degrees[m]>0){
                d=degrees[m];
                break;
            }
        }
        if(m==n){
            return a;
        }
        j=m;k=0;
        for(m=j+1;m<n && k<=d;m++){
            if(degrees[m]!=0){
                k++;
                a[m][j]=1;
                a[j][m]=1;
                degrees[m]--;
            }
        }
        
    }
        
}

int main()
{   int src;
    int **a;
    int i,j,n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    int graph[n][n];
    srand(time(0));
    int min = 1;
    int max = 20;

    int *degrees;
    degrees=(int *)malloc(sizeof(int)*n);
    printf("Enter the degree sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &degrees[i]);
    }
    a=createGraph(degrees, n);
    
    
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(a[i][j]!=1 ||a[i][j]!=0){
                a[i][j]=(rand() % (max - min + 1)) + min;
                a[j][i]=a[i][j];
            }
        }
    }
    printf("Enter the source from v0 to v%d:",n);
    scanf("%d",&src);
    // Function call
    dijkstra(n,a, src);

    return 0;
}