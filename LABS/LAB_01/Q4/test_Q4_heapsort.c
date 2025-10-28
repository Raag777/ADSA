#include "munit.h"
#include "Q4_heapsort.c"

// Helper function to compare two arrays
static void assert_array_equal(int* arr, int* expected, int n) {
    for (int i = 0; i < n; i++) {
        munit_assert_int(arr[i], ==, expected[i]);
    }
}

//  Random unsorted input
static MunitResult
test_heap_sort_basic(const MunitParameter params[], void* data) {
    int arr[] = {4, 10, 3, 5, 1};
    int expected[] = {1, 3, 4, 5, 10};
    int n = 5;

    heapSort(arr, n);
    assert_array_equal(arr, expected, n);
    return MUNIT_OK;
}

//  Already sorted input
static MunitResult
test_heap_sort_sorted_input(const MunitParameter params[], void* data) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    int n = 5;

    heapSort(arr, n);
    assert_array_equal(arr, expected, n);
    return MUNIT_OK;
}

//  Reverse sorted input
static MunitResult
test_heap_sort_reverse_input(const MunitParameter params[], void* data) {
    int arr[] = {9, 7, 5, 3, 1};
    int expected[] = {1, 3, 5, 7, 9};
    int n = 5;

    heapSort(arr, n);
    assert_array_equal(arr, expected, n);
    return MUNIT_OK;
}

//  Single-element array
static MunitResult
test_heap_sort_single_element(const MunitParameter params[], void* data) {
    int arr[] = {42};
    int expected[] = {42};
    int n = 1;

    heapSort(arr, n);
    assert_array_equal(arr, expected, n);
    return MUNIT_OK;
}

//  Array with duplicate elements
static MunitResult
test_heap_sort_duplicates(const MunitParameter params[], void* data) {
    int arr[] = {5, 1, 3, 3, 2, 5};
    int expected[] = {1, 2, 3, 3, 5, 5};
    int n = 6;

    heapSort(arr, n);
    assert_array_equal(arr, expected, n);
    return MUNIT_OK;
}

// Define test suite
static MunitTest tests[] = {
    {"/heap_sort_basic", test_heap_sort_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/heap_sort_sorted_input", test_heap_sort_sorted_input, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/heap_sort_reverse_input", test_heap_sort_reverse_input, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/heap_sort_single_element", test_heap_sort_single_element, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/heap_sort_duplicates", test_heap_sort_duplicates, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "/heap_sort_tests", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
