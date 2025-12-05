#include "munit.h"
#include <stdio.h>
#include <stdlib.h>
#include "Fibonacci_Heap.h"



// Helper: create a heap with sample nodes

static FibHeap* createSampleHeap() {
    FibHeap *H = createFibHeap();
    fibHeapInsert(H, createNode(10));
    fibHeapInsert(H, createNode(3));
    fibHeapInsert(H, createNode(20));
    fibHeapInsert(H, createNode(6));
    return H;
}


// Test: Insert + Min correctness

static MunitResult test_insert(const MunitParameter params[], void* data) {
    FibHeap *H = createFibHeap();

    FibNode *n1 = createNode(30);
    FibNode *n2 = createNode(10);
    FibNode *n3 = createNode(50);

    fibHeapInsert(H, n1);
    fibHeapInsert(H, n2);
    fibHeapInsert(H, n3);

    munit_assert_not_null(H->min);
    munit_assert_int(H->min->key, ==, 10);

    freeHeap(H);
    return MUNIT_OK;
}


// Test: Extract Min

static MunitResult test_extract_min(const MunitParameter params[], void* data) {
    FibHeap *H = createSampleHeap();

    FibNode *min = fibHeapExtractMin(H);

    munit_assert_not_null(min);
    munit_assert_int(min->key, ==, 3);

    free(min);
    freeHeap(H);
    return MUNIT_OK;
}


// Test: Decrease Key

static MunitResult test_decrease_key(const MunitParameter params[], void* data) {
    FibHeap *H = createSampleHeap();

    FibNode *node = H->min->right;  // arbitrary sample (key=20 or 6)
    fibHeapDecreaseKey(H, node, 1);

    munit_assert_int(H->min->key, ==, 1);

    freeHeap(H);
    return MUNIT_OK;
}


// Test: Delete Node

static MunitResult test_delete_node(const MunitParameter params[], void* data) {
    FibHeap *H = createSampleHeap();

    FibNode *node = findNodeById(H, 3);
    fibHeapDelete(H, node);

    FibNode *search = findNodeById(H, 3);
    munit_assert_null(search);

    freeHeap(H);
    return MUNIT_OK;
}


// Test: Find Node

static MunitResult test_find_node(const MunitParameter params[], void* data) {
    FibHeap *H = createSampleHeap();

    // Get actual node pointer (do NOT assume ID)
    FibNode *target = H->min->right;   // pick a valid existing node

    int id = target->id;

    FibNode *found = findNodeById(H, id);
    munit_assert_not_null(found);

    fibHeapDelete(H, found);

    found = findNodeById(H, id);
    munit_assert_null(found);

    freeHeap(H);
    return MUNIT_OK;
}


// Test table

static MunitTest tests[] = {
    { "/insert", test_insert, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/extract_min", test_extract_min, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/decrease_key", test_decrease_key, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/delete", test_delete_node, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/find_node", test_find_node, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};


// Suite definition

static const MunitSuite suite = {
    "/fibonacci_heap_tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};


int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
