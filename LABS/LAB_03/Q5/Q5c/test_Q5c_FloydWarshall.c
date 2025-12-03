#include "munit.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX 20
#define INF 99999

void floydWarshall(int n, int dist[MAX][MAX]);


/* TEST 1 — Simple 3-node graph */

static MunitResult test_basic_fw(const MunitParameter params[], void* data) {

    int n = 3;
    int dist[MAX][MAX] = {
        {0, 4, INF},
        {4, 0, 2},
        {INF, 2, 0}
    };

    floydWarshall(n, dist);

    munit_assert_int(dist[0][2], ==, 6);  // 0 → 1 → 2
    munit_assert_int(dist[2][0], ==, 6);

    return MUNIT_OK;
}


/* TEST 2 — Graph with unreachable node */

static MunitResult test_with_inf(const MunitParameter params[], void* data) {

    int n = 3;
    int dist[MAX][MAX] = {
        {0, 1, 0},
        {1, 0, INF},
        {0, INF, 0}
    };

    floydWarshall(n, dist);

    // Node 0 and 1 connected, node 2 isolated
    munit_assert_int(dist[0][1], ==, 1);
    munit_assert_int(dist[2][0], ==, INF);

    return MUNIT_OK;
}


/* TEST 3 — 4-node weighted graph sample */

static MunitResult test_4node_graph(const MunitParameter params[], void* data) {

    int n = 4;
    int dist[MAX][MAX] = {
        {0,   5,  INF, 10},
        {INF, 0,   3,  INF},
        {INF, INF, 0,   1},
        {INF, INF, INF, 0}
    };

    floydWarshall(n, dist);

    munit_assert_int(dist[0][2], ==, 8);   // 0→1→2
    munit_assert_int(dist[0][3], ==, 9);   // 0→1→2→3

    return MUNIT_OK;
}


/* TEST SUITE CONFIGURATION */

static MunitTest tests[] = {
    {"/basic_fw",       test_basic_fw,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/with_inf",       test_with_inf,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/4node_graph",    test_4node_graph,    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "/FloydWarshall_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};


int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
