#include "munit.h"
#include <stdlib.h>
#include <string.h>

#define T 3

typedef struct BTreeNode {
    int keys[2*T - 1];
    struct BTreeNode* child[2*T];
    int n;
    int leaf;
} BTreeNode;

BTreeNode* insert(BTreeNode* root, int k);
BTreeNode* deleteKey(BTreeNode* root, int k);
BTreeNode* search(BTreeNode* root, int k);


// Helper: collect traversal

void traverse_to_array(BTreeNode* root, int arr[], int *idx) {
    if (!root) return;

    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse_to_array(root->child[i], arr, idx);
        arr[(*idx)++] = root->keys[i];
    }
    if (!root->leaf)
        traverse_to_array(root->child[i], arr, idx);
}


// TEST 1 — Insert elements

static MunitResult test_insert(const MunitParameter params[], void* data) {
    BTreeNode* root = NULL;

    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 20);

    int arr[10], idx = 0;
    traverse_to_array(root, arr, &idx);

    int expected[] = {5, 10, 20};

    for (int i = 0; i < 3; i++)
        munit_assert_int(arr[i], ==, expected[i]);

    return MUNIT_OK;
}


// TEST 2 — Search key

static MunitResult test_search(const MunitParameter params[], void* data) {
    BTreeNode* root = NULL;

    int vals[] = {10, 20, 5, 6, 12};
    for (int i = 0; i < 5; i++)
        root = insert(root, vals[i]);

    munit_assert_ptr_not_null(search(root, 6));
    munit_assert_ptr_null(search(root, 99));

    return MUNIT_OK;
}


// TEST 3 — Delete leaf key

static MunitResult test_delete_leaf(const MunitParameter params[], void* data) {
    BTreeNode* root = NULL;

    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 20);

    root = deleteKey(root, 10);

    int arr[10], idx = 0;
    traverse_to_array(root, arr, &idx);

    int expected[] = {5, 20};
    munit_assert_int(arr[0], ==, expected[0]);
    munit_assert_int(arr[1], ==, expected[1]);

    return MUNIT_OK;
}


// TEST 4 — Delete non-existing key

static MunitResult test_delete_not_found(const MunitParameter params[], void* data) {
    BTreeNode* root = NULL;

    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);

    root = deleteKey(root, 100);  // does not exist

    int arr[10], idx = 0;
    traverse_to_array(root, arr, &idx);

    int expected[] = {5, 15, 25};

    for (int i = 0; i < 3; i++)
        munit_assert_int(arr[i], ==, expected[i]);

    return MUNIT_OK;
}


// TEST 5 — Root Split test

static MunitResult test_root_split(const MunitParameter params[], void* data) {
    BTreeNode* root = NULL;

    int vals[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int i = 0; i < 8; i++)
        root = insert(root, vals[i]);

    int arr[20], idx = 0;
    traverse_to_array(root, arr, &idx);

    int expected[] = {5, 6, 7, 10, 12, 17, 20, 30};

    for (int i = 0; i < 8; i++)
        munit_assert_int(arr[i], ==, expected[i]);

    return MUNIT_OK;
}


// Test Suite

static MunitTest tests[] = {
    {"/insert", test_insert, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/search", test_search, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/delete_leaf", test_delete_leaf, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/delete_not_found", test_delete_not_found, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/root_split", test_root_split, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "/BTree_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
