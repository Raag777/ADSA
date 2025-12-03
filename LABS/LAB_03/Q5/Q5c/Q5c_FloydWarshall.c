#include <stdio.h>
#define INF 99999
#define MAX 20

void floydWarshall(int n, int dist[MAX][MAX]) {

    // Convert 0 to INF except diagonal
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && dist[i][j] == 0)
                dist[i][j] = INF;

    // Floyd–Warshall algorithm
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

#ifndef TEST_MODE

int main() {
    int n;
    int dist[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge, except diagonal):\n");

    // Input graph
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
            if (i != j && dist[i][j] == 0)
                dist[i][j] = INF;
        }

    // Apply Floyd–Warshall
    floydWarshall(n, dist);

    // Output
    printf("\nAll-Pairs Shortest Path Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        printf("\n");
    }

    return 0;
}
#endif
