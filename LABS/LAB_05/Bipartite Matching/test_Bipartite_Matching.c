#include "munit.h"
#include <stdio.h>
#include <stdbool.h>

#define MAX 100


// Use extern so we can compile separately

extern int maxBipartiteMatching(int nLeft, int nRight, int graph[MAX][MAX]);


// TEST 1: Basic Matching

static MunitResult test_basic_matching(const MunitParameter params[], void* data) {

    int nLeft = 4, nRight = 4;

    int graph[MAX][MAX] = {
        {0,1,1,0},
        {1,0,0,1},
        {0,0,1,0},
        {1,1,0,0}
    };

    int result = maxBipartiteMatching(nLeft, nRight, graph);
    munit_assert_int(result, ==, 4);

    return MUNIT_OK;
}


// TEST 2: No edges

static MunitResult test_no_edges(const MunitParameter params[], void* data) {

    int nLeft = 3, nRight = 3;

    int graph[MAX][MAX] = {
        {0,0,0},
        {0,0,0},
        {0,0,0}
    };

    int result = maxBipartiteMatching(nLeft, nRight, graph);
    munit_assert_int(result, ==, 0);

    return MUNIT_OK;
}


// TEST 3: Perfect Matching

static MunitResult test_perfect_matching(const MunitParameter params[], void* data) {

    int nLeft = 3, nRight = 3;

    int graph[MAX][MAX] = {
        {1,0,0},
        {0,1,0},
        {0,0,1}
    };

    int result = maxBipartiteMatching(nLeft, nRight, graph);
    munit_assert_int(result, ==, 3);

    return MUNIT_OK;
}


// TEST 4: Partial Matching

static MunitResult test_partial_matching(const MunitParameter params[], void* data) {

    int nLeft = 4, nRight = 4;

    int graph[MAX][MAX] = {
        {0,1,0,0},
        {0,0,0,1},
        {0,0,0,0},
        {1,0,0,0}
    };

    int result = maxBipartiteMatching(nLeft, nRight, graph);
    munit_assert_int(result, ==, 3);

    return MUNIT_OK;
}


// TEST 5: Rectangular (non-square) graph

static MunitResult test_rectangular_graph(const MunitParameter params[], void* data) {

    int nLeft = 3, nRight = 5;

    int graph[MAX][MAX] = {
        {1,0,1,0,0},
        {0,1,0,0,1},
        {1,0,0,1,0}
    };

    int result = maxBipartiteMatching(nLeft, nRight, graph);
    munit_assert_int(result, ==, 3);

    return MUNIT_OK;
}


// MUnit Test Suite Table

static MunitTest tests[] = {
    { "/basic-matching", test_basic_matching, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/no-edges", test_no_edges, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/perfect-matching", test_perfect_matching, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/partial-matching", test_partial_matching, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/rectangular-graph", test_rectangular_graph, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/bipartite-matching-tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};


// MUnit Runner

int main(int argc, char *argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
