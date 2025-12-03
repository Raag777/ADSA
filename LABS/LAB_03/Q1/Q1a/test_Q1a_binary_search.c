#include <stdio.h>
#include "munit.h"

// Declare functions from Q1a_binary_search.c
int binarySearchIterative(int arr[], int n, int key);
int binarySearchRecursive(int arr[], int low, int high, int key);

//  ITERATIVE TESTS 

static MunitResult test_iter_basic(const MunitParameter params[], void* data) {
    int arr[] = {2, 4, 6, 8, 10};
    munit_assert_int(binarySearchIterative(arr, 5, 6), ==, 2);
    return MUNIT_OK;
}

static MunitResult test_iter_first(const MunitParameter params[], void* data) {
    int arr[] = {3, 5, 7, 9};
    munit_assert_int(binarySearchIterative(arr, 4, 3), ==, 0);
    return MUNIT_OK;
}

static MunitResult test_iter_last(const MunitParameter params[], void* data) {
    int arr[] = {3, 5, 7, 9};
    munit_assert_int(binarySearchIterative(arr, 4, 9), ==, 3);
    return MUNIT_OK;
}

static MunitResult test_iter_not_found(const MunitParameter params[], void* data) {
    int arr[] = {1, 2, 3, 4};
    munit_assert_int(binarySearchIterative(arr, 4, 10), ==, -1);
    return MUNIT_OK;
}

static MunitResult test_iter_single(const MunitParameter params[], void* data) {
    int arr[] = {7};
    munit_assert_int(binarySearchIterative(arr, 1, 7), ==, 0);
    return MUNIT_OK;
}

static MunitResult test_iter_duplicate(const MunitParameter params[], void* data) {
    int arr[] = {2, 4, 4, 4, 6};
    int result = binarySearchIterative(arr, 5, 4);
    munit_assert_true(result == 1 || result == 2 || result == 3);
    return MUNIT_OK;
}

//  RECURSIVE TESTS 

static MunitResult test_rec_basic(const MunitParameter params[], void* data) {
    int arr[] = {2, 4, 6, 8};
    munit_assert_int(binarySearchRecursive(arr, 0, 3, 8), ==, 3);
    return MUNIT_OK;
}

static MunitResult test_rec_not_found(const MunitParameter params[], void* data) {
    int arr[] = {1, 3, 5};
    munit_assert_int(binarySearchRecursive(arr, 0, 2, 8), ==, -1);
    return MUNIT_OK;
}

static MunitResult test_rec_large(const MunitParameter params[], void* data) {
    int arr[100];
    for (int i = 0; i < 100; i++) arr[i] = i * 2;
    munit_assert_int(binarySearchRecursive(arr, 0, 99, 98), ==, 49);
    return MUNIT_OK;
}

//  TEST SUITE 

static MunitTest tests[] = {
    // Iterative
    {"/iter/basic",      test_iter_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/iter/first",      test_iter_first, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/iter/last",       test_iter_last, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/iter/not_found",  test_iter_not_found, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/iter/single",     test_iter_single, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/iter/duplicates", test_iter_duplicate, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

    // Recursive
    {"/rec/basic",       test_rec_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/rec/not_found",   test_rec_not_found, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/rec/large",       test_rec_large, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "/binary_search",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
