#include <stdio.h>
#include <stdbool.h>

#define MAX 100   // Max number of vertices on each side


// DFS to find augmenting path

bool bpmDFS(int u, int nRight, int graph[MAX][MAX], bool visited[], int matchR[]) {

    for (int v = 0; v < nRight; v++) {

        // Check if edge exists and v is not visited
        if (graph[u][v] && !visited[v]) {

            visited[v] = true;

            // If v is not matched OR we can find alternate for its match
            if (matchR[v] < 0 || bpmDFS(matchR[v], nRight, graph, visited, matchR)) {
                matchR[v] = u;  // Match u with v
                return true;
            }
        }
    }
    return false;
}


// Maximum Bipartite Matching

int maxBipartiteMatching(int nLeft, int nRight, int graph[MAX][MAX]) {

    int matchR[MAX];

    // Initially all vertices on right are free (-1)
    for (int i = 0; i < nRight; i++)
        matchR[i] = -1;

    int result = 0;

    // Try all vertices on left one by one
    for (int u = 0; u < nLeft; u++) {
        bool visited[MAX] = { false };

        // If u gets matched
        if (bpmDFS(u, nRight, graph, visited, matchR))
            result++;
    }

    // Print matched pairs
    printf("\nMatched Pairs (Left -> Right):\n");
    for (int v = 0; v < nRight; v++) {
        if (matchR[v] != -1)
            printf("  %d -> %d\n", matchR[v], v);
    }

    return result;
}

#ifndef TEST_MODE

int main() {

    int nLeft, nRight;

    printf("Enter number of vertices in Left set: ");
    scanf("%d", &nLeft);

    printf("Enter number of vertices in Right set: ");
    scanf("%d", &nRight);

    int graph[MAX][MAX];

    printf("\nEnter adjacency matrix (%d x %d):\n", nLeft, nRight);
    for (int i = 0; i < nLeft; i++)
        for (int j = 0; j < nRight; j++)
            scanf("%d", &graph[i][j]);

    int maxMatch = maxBipartiteMatching(nLeft, nRight, graph);

    printf("\nMaximum Bipartite Matching = %d\n", maxMatch);

    return 0;
}
#endif
