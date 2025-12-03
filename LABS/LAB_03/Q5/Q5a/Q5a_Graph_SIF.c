#include <stdio.h>
#include <string.h>

#define MAX 20

/* FUNCTION 1 — For MUnit Tests (NO scanf) */
int build_graph_sif_test(char edges[][30], int edge_count,
                         int adj[MAX][MAX], char nodes[MAX][10], int *nodeCount) {

    *nodeCount = 0;

    for (int k = 0; k < edge_count; k++) {
        char a[10], b[10];
        int w;

        sscanf(edges[k], "%s %s %d", a, b, &w);

        int u = -1, v = -1;

        // Find/add node a
        for (int i = 0; i < *nodeCount; i++)
            if (strcmp(nodes[i], a) == 0) u = i;
        if (u == -1) {
            strcpy(nodes[*nodeCount], a);
            u = (*nodeCount)++;
        }

        // Find/add node b
        for (int i = 0; i < *nodeCount; i++)
            if (strcmp(nodes[i], b) == 0) v = i;
        if (v == -1) {
            strcpy(nodes[*nodeCount], b);
            v = (*nodeCount)++;
        }

        adj[u][v] = w;
        adj[v][u] = w;
    }

    return *nodeCount;
}


/* FUNCTION 2 — For Normal User Input (scanf mode) */

#ifndef TEST_MODE
int build_graph_sif(int adj[MAX][MAX], char nodes[MAX][10]) {

    int nodeCount = 0;
    char a[10], b[10];
    int w;

    while (1) {
        scanf("%s", a);

        if (strcmp(a, "END") == 0)
            break;

        scanf("%s %d", b, &w);

        int u = -1, v = -1;

        // Find/add node a
        for (int i = 0; i < nodeCount; i++)
            if (strcmp(nodes[i], a) == 0) u = i;
        if (u == -1) {
            strcpy(nodes[nodeCount], a);
            u = nodeCount++;
        }

        // Find/add node b
        for (int i = 0; i < nodeCount; i++)
            if (strcmp(nodes[i], b) == 0) v = i;
        if (v == -1) {
            strcpy(nodes[nodeCount], b);
            v = nodeCount++;
        }

        adj[u][v] = w;
        adj[v][u] = w;
    }

    return nodeCount;
}
#endif


#ifndef TEST_MODE

int main() {
    int adj[MAX][MAX] = {0};
    char nodes[MAX][10];
    int nodeCount;

    printf("Enter edges in SIF format (Node1 Node2 Weight). Enter END to stop.\n");

    nodeCount = build_graph_sif(adj, nodes);

    // Print adjacency matrix
    printf("\nAdjacency Matrix:\n   ");
    for (int i = 0; i < nodeCount; i++)
        printf("%s ", nodes[i]);
    printf("\n");

    for (int i = 0; i < nodeCount; i++) {
        printf("%s ", nodes[i]);
        for (int j = 0; j < nodeCount; j++)
            printf("%d ", adj[i][j]);
        printf("\n");
    }

    return 0;
}
#endif
