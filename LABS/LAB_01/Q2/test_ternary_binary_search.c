#include "munit.h"
#include <stdio.h>
#include <stdlib.h>


int binaryComparisons = 0;
int ternaryComparisons = 0;

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        binaryComparisons++;
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

int ternarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        ternaryComparisons++;
        if (arr[mid1] == key) return mid1;

        ternaryComparisons++;
        if (arr[mid2] == key) return mid2;

        if (key < arr[mid1]) {
            high = mid1 - 1;
        } else if (key > arr[mid2]) {
            low = mid2 + 1;
        } else {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }
    return -1;
}

// ---------- MUNIT TEST CASES ----------

// Test 1: Key present in array
static MunitResult test_key_present(const MunitParameter params[], void* data) {
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int n = 7;
    int key = 7;

    int bIndex = binarySearch(arr, n, key);
    int tIndex = ternarySearch(arr, 0, n - 1, key);

    munit_assert_int(bIndex, ==, 3);
    munit_assert_int(tIndex, ==, 3);

    return MUNIT_OK;
}

// Test 2: Key not present in array
static MunitResult test_key_not_present(const MunitParameter params[], void* data) {
    int arr[] = {1, 2, 4, 6, 8, 10};
    int n = 6;
    int key = 5;

    int bIndex = binarySearch(arr, n, key);
    int tIndex = ternarySearch(arr, 0, n - 1, key);

    munit_assert_int(bIndex, ==, -1);
    munit_assert_int(tIndex, ==, -1);

    return MUNIT_OK;
}

// Test 3: Edge case - first element
static MunitResult test_first_element(const MunitParameter params[], void* data) {
    int arr[] = {2, 4, 6, 8, 10};
    int n = 5;
    int key = 2;

    int bIndex = binarySearch(arr, n, key);
    int tIndex = ternarySearch(arr, 0, n - 1, key);

    munit_assert_int(bIndex, ==, 0);
    munit_assert_int(tIndex, ==, 0);

    return MUNIT_OK;
}

// Test 4: Edge case - last element
static MunitResult test_last_element(const MunitParameter params[], void* data) {
    int arr[] = {2, 4, 6, 8, 10};
    int n = 5;
    int key = 10;

    int bIndex = binarySearch(arr, n, key);
    int tIndex = ternarySearch(arr, 0, n - 1, key);

    munit_assert_int(bIndex, ==, 4);
    munit_assert_int(tIndex, ==, 4);

    return MUNIT_OK;
}

// Test 5: Comparison count check
static MunitResult test_comparison_counts(const MunitParameter params[], void* data) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = 10;
    int key = 8;

    binaryComparisons = 0;
    ternaryComparisons = 0;

    binarySearch(arr, n, key);
    ternarySearch(arr, 0, n - 1, key);

    munit_assert_int(binaryComparisons, >, 0);
    munit_assert_int(ternaryComparisons, >, 0);

    return MUNIT_OK;
}

// ---------- TEST SUITE ----------

static MunitTest tests[] = {
    {"/key_present", test_key_present, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/key_not_present", test_key_not_present, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/first_element", test_first_element, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/last_element", test_last_element, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/comparison_counts", test_comparison_counts, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "/ternary_binary_search_tests", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
