#include <stdio.h>
#define INF 99999
#define MAX 20

/* FUNCTION — Dijkstra algorithm (For MUnit Tests) */
void dijkstra(int n, int cost[MAX][MAX], int src, int dist[MAX]) {

    int visited[MAX] = {0};

    // Initialize distances
    for (int i = 0; i < n; i++) {
        dist[i] = (cost[src][i] == 0 && i != src) ? INF : cost[src][i];
    }

    dist[src] = 0;

    // Dijkstra Algorithm
    for (int count = 0; count < n - 1; count++) {

        int min = INF, u = -1;

        for (int i = 0; i < n; i++)
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }

        if (u == -1) break; // safety check
        visited[u] = 1;

        for (int v = 0; v < n; v++)
            if (!visited[v] && cost[u][v] &&
                dist[u] + cost[u][v] < dist[v]) {

                dist[v] = dist[u] + cost[u][v];
            }
    }
}

#ifndef TEST_MODE

int main() {

    int n, src;
    int cost[MAX][MAX], dist[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &cost[i][j]);

    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &src);

    dijkstra(n, cost, src, dist);

    printf("\nShortest distances from source %d:\n", src);
    for (int i = 0; i < n; i++)
        printf("To %d = %d\n", i, dist[i]);

    return 0;
}
#endif
