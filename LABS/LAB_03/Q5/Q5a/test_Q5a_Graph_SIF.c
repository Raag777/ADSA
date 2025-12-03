#include "munit.h"
#include <string.h>
#include <stdio.h>

#define MAX 20

/* Function used ONLY for testing */
int build_graph_sif_test(char edges[][30], int edge_count,
                         int adj[MAX][MAX], char nodes[MAX][10], int *nodeCount);


/* TEST 1 – Basic graph */
static MunitResult test_basic_graph(const MunitParameter params[], void* data) {

    char edges[][30] = {
        "A B 3",
        "A C 2",
        "B C 1"
    };

    int adj[MAX][MAX] = {0};
    char nodes[MAX][10];
    int nodeCount = 0;

    build_graph_sif_test(edges, 3, adj, nodes, &nodeCount);

    munit_assert_int(nodeCount, ==, 3);

    munit_assert_int(adj[0][1], ==, 3);
    munit_assert_int(adj[0][2], ==, 2);
    munit_assert_int(adj[1][2], ==, 1);

    return MUNIT_OK;
}


/* TEST 2 – Unordered nodes */
static MunitResult test_unordered_nodes(const MunitParameter params[], void* data) {

    char edges[][30] = {
        "C A 5",
        "B D 7",
        "A D 3"
    };

    int adj[MAX][MAX] = {0};
    char nodes[MAX][10];
    int nodeCount = 0;

    build_graph_sif_test(edges, 3, adj, nodes, &nodeCount);

    munit_assert_int(nodeCount, ==, 4);

    return MUNIT_OK;
}


/* TEST 3 – Duplicate edge overwrite */
static MunitResult test_duplicate_edges(const MunitParameter params[], void* data) {

    char edges[][30] = {
        "A B 5",
        "A B 10"
    };

    int adj[MAX][MAX] = {0};
    char nodes[MAX][10];
    int nodeCount = 0;

    build_graph_sif_test(edges, 2, adj, nodes, &nodeCount);

    munit_assert_int(adj[0][1], ==, 10);

    return MUNIT_OK;
}


/* Test Suite */
static MunitTest tests[] = {
    { "/basic_graph", test_basic_graph, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/unordered_nodes", test_unordered_nodes, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/duplicate_edges", test_duplicate_edges, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};


static const MunitSuite suite = {
    "/Graph_SIF_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};


int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
