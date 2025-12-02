#include "munit.h"

// Function declarations from Q1b_sorting.c
void quickSort(int arr[], int low, int high);
void mergeSort(int arr[], int l, int r);
void heapSort(int arr[], int n);

static void check_sorted(int arr[], int expected[], int n) {
    for (int i = 0; i < n; i++)
        munit_assert_int(arr[i], ==, expected[i]);
}

// ---------------------- QUICK SORT ----------------------

static MunitResult test_qs_basic(const MunitParameter params[], void* data) {
    int arr[] = {5, 1, 4, 2};
    int exp[] = {1, 2, 4, 5};
    quickSort(arr, 0, 3);
    check_sorted(arr, exp, 4);
    return MUNIT_OK;
}

static MunitResult test_qs_reverse(const MunitParameter params[], void* data) {
    int arr[] = {9, 7, 5, 3};
    int exp[] = {3, 5, 7, 9};
    quickSort(arr, 0, 3);
    check_sorted(arr, exp, 4);
    return MUNIT_OK;
}

static MunitResult test_qs_duplicate(const MunitParameter params[], void* data) {
    int arr[] = {2, 2, 2, 2};
    int exp[] = {2, 2, 2, 2};
    quickSort(arr, 0, 3);
    check_sorted(arr, exp, 4);
    return MUNIT_OK;
}

// ---------------------- MERGE SORT ----------------------

static MunitResult test_ms_sorted(const MunitParameter params[], void* data) {
    int arr[] = {1, 2, 3, 4};
    int exp[] = {1, 2, 3, 4};
    mergeSort(arr, 0, 3);
    check_sorted(arr, exp, 4);
    return MUNIT_OK;
}

static MunitResult test_ms_negatives(const MunitParameter params[], void* data) {
    int arr[] = {-5, -1, -3, -2};
    int exp[] = {-5, -3, -2, -1};
    mergeSort(arr, 0, 3);
    check_sorted(arr, exp, 4);
    return MUNIT_OK;
}

// ---------------------- HEAP SORT ----------------------

static MunitResult test_heap_basic(const MunitParameter params[], void* data) {
    int arr[] = {4, 10, 3, 5, 1};
    int exp[] = {1, 3, 4, 5, 10};
    heapSort(arr, 5);
    check_sorted(arr, exp, 5);
    return MUNIT_OK;
}

static MunitResult test_heap_reverse(const MunitParameter params[], void* data) {
    int arr[] = {9, 8, 7, 6};
    int exp[] = {6, 7, 8, 9};
    heapSort(arr, 4);
    check_sorted(arr, exp, 4);
    return MUNIT_OK;
}

static MunitResult test_heap_single(const MunitParameter params[], void* data) {
    int arr[] = {5};
    int exp[] = {5};
    heapSort(arr, 1);
    check_sorted(arr, exp, 1);
    return MUNIT_OK;
}

// ---------------------- TEST SUITE ----------------------

static MunitTest tests[] = {
    {"/quick/basic",   test_qs_basic,   NULL, NULL, 0, NULL},
    {"/quick/reverse", test_qs_reverse, NULL, NULL, 0, NULL},
    {"/quick/dup",     test_qs_duplicate, NULL, NULL, 0, NULL},

    {"/merge/sorted",   test_ms_sorted, NULL, NULL, 0, NULL},
    {"/merge/negative", test_ms_negatives, NULL, NULL, 0, NULL},

    {"/heap/basic",  test_heap_basic, NULL, NULL, 0, NULL},
    {"/heap/reverse",  test_heap_reverse, NULL, NULL, 0, NULL},
    {"/heap/single",  test_heap_single, NULL, NULL, 0, NULL},

    {NULL, NULL, NULL, NULL, 0, NULL}
};

static const MunitSuite suite = {
    "/sorting",
    tests,
    NULL,
    1,
    0
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
