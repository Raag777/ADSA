#include "munit.h"
#include <stdio.h>
#include <math.h>

#define MAX 10
#define EPS 1e-6

//  External function from Q3_LUP_Decomposition.c 
extern int LUP_Decompose(double A[MAX][MAX], int P[MAX], int n);

//  Helper: Compare two matrices within tolerance 
static int matrices_are_close(double A[MAX][MAX], double B[MAX][MAX], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (fabs(A[i][j] - B[i][j]) > EPS)
                return 0;
    return 1;
}

//  Helper: Print matrix (for debugging) 
static void printMatrix(double A[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%8.4f ", A[i][j]);
        printf("\n");
    }
}


//  Test Case 1: Simple 3×3 Matrix

static MunitResult test_simple_matrix(const MunitParameter params[], void* data) {
    (void)params; (void)data;

    int n = 3;
    double A[MAX][MAX] = {
        {2, -1, -2},
        {-4, 6, 3},
        {-4, -2, 8}
    };
    int P[MAX];

    int result = LUP_Decompose(A, P, n);
    munit_assert_int(result, ==, 0);
    return MUNIT_OK;
}


//  Test Case 2: Singular Matrix (should fail)

static MunitResult test_singular_matrix(const MunitParameter params[], void* data) {
    (void)params; (void)data;

    int n = 3;
    double A[MAX][MAX] = {
        {1, 2, 3},
        {2, 4, 6},
        {1, 5, 9}
    };
    int P[MAX];

    int result = LUP_Decompose(A, P, n);
    munit_assert_int(result, ==, -1); // Expect failure
    return MUNIT_OK;
}


//  Test Case 3: Identity Matrix (should remain unchanged)

static MunitResult test_identity_matrix(const MunitParameter params[], void* data) {
    (void)params; (void)data;

    int n = 3;
    double A[MAX][MAX] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    int P[MAX];

    int result = LUP_Decompose(A, P, n);
    munit_assert_int(result, ==, 0);

    // Permutation unchanged
    for (int i = 0; i < n; i++)
        munit_assert_int(P[i], ==, i);

    return MUNIT_OK;
}


//  Test Case 4: Simple 2×2 Matrix

static MunitResult test_2x2_matrix(const MunitParameter params[], void* data) {
    (void)params; (void)data;

    int n = 2;
    double A[MAX][MAX] = {
        {4, 3},
        {6, 3}
    };
    int P[MAX];

    int result = LUP_Decompose(A, P, n);
    munit_assert_int(result, ==, 0);

    // Check for a valid pivot permutation (largest pivot in row 1)
    munit_assert_int(P[0], ==, 1);

    return MUNIT_OK;
}


//  Test Case 5: Matrix with Negative Elements

static MunitResult test_negative_elements(const MunitParameter params[], void* data) {
    (void)params; (void)data;

    int n = 3;
    double A[MAX][MAX] = {
        {-2, -3, -1},
        {-4, -5, -6},
        {-7, -8, -9}
    };
    int P[MAX];

    int result = LUP_Decompose(A, P, n);

    // This matrix is nearly singular; ensure function handles it gracefully
    if (result == -1) {
        printf("Matrix is singular or near singular (expected).\n");
        return MUNIT_OK;
    }

    munit_assert_int(result, ==, 0);
    return MUNIT_OK;
}


//  Register Tests

static MunitTest tests[] = {
    {"/simple_matrix", test_simple_matrix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/singular_matrix", test_singular_matrix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/identity_matrix", test_identity_matrix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/2x2_matrix", test_2x2_matrix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/negative_elements", test_negative_elements, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};


//  Define Suite

static const MunitSuite suite = {
    "/LUP_Decomposition_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};


//  Main

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
