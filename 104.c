#include <stdio.h>
#include <stdlib.h>
#include<limits.h>
#define MAX 100

// Structure to represent an edge
struct Edge {
    int u, v, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Function prototypes
int find(struct Subset subsets[], int i);
void Union(struct Subset subsets[], int x, int y);
void Kruskal(struct Edge edges[], int V, int E, struct Edge mst[]);
void findFundamentalCircuit(struct Edge mst[], struct Edge edges[], int V, int E);
void findFundamentalCutset(struct Edge mst[], struct Edge edges[], int V, int E);

// Function to find set of an element i (uses path compression technique)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// A function that does union of two sets of x and y (uses union by rank)
void Union(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Kruskal's algorithm to find the MST
void Kruskal(struct Edge edges[], int V, int E, struct Edge mst[]) {
    struct Subset *subsets = (struct Subset *) malloc(V * sizeof(struct Subset));
    int i,v;
    for ( v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int mstIndex = 0;
    for ( i = 0; i < E; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;

        int setU = find(subsets, u);
        int setV = find(subsets, v);

        if (setU != setV) {
            mst[mstIndex++] = edges[i];
            Union(subsets, setU, setV);
        }
    }
}

// Function to find the fundamental circuit
void findFundamentalCircuit(struct Edge mst[], struct Edge edges[], int V, int E) {
    printf("\nFundamental Circuits:\n");
    int i,j;
    for ( i = 0; i < E; ++i) {
        int isInMST = 0;
        for ( j = 0; j < V - 1; ++j) {
            if ((edges[i].u == mst[j].u && edges[i].v == mst[j].v) ||
                (edges[i].u == mst[j].v && edges[i].v == mst[j].u)) {
                isInMST = 1;
                break;
            }
        }

        if (!isInMST) {
            printf("Cycle with edge (%d, %d)\n", edges[i].u, edges[i].v);
        }
    }
}

// Function to find the fundamental cutset
void findFundamentalCutset(struct Edge mst[], struct Edge edges[], int V, int E) {
    printf("\nFundamental Cutsets:\n");
    int i,v,j;
    for ( i = 0; i < V - 1; i++) {  // Loop through each edge in the MST
        int removedU = mst[i].u;
        int removedV = mst[i].v;

        // Step 1: Remove the edge from the MST, which creates two components.
        struct Subset *subsets = (struct Subset *) malloc(V * sizeof(struct Subset));
        for ( v = 0; v < V; v++) {
            subsets[v].parent = v;
            subsets[v].rank = 0;
        }

        // Add all MST edges except the removed edge
        for ( j = 0; j < V - 1; j++) {
            if (i != j) {
                Union(subsets, mst[j].u, mst[j].v);
            }
        }

        // Step 2: Find edges that connect the two disjoint sets
        printf("Cutset with removed edge (%d, %d):\n", removedU, removedV);
        for ( j = 0; j < E; j++) {
            if (find(subsets, edges[j].u) != find(subsets, edges[j].v)) {
                printf("Edge (%d, %d)\n", edges[j].u, edges[j].v);
            }
        }

        free(subsets);
    }
}

int main() {
    int V, E;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    // Initialize adjacency matrix
    int adjMatrix[MAX][MAX];
    int i,j;
    printf("Enter the adjacency matrix:\n");
    for ( i = 0; i < V; ++i) {
        for ( j = 0; j < V; ++j) {
            scanf("%d", &adjMatrix[i][j]);
            // If there's no edge between vertex i and j and it's not a self-loop,
            // we can consider it as no weight or infinity.
            if (i != j && adjMatrix[i][j] == 0) { 
                adjMatrix[i][j] = INT_MAX; // Use INT_MAX to indicate no connection
            }
        }
    }

    // Extracting edges from adjacency matrix
    struct Edge edges[MAX * MAX];
    E = 0;

    for ( i = 0; i < V; ++i) {
        for ( j = i + 1; j < V; ++j) { // Avoid duplicate entries and self-loops
            if (adjMatrix[i][j] != INT_MAX) { 
                edges[E++] = (struct Edge){i, j, adjMatrix[i][j]};
            }
        }
    }

    // Sort edges by weight using simple bubble sort
    for ( i = 0; i < E - 1; i++) {
        for ( j = i + 1; j < E; j++) {
            if (edges[i].weight > edges[j].weight) {
                struct Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }

    struct Edge mst[MAX];
    
	// Call Kruskal's algorithm to find MST
	Kruskal(edges,V,E,mst);

	printf("Minimum Spanning Tree:\n");
	for(i=0;i<V-1;++i){
		printf("(%d, %d)\n",mst[i].u,mst[i].v);
	}

	findFundamentalCircuit(mst,edges,V,E);
	findFundamentalCutset(mst,edges,V,E);

	return 0;
}