#include "munit.h"
#include <math.h>
#include <stdio.h>

#define N 3
#define EPS 1e-6

/* Declarations from Q2_LUP_Solver.c */
int LUP_Decompose(double A[N][N], int P[N]);
void LUP_Solve(double A[N][N], int P[N], double b[N], double x[N]);

/* Helpers */
static void copy_mat(double dst[N][N], double src[N][N]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            dst[i][j] = src[i][j];
}

static void mat_vec_mul(double A[N][N], double x[N], double out[N]) {
    for (int i = 0; i < N; ++i) {
        out[i] = 0.0;
        for (int j = 0; j < N; ++j)
            out[i] += A[i][j] * x[j];
    }
}

static int vecs_close(double a[N], double b[N]) {
    for (int i = 0; i < N; ++i)
        if (fabs(a[i] - b[i]) > EPS) return 0;
    return 1;
}

/*  TEST 1: regular system (Ax=b)  */
static MunitResult test_regular_system(const MunitParameter params[], void* user_data) {
    (void)params; (void)user_data;

    double A_orig[N][N] = {
        {2, 3, 1},
        {4, 7, -1},
        {-2, 4, 5}
    };
    double b[N] = {1, 6, -3};

    double A[N][N];
    copy_mat(A, A_orig);

    double x[N];
    int P[N];

    munit_assert_int(LUP_Decompose(A, P), ==, 0);
    LUP_Solve(A, P, b, x);

    double Ax[N];
    mat_vec_mul(A_orig, x, Ax);
    munit_assert_true(vecs_close(Ax, b));

    return MUNIT_OK;
}

/*  TEST 2: identity  */
static MunitResult test_identity_matrix(const MunitParameter params[], void* user_data) {
    (void)params; (void)user_data;

    double A_orig[N][N] = {
        {1,0,0},
        {0,1,0},
        {0,0,1}
    };
    double b[N] = {5, -2, 3};

    double A[N][N];
    copy_mat(A, A_orig);

    double x[N];
    int P[N];

    munit_assert_int(LUP_Decompose(A, P), ==, 0);
    LUP_Solve(A, P, b, x);

    double Ax[N];
    mat_vec_mul(A_orig, x, Ax);
    munit_assert_true(vecs_close(Ax, b));

    return MUNIT_OK;
}

/*  TEST 3: singular matrix  */
static MunitResult test_singular_matrix(const MunitParameter params[], void* user_data) {
    (void)params; (void)user_data;

    double A_orig[N][N] = {
        {1,2,3},
        {2,4,6},
        {1,1,1}
    };

    double A[N][N];
    copy_mat(A, A_orig);

    int P[N];
    munit_assert_int(LUP_Decompose(A, P), ==, -1);
    return MUNIT_OK;
}

/*  TEST 4: negative values  */
static MunitResult test_negative_values(const MunitParameter params[], void* user_data) {
    (void)params; (void)user_data;

    double A_orig[N][N] = {
        {-2, 1, 0},
        { 3,-1, 2},
        { 1, 2,-1}
    };
    double b[N] = {-1, 4, 2};

    double A[N][N];
    copy_mat(A, A_orig);

    double x[N];
    int P[N];

    munit_assert_int(LUP_Decompose(A, P), ==, 0);
    LUP_Solve(A, P, b, x);

    double Ax[N];
    mat_vec_mul(A_orig, x, Ax);
    munit_assert_true(vecs_close(Ax, b));

    return MUNIT_OK;
}

/*  TEST 5: random invertible  */
static MunitResult test_random_invertible(const MunitParameter params[], void* user_data) {
    (void)params; (void)user_data;

    double A_orig[N][N] = {
        {3, 2, -1},
        {2,-2,  4},
        {-1,0.5,-1}
    };
    double b[N] = {1, -2, 0};

    double A[N][N];
    copy_mat(A, A_orig);

    double x[N];
    int P[N];

    munit_assert_int(LUP_Decompose(A, P), ==, 0);
    LUP_Solve(A, P, b, x);

    double Ax[N];
    mat_vec_mul(A_orig, x, Ax);
    munit_assert_true(vecs_close(Ax, b));

    return MUNIT_OK;
}

/*  Test registration  */
static MunitTest tests[] = {
    { "/regular_system", test_regular_system, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/identity_matrix", test_identity_matrix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/singular_matrix", test_singular_matrix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/negative_values", test_negative_values, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/random_invertible", test_random_invertible, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/LUP_Solver_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
