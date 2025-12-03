#include "munit.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Edge struct
typedef struct {
    int u, v, w;
} Edge;

/* Prim MST */

int prim_mst_weight(int n, int graph[n][n]) {
    int select[n], key[n], parentNode[n];

    for (int i = 0; i < n; i++) {
        key[i] = 999999;
        select[i] = 0;
        parentNode[i] = -1;
    }

    key[0] = 0;

    for (int c = 0; c < n - 1; c++) {
        int min = 999999, u = -1;

        for (int v = 0; v < n; v++)
            if (!select[v] && key[v] < min) {
                min = key[v];
                u = v;
            }

        select[u] = 1;

        for (int v = 0; v < n; v++)
            if (graph[u][v] && !select[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parentNode[v] = u;
            }
    }

    int total = 0;
    for (int i = 1; i < n; i++)
        total += graph[i][parentNode[i]];

    return total;
}

/* Kruskal MST Weight */

int parentArr[MAX], rankArr[MAX];

void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parentArr[i] = i;
        rankArr[i] = 0;
    }
}

int findSet(int x) {
    if (x != parentArr[x])
        parentArr[x] = findSet(parentArr[x]);
    return parentArr[x];
}

void unionSet(int x, int y) {
    int px = findSet(x);
    int py = findSet(y);
    if (px != py) {
        if (rankArr[px] < rankArr[py])
            parentArr[px] = py;
        else if (rankArr[py] < rankArr[px])
            parentArr[py] = px;
        else {
            parentArr[py] = px;
            rankArr[px]++;
        }
    }
}

int cmp(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int kruskal_mst_weight(int n, Edge edges[], int e) {
    qsort(edges, e, sizeof(Edge), cmp);
    makeSet(n);

    int total = 0, cnt = 0;

    for (int i = 0; i < e; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (findSet(u) != findSet(v)) {
            total += edges[i].w;
            unionSet(u, v);
            cnt++;
            if (cnt == n - 1) break;
        }
    }

    return total;
}

/* TEST GRAPHS */

// Test Case 1 (from lab) MST = 16
static int graph1[5][5] = {
    {0,2,0,6,0},
    {2,0,3,8,5},
    {0,3,0,0,7},
    {6,8,0,0,9},
    {0,5,7,9,0}
};

static Edge edges1[] = {
    {0,1,2},{0,3,6},{1,2,3},{1,3,8},
    {1,4,5},{2,4,7},{3,4,9}
};

// Test Case 2 (simple square) MST = 6
static int graph2[4][4] = {
    {0,1,4,0},
    {1,0,2,6},
    {4,2,0,3},
    {0,6,3,0}
};

static Edge edges2[] = {
    {0,1,1},{1,2,2},{2,3,3},{0,2,4},{1,3,6}
};

// Test Case 3 (complete graph) MST = 10
static int graph3[4][4] = {
    {0,3,4,5},
    {3,0,6,7},
    {4,6,0,2},
    {5,7,2,0}
};

static Edge edges3[] = {
    {0,1,3},{0,2,4},{0,3,5},{1,2,6},{1,3,7},{2,3,2}
};

// Test Case 4 (line graph) MST = sum = 1+2+3+4 = 10
static int graph4[5][5] = {
    {0,1,0,0,0},
    {1,0,2,0,0},
    {0,2,0,3,0},
    {0,0,3,0,4},
    {0,0,0,4,0}
};

static Edge edges4[] = {
    {0,1,1},{1,2,2},{2,3,3},{3,4,4}
};

/* TEST FUNCTIONS */

static MunitResult test_prim_case1(const MunitParameter params[], void* data) {
    munit_assert_int(prim_mst_weight(5, graph1), ==, 16);
    return MUNIT_OK;
}

static MunitResult test_kruskal_case1(const MunitParameter params[], void* data) {
    Edge t[7]; for(int i=0;i<7;i++) t[i]=edges1[i];
    munit_assert_int(kruskal_mst_weight(5, t, 7), ==, 16);
    return MUNIT_OK;
}

static MunitResult test_prim_case2(const MunitParameter params[], void* data) {
    munit_assert_int(prim_mst_weight(4, graph2), ==, 6);
    return MUNIT_OK;
}

static MunitResult test_kruskal_case2(const MunitParameter params[], void* data) {
    Edge t[5]; for(int i=0;i<5;i++) t[i]=edges2[i];
    munit_assert_int(kruskal_mst_weight(4, t, 5), ==, 6);
    return MUNIT_OK;
}

static MunitResult test_prim_case3(const MunitParameter params[], void* data) {
    munit_assert_int(prim_mst_weight(4, graph3), ==, 9);
    return MUNIT_OK;
}

static MunitResult test_kruskal_case3(const MunitParameter params[], void* data) {
    Edge t[6]; for(int i=0;i<6;i++) t[i]=edges3[i];
    munit_assert_int(kruskal_mst_weight(4, t, 6), ==, 9);
    return MUNIT_OK;
}

static MunitResult test_prim_case4(const MunitParameter params[], void* data) {
    munit_assert_int(prim_mst_weight(5, graph4), ==, 10);
    return MUNIT_OK;
}

static MunitResult test_kruskal_case4(const MunitParameter params[], void* data) {
    Edge t[4]; for(int i=0;i<4;i++) t[i]=edges4[i];
    munit_assert_int(kruskal_mst_weight(5, t, 4), ==, 10);
    return MUNIT_OK;
}

/* SUITE */

static MunitTest tests[] = {
    { "/prim/test_case1", test_prim_case1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/kruskal/test_case1", test_kruskal_case1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/prim/test_case2", test_prim_case2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/kruskal/test_case2", test_kruskal_case2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/prim/test_case3", test_prim_case3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/kruskal/test_case3", test_kruskal_case3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/prim/test_case4", test_prim_case4, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/kruskal/test_case4", test_kruskal_case4, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/Q6_MST_tests", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
