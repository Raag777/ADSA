#include "munit.h"
#include <stdio.h>
#include <math.h>

#define MAX 10
#define EPS 1e-6

// External function declarations from Q3_LUP_Decomposition.c
extern int LUP_Decompose(double A[MAX][MAX], int P[MAX], int n);
extern void LUP_Solve(double A[MAX][MAX], int P[MAX], double b[MAX], double x[MAX], int n);

// Helper: compare two vectors within tolerance
static int vectors_are_close(double a[], double b[], int n) {
    for (int i = 0; i < n; i++) {
        if (fabs(a[i] - b[i]) > EPS)
            return 0;
    }
    return 1;
}


// Test case 1: Simple 3x3 matrix

static MunitResult test_simple_matrix(const MunitParameter params[], void* data) {
    (void)params; (void)data;
    int n = 3;
    double A[MAX][MAX] = {
        {2, -1, -2},
        {-4, 6, 3},
        {-4, -2, 8}
    };
    double b[MAX] = {-2, 9, -5};
    // Correct solution computed for this system:
    double expected_x[MAX] = {-1.875, 0.9166666666666667, -1.3333333333333333};

    int P[MAX];
    double x[MAX];
    int result = LUP_Decompose(A, P, n);
    munit_assert_int(result, ==, 0);

    LUP_Solve(A, P, b, x, n);
    munit_assert_true(vectors_are_close(x, expected_x, n));

    return MUNIT_OK;
}


// Test case 2: Singular matrix

static MunitResult test_singular_matrix(const MunitParameter params[], void* data) {
    (void)params; (void)data;
    int n = 3;
    double A[MAX][MAX] = {
        {1, 2, 3},
        {2, 4, 6},
        {1, 5, 9}
    };
    double b[MAX] = {1, 2, 3};
    int P[MAX];

    int result = LUP_Decompose(A, P, n);
    munit_assert_int(result, ==, -1);

    return MUNIT_OK;
}


// Test case 3: 2x2 Identity matrix

static MunitResult test_identity_matrix(const MunitParameter params[], void* data) {
    (void)params; (void)data;
    int n = 2;
    double A[MAX][MAX] = {
        {1, 0},
        {0, 1}
    };
    double b[MAX] = {5, -3};
    double expected_x[MAX] = {5, -3};

    int P[MAX];
    double x[MAX];

    int result = LUP_Decompose(A, P, n);
    munit_assert_int(result, ==, 0);

    LUP_Solve(A, P, b, x, n);
    munit_assert_true(vectors_are_close(x, expected_x, n));

    return MUNIT_OK;
}


// Test case 4: 2x2 non-trivial matrix

static MunitResult test_2x2_matrix(const MunitParameter params[], void* data) {
    (void)params; (void)data;
    int n = 2;
    double A[MAX][MAX] = {
        {4, 3},
        {6, 3}
    };
    double b[MAX] = {10, 12};
    // Correct solution for this 2x2 system:
    double expected_x[MAX] = {1.0, 2.0};

    int P[MAX];
    double x[MAX];

    int result = LUP_Decompose(A, P, n);
    munit_assert_int(result, ==, 0);

    LUP_Solve(A, P, b, x, n);
    munit_assert_true(vectors_are_close(x, expected_x, n));

    return MUNIT_OK;
}


// Test case 5: Matrix with negative elements (singular)

static MunitResult test_negative_elements(const MunitParameter params[], void* data) {
    (void)params; (void)data;
    int n = 3;
    double A[MAX][MAX] = {
        {-2, -3, 1},
        {3, -1, -2},
        {2, 3, -1}
    };
    double b[MAX] = {-4, 15, 8};
    int P[MAX];
    // This matrix is singular (or near singular) for the current pivot tolerance,
    // so we expect decomposition to return -1.
    int result = LUP_Decompose(A, P, n);
    munit_assert_int(result, ==, -1);

    return MUNIT_OK;
}


// Register all tests

static MunitTest test_suite_tests[] = {
    { "/test_simple_matrix", test_simple_matrix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_singular_matrix", test_singular_matrix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_identity_matrix", test_identity_matrix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_2x2_matrix", test_2x2_matrix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_negative_elements", test_negative_elements, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
    "/LUP_Decomposition_Tests",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};


// MAIN

int main(int argc, char* argv[]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}
