#include "munit.h"
#include <math.h>
#include <stdio.h>

#define N 3
#define EPS 1e-6

// Declare functions from Q2_LUP_Solver.c
int LUP_Decompose(double A[N][N], int P[N]);
void LUP_Solve(double A[N][N], int P[N], double b[N], double x[N]);

// Helper: copy matrix
static void copy_mat(double dest[N][N], const double src[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dest[i][j] = src[i][j];
}

// Helper: matrix * vector
static void mat_vec_mul(const double A[N][N], const double x[N], double result[N]) {
    for (int i = 0; i < N; i++) {
        result[i] = 0.0;
        for (int j = 0; j < N; j++)
            result[i] += A[i][j] * x[j];
    }
}

// Helper: compare two vectors
static int vecs_close(const double a[N], const double b[N]) {
    for (int i = 0; i < N; i++)
        if (fabs(a[i] - b[i]) > EPS)
            return 0;
    return 1;
}

/*  TEST CASES  */

//  Test 1: Regular system
static MunitResult test_regular_system(const MunitParameter params[], void* data) {
    double A[N][N] = {
        {2, 3, 1},
        {4, 7, -1},
        {-2, 4, 5}
    };
    double b[N] = {1, 6, -3};
    double A_copy[N][N], x[N], check_b[N];
    int P[N];

    copy_mat(A_copy, A);
    munit_assert_int(LUP_Decompose(A_copy, P), ==, 0);
    LUP_Solve(A_copy, P, b, x);
    mat_vec_mul(A, x, check_b);
    munit_assert_true(vecs_close(check_b, b));
    return MUNIT_OK;
}

//  Test 2: Identity matrix
static MunitResult test_identity_matrix(const MunitParameter params[], void* data) {
    double A[N][N] = {
        {1,0,0},
        {0,1,0},
        {0,0,1}
    };
    double b[N] = {5, -2, 3};
    double A_copy[N][N], x[N], check_b[N];
    int P[N];

    copy_mat(A_copy, A);
    munit_assert_int(LUP_Decompose(A_copy, P), ==, 0);
    LUP_Solve(A_copy, P, b, x);
    mat_vec_mul(A, x, check_b);
    munit_assert_true(vecs_close(check_b, b));
    return MUNIT_OK;
}

//  Test 3: Singular matrix
static MunitResult test_singular_matrix(const MunitParameter params[], void* data) {
    double A[N][N] = {
        {2, 4, 1},
        {4, 8, 2},
        {1, 2, 0.5}
    };
    int P[N];
    double A_copy[N][N];
    copy_mat(A_copy, A);
    munit_assert_int(LUP_Decompose(A_copy, P), ==, -1);
    return MUNIT_OK;
}

//  Test 4: Negative values
static MunitResult test_negative_values(const MunitParameter params[], void* data) {
    double A[N][N] = {
        {-3, 2, -5},
        {4, -1, 2},
        {2, 3, -1}
    };
    double b[N] = {-3, 9, 7};
    double A_copy[N][N], x[N], check_b[N];
    int P[N];

    copy_mat(A_copy, A);
    munit_assert_int(LUP_Decompose(A_copy, P), ==, 0);
    LUP_Solve(A_copy, P, b, x);
    mat_vec_mul(A, x, check_b);
    munit_assert_true(vecs_close(check_b, b));
    return MUNIT_OK;
}

//  Test 5: Random invertible
static MunitResult test_random_invertible(const MunitParameter params[], void* data) {
    double A[N][N] = {
        {1, 2, 3},
        {0, 1, 4},
        {5, 6, 0}
    };
    double b[N] = {14, 13, 23};
    double A_copy[N][N], x[N], check_b[N];
    int P[N];

    copy_mat(A_copy, A);
    munit_assert_int(LUP_Decompose(A_copy, P), ==, 0);
    LUP_Solve(A_copy, P, b, x);
    mat_vec_mul(A, x, check_b);
    munit_assert_true(vecs_close(check_b, b));
    return MUNIT_OK;
}

/*  TEST SUITE  */

static MunitTest tests[] = {
    { "/regular_system", test_regular_system, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/identity_matrix", test_identity_matrix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/singular_matrix", test_singular_matrix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/negative_values", test_negative_values, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/random_invertible", test_random_invertible, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/LUP_Solver_Tests", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
