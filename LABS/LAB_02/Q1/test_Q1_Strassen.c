#define TEST_MODE   // prevents main() from Q1_Strassen.c being compiled
#include "munit.h"
#include "Q1_Strassen.c"


// Test Case 1: 2x2 matrices

static MunitResult test_2x2(const MunitParameter params[], void* data) {
    int n = 2;
    int A[MAX][MAX] = {{1, 2}, {3, 4}};
    int B[MAX][MAX] = {{5, 6}, {7, 8}};
    int C[MAX][MAX] = {0};
    int expected[MAX][MAX] = {{19, 22}, {43, 50}};
    strassen(A, B, C, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            munit_assert_int(C[i][j], ==, expected[i][j]);
    return MUNIT_OK;
}


// Test Case 2: 3x3 matrices (with padding)

static MunitResult test_3x3(const MunitParameter params[], void* data) {
    int n = 3;
    int A[MAX][MAX] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int B[MAX][MAX] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };
    int C[MAX][MAX] = {0};
    int expected[MAX][MAX] = {
        {30, 24, 18},
        {84, 69, 54},
        {138, 114, 90}
    };
    strassen(A, B, C, 4);  // next power of 2 = 4
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            munit_assert_int(C[i][j], ==, expected[i][j]);
    return MUNIT_OK;
}


// Test Case 3: Single element

static MunitResult test_single(const MunitParameter params[], void* data) {
    int n = 1;
    int A[MAX][MAX] = {{5}};
    int B[MAX][MAX] = {{6}};
    int C[MAX][MAX] = {0};
    strassen(A, B, C, n);
    munit_assert_int(C[0][0], ==, 30);
    return MUNIT_OK;
}


// Test Case 4: Zero matrix

static MunitResult test_zero(const MunitParameter params[], void* data) {
    int n = 2;
    int A[MAX][MAX] = {{0, 0}, {0, 0}};
    int B[MAX][MAX] = {{1, 2}, {3, 4}};
    int C[MAX][MAX] = {0};
    strassen(A, B, C, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            munit_assert_int(C[i][j], ==, 0);
    return MUNIT_OK;
}


// Test Case 5: Identity matrix multiplication

static MunitResult test_identity(const MunitParameter params[], void* data) {
    int n = 2;
    int A[MAX][MAX] = {{1, 2}, {3, 4}};
    int I[MAX][MAX] = {{1, 0}, {0, 1}};
    int C[MAX][MAX] = {0};
    strassen(A, I, C, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            munit_assert_int(C[i][j], ==, A[i][j]);
    return MUNIT_OK;
}


// MUnit Test Suite

static MunitTest tests[] = {
    {"/2x2", test_2x2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/3x3", test_3x3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/single", test_single, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/zero", test_zero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/identity", test_identity, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "/strassen-tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
