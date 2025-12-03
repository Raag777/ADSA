// Q6_MST.c
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Function prototypes for test file
void prim(int n, int graph[MAX][MAX]);
void kruskal(int n, Edge edges[], int edgeCount);

// Edge structure for Kruskal
typedef struct {
    int u, v, w;
} Edge;

// Disjoint Set for Kruskal
int parent[MAX], rankArr[MAX];

void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rankArr[i] = 0;
    }
}

int findSet(int x) {
    if (x != parent[x])
        parent[x] = findSet(parent[x]);
    return parent[x];
}

void unionSet(int x, int y) {
    int px = findSet(x);
    int py = findSet(y);

    if (px != py) {
        if (rankArr[px] < rankArr[py])
            parent[px] = py;
        else if (rankArr[py] < rankArr[px])
            parent[py] = px;
        else {
            parent[py] = px;
            rankArr[px]++;
        }
    }
}

// Prim's Algorithm
void prim(int n, int graph[MAX][MAX]) {
    int select[MAX];
    int key[MAX];
    int parentNode[MAX];

    for (int i = 0; i < n; i++) {
        key[i] = 999999;
        select[i] = 0;
        parentNode[i] = -1;
    }

    key[0] = 0;

    for (int i = 0; i < n - 1; i++) {
        int min = 999999, u = -1;

        for (int v = 0; v < n; v++)
            if (!select[v] && key[v] < min) {
                min = key[v];
                u = v;
            }

        select[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !select[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parentNode[v] = u;
            }
        }
    }

    printf("\nMST using Prim's Algorithm:\n");
    int total = 0;

    for (int i = 1; i < n; i++) {
        printf("%d -- %d   (weight = %d)\n", parentNode[i], i, graph[i][parentNode[i]]);
        total += graph[i][parentNode[i]];
    }

    printf("Total Weight = %d\n", total);
}

// Kruskal’s Algorithm
int cmp(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

void kruskal(int n, Edge edges[], int edgeCount) {
    qsort(edges, edgeCount, sizeof(Edge), cmp);
    makeSet(n);

    printf("\nMST using Kruskal's Algorithm:\n");
    int total = 0, selected = 0;

    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (findSet(u) != findSet(v)) {
            printf("%d -- %d   (weight = %d)\n", u, v, edges[i].w);
            total += edges[i].w;
            unionSet(u, v);
            selected++;
            if (selected == n - 1) break;
        }
    }

    printf("Total Weight = %d\n", total);
}

#ifndef TEST_MODE
int main() {
    int n, e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    Edge edges[MAX];
    int graph[MAX][MAX] = {0};

    printf("\nEnter edges in SIF format:  u v w  (0-indexed)\n");

    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        graph[edges[i].u][edges[i].v] = edges[i].w;
        graph[edges[i].v][edges[i].u] = edges[i].w;
    }

    prim(n, graph);
    kruskal(n, edges, e);

    return 0;
}
#endif