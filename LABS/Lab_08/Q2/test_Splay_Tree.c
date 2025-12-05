#include "munit.h"
#include <stdio.h>
#include <stdlib.h>
#include "Splay_Tree.h"

static int expected_vals[10];
static int idx;

/* inorder collector */
static void inorderCollect(Node* root) {
    if (!root) return;
    inorderCollect(root->left);
    munit_assert_int(root->key, ==, expected_vals[idx]);
    idx++;
    inorderCollect(root->right);
}

/* Helper: Create sample tree */
static Node* createSampleTree() {
    Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    return root;
}

/* TEST INSERT */
static MunitResult test_insert(const MunitParameter params[], void* data) {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);

    munit_assert_not_null(root);
    munit_assert_int(root->key, ==, 5);

    return MUNIT_OK;
}

/* TEST SEARCH */
static MunitResult test_search(const MunitParameter params[], void* data) {
    Node* root = createSampleTree();

    root = search(root, 40);

    munit_assert_not_null(root);
    munit_assert_int(root->key, ==, 40);

    return MUNIT_OK;
}

/* TEST DELETE */
static MunitResult test_delete_key(const MunitParameter params[], void* data) {
    Node* root = createSampleTree();

    root = deleteKey(root, 30);

    root = search(root, 30);
    munit_assert_int(root->key, !=, 30);

    return MUNIT_OK;
}

/* TEST SPLAY PROPERTY */
static MunitResult test_splay_property(const MunitParameter params[], void* data) {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 20);

    root = search(root, 20);
    munit_assert_int(root->key, ==, 20);

    return MUNIT_OK;
}

/* TEST TRAVERSAL */
static MunitResult test_inorder(const MunitParameter params[], void* data) {
    Node* root = createSampleTree();

    int values[] = {20, 30, 40, 50, 70};
    for (int i = 0; i < 5; i++) expected_vals[i] = values[i];
    idx = 0;

    inorderCollect(root);
    munit_assert_int(idx, ==, 5);

    return MUNIT_OK;
}

/* TEST TABLE */
static MunitTest tests[] = {
    { "/insert", test_insert, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/search", test_search, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/delete", test_delete_key, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/splay_property", test_splay_property, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/inorder", test_inorder, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* SUITE DEFINITION */
static const MunitSuite suite = {
    "/splay_tree_tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
