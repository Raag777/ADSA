#include "munit.h"
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

Node* insert(Node* node, int key);
Node* deleteNode(Node* root, int key);
void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);


void inorder_to_array(Node* root, int arr[], int* idx) {
    if (!root) return;
    inorder_to_array(root->left, arr, idx);
    arr[(*idx)++] = root->key;
    inorder_to_array(root->right, arr, idx);
}

void preorder_to_array(Node* root, int arr[], int* idx) {
    if (!root) return;
    arr[(*idx)++] = root->key;
    preorder_to_array(root->left, arr, idx);
    preorder_to_array(root->right, arr, idx);
}

void postorder_to_array(Node* root, int arr[], int* idx) {
    if (!root) return;
    postorder_to_array(root->left, arr, idx);
    postorder_to_array(root->right, arr, idx);
    arr[(*idx)++] = root->key;
}

/* TEST 1: INSERTION & AVL SELF-BALANCING */

static MunitResult test_avl_insert(const MunitParameter params[], void* data) {
    Node* root = NULL;
    int arr[20], idx = 0;

    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 10);   // This SHOULD trigger Right-Rotation

    inorder_to_array(root, arr, &idx);

    int expected[] = {10, 20, 30};
    for (int i = 0; i < 3; i++)
        munit_assert_int(arr[i], ==, expected[i]);

    return MUNIT_OK;
}

/* TEST 2: DELETE LEAF NODE */

static MunitResult test_avl_delete_leaf(const MunitParameter params[], void* data) {
    Node* root = NULL;
    int arr[20], idx = 0;

    root = insert(root, 40);
    root = insert(root, 20);
    root = insert(root, 60);
    root = insert(root, 10);

    root = deleteNode(root, 10);  // delete leaf

    inorder_to_array(root, arr, &idx);

    int expected[] = {20, 40, 60};
    for (int i = 0; i < 3; i++)
        munit_assert_int(arr[i], ==, expected[i]);

    return MUNIT_OK;
}

/* TEST 3: DELETE NODE WITH ONE CHILD */

static MunitResult test_avl_delete_one_child(const MunitParameter params[], void* data) {
    Node* root = NULL;
    int arr[20], idx = 0;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 40);

    root = deleteNode(root, 30); // one child

    inorder_to_array(root, arr, &idx);

    int expected[] = {40, 50};
    for (int i = 0; i < 2; i++)
        munit_assert_int(arr[i], ==, expected[i]);

    return MUNIT_OK;
}

/* TEST 4: DELETE NODE WITH TWO CHILDREN */

static MunitResult test_avl_delete_two_children(const MunitParameter params[], void* data) {
    Node* root = NULL;
    int arr[20], idx = 0;

    int nums[] = {50, 30, 20, 40, 70, 60, 80};
    for (int i = 0; i < 7; i++)
        root = insert(root, nums[i]);

    root = deleteNode(root, 50);  // two children (root node)

    inorder_to_array(root, arr, &idx);

    int expected[] = {20, 30, 40, 60, 70, 80};
    for (int i = 0; i < 6; i++)
        munit_assert_int(arr[i], ==, expected[i]);

    return MUNIT_OK;
}

/* TEST 5: TRAVERSALS (INORDER, PREORDER, POSTORDER) */

static MunitResult test_avl_traversals(const MunitParameter params[], void* data) {
    Node* root = NULL;

    int list[] = {10, 20, 5, 4, 15};
    for (int i = 0; i < 5; i++)
        root = insert(root, list[i]);

    int in[20], pre[20], post[20];
    int i1 = 0, i2 = 0, i3 = 0;

    inorder_to_array(root, in, &i1);
    preorder_to_array(root, pre, &i2);
    postorder_to_array(root, post, &i3);

    int exp_in[]  = {4, 5, 10, 15, 20};
    int exp_pre[] = {10, 5, 4, 20, 15};
    int exp_post[]= {4, 5, 15, 20, 10};

    for (int i = 0; i < 5; i++) {
        munit_assert_int(in[i], ==, exp_in[i]);
        munit_assert_int(pre[i], ==, exp_pre[i]);
        munit_assert_int(post[i], ==, exp_post[i]);
    }

    return MUNIT_OK;
}

/* TEST SUITE */

static MunitTest tests[] = {
    {"/insert",               test_avl_insert,               NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/delete_leaf",          test_avl_delete_leaf,          NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/delete_one_child",     test_avl_delete_one_child,     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/delete_two_children",  test_avl_delete_two_children,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/traversals",           test_avl_traversals,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "/AVL_Tree_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
