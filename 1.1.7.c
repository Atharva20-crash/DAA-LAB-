 #include <stdio.h>
#include <stdlib.h>

#define INF 1000000000 // Representation for infinity

// Structure to represent a directed weighted edge
struct Edge {
    int u, v, w;
};

// Function to print the path from source to a given vertex
void printPath(int parent[], int vertex) {
    int path[1005];
    int count = 0;
    int curr = vertex;
    
    // Backtrack from the destination vertex to the source using parent array
    while (curr != -1) {
        path[count++] = curr;
        curr = parent[curr];
    }
    
    // Print the path in forward direction
    for (int i = count - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) {
            printf("->");
        }
    }
}

int main() {
    int V, E;
    if (scanf("%d", &V) != 1) return 0;
    if (scanf("%d", &E) != 1) return 0;

    struct Edge* edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    int source;
    if (scanf("%d", &source) != 1) return 0;

    int* dist = (int*)malloc((V + 1) * sizeof(int));
    int* parent = (int*)malloc((V + 1) * sizeof(int));

    // Step 1: Initialize distances and parents
    for (int i = 1; i <= V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[source] = 0;

    // Step 2: Relax all edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    int has_negative_cycle = 0;
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            has_negative_cycle = 1;
            break;
        }
    }

    // Step 4: Print results matching the format constraints
    if (has_negative_cycle) {
        printf("Negative cycle detected\n");
    } else {
        for (int i = 1; i <= V; i++) {
            if (i == source) continue; // Skip printing the source vertex
            
            if (dist[i] == INF) {
                printf("%d INF None\n", i);
            } else {
                printf("%d %d ", i, dist[i]);
                printPath(parent, i);
                printf("\n");
            }
        }
    }

    // Clean up allocated memory
    free(edges);
    free(dist);
    free(parent);
    return 0;
}
