#include "munit.h"
#include <stdlib.h>

// Import functions from Q2_BST.c
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* insert(Node* root, int data);
Node* deleteNode(Node* root, int key);
void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);

// Helper to convert traversal into array output
void inorder_to_array(Node* root, int arr[], int* idx) {
    if (root == NULL) return;
    inorder_to_array(root->left, arr, idx);
    arr[(*idx)++] = root->data;
    inorder_to_array(root->right, arr, idx);
}

void preorder_to_array(Node* root, int arr[], int* idx) {
    if (root == NULL) return;
    arr[(*idx)++] = root->data;
    preorder_to_array(root->left, arr, idx);
    preorder_to_array(root->right, arr, idx);
}

void postorder_to_array(Node* root, int arr[], int* idx) {
    if (root == NULL) return;
    postorder_to_array(root->left, arr, idx);
    postorder_to_array(root->right, arr, idx);
    arr[(*idx)++] = root->data;
}

//  TEST 1: Insert Nodes 
static MunitResult test_insert(const MunitParameter params[], void* data) {
    Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);

    int arr[10], idx = 0;
    inorder_to_array(root, arr, &idx);

    int expected[] = {20, 30, 40, 50, 70};
    for (int i = 0; i < 5; i++)
        munit_assert_int(arr[i], ==, expected[i]);

    return MUNIT_OK;
}

//  TEST 2: Delete Leaf Node 
static MunitResult test_delete_leaf(const MunitParameter params[], void* data) {
    Node* root = NULL;
    int nodes[] = {50, 30, 70, 20};
    for (int i = 0; i < 4; i++)
        root = insert(root, nodes[i]);

    root = deleteNode(root, 20);  // deleting a leaf

    int arr[10], idx = 0;
    inorder_to_array(root, arr, &idx);

    int expected[] = {30, 50, 70};
    for (int i = 0; i < 3; i++)
        munit_assert_int(arr[i], ==, expected[i]);

    return MUNIT_OK;
}

//  TEST 3: Delete Node with One Child 
static MunitResult test_delete_one_child(const MunitParameter params[], void* data) {
    Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 40);

    root = deleteNode(root, 30); // node with one child

    int arr[10], idx = 0;
    inorder_to_array(root, arr, &idx);

    int expected[] = {40, 50};
    for (int i = 0; i < 2; i++)
        munit_assert_int(arr[i], ==, expected[i]);

    return MUNIT_OK;
}

//  TEST 4: Delete Node with Two Children 
static MunitResult test_delete_two_children(const MunitParameter params[], void* data) {
    Node* root = NULL;
    int nodes[] = {50, 30, 70, 20, 40};
    for (int i = 0; i < 5; i++)
        root = insert(root, nodes[i]);

    root = deleteNode(root, 30); // has two children

    int arr[10], idx = 0;
    inorder_to_array(root, arr, &idx);

    int expected[] = {20, 40, 50, 70};
    for (int i = 0; i < 4; i++)
        munit_assert_int(arr[i], ==, expected[i]);

    return MUNIT_OK;
}

//  TEST 5: Traversals 
static MunitResult test_traversals(const MunitParameter params[], void* data) {
    Node* root = NULL;
    int nodes[] = {50, 30, 70, 20, 40};
    for (int i = 0; i < 5; i++)
        root = insert(root, nodes[i]);

    int in[10], pre[10], post[10];
    int i1 = 0, i2 = 0, i3 = 0;

    inorder_to_array(root, in, &i1);
    preorder_to_array(root, pre, &i2);
    postorder_to_array(root, post, &i3);

    int exp_in[]  = {20, 30, 40, 50, 70};
    int exp_pre[] = {50, 30, 20, 40, 70};
    int exp_post[]= {20, 40, 30, 70, 50};

    for (int i = 0; i < 5; i++) {
        munit_assert_int(in[i], ==, exp_in[i]);
        munit_assert_int(pre[i], ==, exp_pre[i]);
        munit_assert_int(post[i], ==, exp_post[i]);
    }

    return MUNIT_OK;
}

//  SUITE 
static MunitTest tests[] = {
    {"/insert",               test_insert,               NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/delete_leaf",          test_delete_leaf,          NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/delete_one_child",     test_delete_one_child,     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/delete_two_children",  test_delete_two_children,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/traversals",           test_traversals,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "/BST_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
