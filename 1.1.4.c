#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



void kruskalMST(int **cost, int V) {

    int parent[V];
    // Initialize each vertex as its own parent
    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }

    int edge_count = 0;
    int total_min_cost = 0;

    // A tree with V vertices has exactly V-1 edges
    while (edge_count < V - 1) {
        int min = 9999; // 9999 represents infinity as per instructions
        int u = -1, v = -1;

        // Find the minimum weight edge that doesn't form a cycle
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // Find root of component containing i
                int root_i = i;
                while (parent[root_i] != root_i) {
                    root_i = parent[root_i];
                }

                // Find root of component containing j
                int root_j = j;
                while (parent[root_j] != root_j) {
                    root_j = parent[root_j];
                }

                // If they belong to different components and edge weight is smaller
                if (root_i != root_j && cost[i][j] < min) {
                    min = cost[i][j];
                    u = i;
                    v = j;
                }
            }
        }

        // If a valid edge is found, include it in the MST
        if (u != -1 && v != -1) {
            // Union the components
            int root_u = u;
            while (parent[root_u] != root_u) {
                root_u = parent[root_u];
            }
            int root_v = v;
            while (parent[root_v] != root_v) {
                root_v = parent[root_v];
            }
            parent[root_u] = root_v;

            // Print the selected edge
            printf("Edge %d:(%d, %d) cost:%d\n", edge_count, u, v, min);
            total_min_cost += min;
            edge_count++;
        } else {
            // Graph is disconnected and no more edges can be formed
            break;
        }
    }

    // Print the final minimum cost
    printf("Minimum cost= %d\n", total_min_cost);
}

	


int main() {
    int V;
    printf("No of vertices: ");
    scanf("%d", &V);

    int **cost = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
        cost[i] = (int *)malloc(V * sizeof(int));

    printf("Adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &cost[i][j]);

    kruskalMST(cost, V);

    for (int i = 0; i < V; i++)
        free(cost[i]);
    free(cost);

    return 0;
}
