#include "munit.h"
#include <string.h>

#define MAX 20
#define INF 99999

void dijkstra(int n, int cost[MAX][MAX], int src, int dist[MAX]);

/* TEST 1 — Basic graph */
static MunitResult test_basic(const MunitParameter params[], void* data) {

    int n = 4;
    int cost[MAX][MAX] = {
        {0, 1, 4, 0},
        {1, 0, 2, 6},
        {4, 2, 0, 3},
        {0, 6, 3, 0}
    };

    int dist[MAX];

    dijkstra(n, cost, 0, dist);

    munit_assert_int(dist[0], ==, 0);
    munit_assert_int(dist[1], ==, 1);
    munit_assert_int(dist[2], ==, 3);
    munit_assert_int(dist[3], ==, 6);

    return MUNIT_OK;
}

/* TEST 2 — Unreachable nodes */
static MunitResult test_unreachable(const MunitParameter params[], void* data) {

    int n = 4;
    int cost[MAX][MAX] = {
        {0, 5, 0, 0},
        {5, 0, 0, 0},
        {0, 0, 0, 2},
        {0, 0, 2, 0}
    };

    int dist[MAX];

    dijkstra(n, cost, 0, dist);

    munit_assert_int(dist[0], ==, 0);
    munit_assert_int(dist[1], ==, 5);
    munit_assert_int(dist[2], ==, INF);
    munit_assert_int(dist[3], ==, INF);

    return MUNIT_OK;
}

/* TEST 3 — Zero weight edge */
static MunitResult test_zero_edge(const MunitParameter params[], void* data) {

    int n = 3;
    int cost[MAX][MAX] = {
        {0, 0, 2},
        {0, 0, 1},
        {2, 1, 0}
    };

    int dist[MAX];

    dijkstra(n, cost, 0, dist);

    munit_assert_int(dist[0], ==, 0);
    munit_assert_int(dist[1], ==, 3);
    munit_assert_int(dist[2], ==, 2);

    return MUNIT_OK;
}

/* TEST SUITE */
static MunitTest tests[] = {
    {"/basic",         test_basic,        NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/unreachable",   test_unreachable,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/zero_edge",     test_zero_edge,    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "/Dijkstra_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
