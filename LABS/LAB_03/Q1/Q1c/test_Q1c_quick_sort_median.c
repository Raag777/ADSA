#include "munit.h"

// Declare function from Q1c program
void quickSortMedian(int arr[], int low, int high);

// Helper to check sorted result
static void assert_sorted(int arr[], int exp[], int n) {
    for (int i = 0; i < n; i++)
        munit_assert_int(arr[i], ==, exp[i]);
}

//  TEST CASES 

static MunitResult test_basic(const MunitParameter params[], void* user_data) {
    int arr[] = {9, 3, 7, 1, 6};
    int exp[] = {1, 3, 6, 7, 9};
    quickSortMedian(arr, 0, 4);
    assert_sorted(arr, exp, 5);
    return MUNIT_OK;
}

static MunitResult test_sorted(const MunitParameter params[], void* user_data) {
    int arr[] = {1, 2, 3, 4};
    int exp[] = {1, 2, 3, 4};
    quickSortMedian(arr, 0, 3);
    assert_sorted(arr, exp, 4);
    return MUNIT_OK;
}

static MunitResult test_reverse(const MunitParameter params[], void* user_data) {
    int arr[] = {9, 7, 5, 3};
    int exp[] = {3, 5, 7, 9};
    quickSortMedian(arr, 0, 3);
    assert_sorted(arr, exp, 4);
    return MUNIT_OK;
}

static MunitResult test_duplicates(const MunitParameter params[], void* user_data) {
    int arr[] = {4, 4, 4, 4};
    int exp[] = {4, 4, 4, 4};
    quickSortMedian(arr, 0, 3);
    assert_sorted(arr, exp, 4);
    return MUNIT_OK;
}

static MunitResult test_single(const MunitParameter params[], void* user_data) {
    int arr[] = {5};
    int exp[] = {5};
    quickSortMedian(arr, 0, 0);
    assert_sorted(arr, exp, 1);
    return MUNIT_OK;
}

static MunitResult test_negative(const MunitParameter params[], void* user_data) {
    int arr[] = {-5, -1, -9, -3};
    int exp[] = {-9, -5, -3, -1};
    quickSortMedian(arr, 0, 3);
    assert_sorted(arr, exp, 4);
    return MUNIT_OK;
}

//  TEST SUITE 

static MunitTest tests[] = {
    {"/basic",      test_basic,      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/sorted",     test_sorted,     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/reverse",    test_reverse,    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/duplicates", test_duplicates, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/single",     test_single,     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/negative",   test_negative,   NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "/quick_sort_median",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

//  MAIN TEST RUNNER 

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
