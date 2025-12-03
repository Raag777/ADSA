#include "munit.h"
#include <stdio.h>

#define MAX 10
#define EPS 1e-6

int inverseMatrix(int n, double A[MAX][MAX], double I[MAX][MAX]);

/* Compare two floating point numbers */
static int float_equal(double a, double b) {
    return (a - b < EPS && b - a < EPS);
}

/* Helper: multiply matrices A (n×n) and B (n×n) -> out (n×n) */
static void matmul(int n, double A[MAX][MAX], double B[MAX][MAX], double out[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            out[i][j] = 0.0;
            for (int k = 0; k < n; k++)
                out[i][j] += A[i][k] * B[k][j];
        }
}

/* Helper: check if product is identity */
static int is_identity(int n, double M[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            double expected = (i == j) ? 1.0 : 0.0;
            if (!float_equal(M[i][j], expected)) return 0;
        }
    return 1;
}

/* TEST 1 — Check inverse of 2x2 matrix */
static MunitResult test_inverse_2x2(const MunitParameter params[], void* data) {

    int n = 2;
    double A[MAX][MAX] = {
        {4, 7},
        {2, 6}
    };
    double I[MAX][MAX];

    double expected[MAX][MAX] = {
        {0.6, -0.7},
        {-0.2, 0.4}
    };

    // Copy matrix because function may modify input
    double B[MAX][MAX] = {0};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];

    int status = inverseMatrix(n, B, I);
    munit_assert_int(status, ==, 1);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            munit_assert_true(float_equal(I[i][j], expected[i][j]));

    return MUNIT_OK;
}

/* TEST 2 — Singular matrix (det = 0) */
static MunitResult test_singular(const MunitParameter params[], void* data) {

    int n = 2;
    double A[MAX][MAX] = {
        {2, 4},
        {1, 2}
    };
    double I[MAX][MAX];

    int status = inverseMatrix(n, A, I);
    munit_assert_int(status, ==, 0);

    return MUNIT_OK;
}

/* TEST 3 — 3x3 inverse check (small matrix) */
static MunitResult test_inverse_3x3(const MunitParameter params[], void* data) {

    int n = 3;
    double A[MAX][MAX] = {
        {1, 2, 3},
        {0, 1, 4},
        {5, 6, 0}
    };
    double I[MAX][MAX];

    double B[MAX][MAX];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];

    int status = inverseMatrix(n, B, I);
    munit_assert_int(status, ==, 1);

    /* Instead of checking exact values (which may be scaled),
       validate by verifying A * I == Identity (within EPS) */
    double prod[MAX][MAX];
    matmul(n, A, I, prod);
    munit_assert_true(is_identity(n, prod));

    return MUNIT_OK;
}

/* TEST 4 — Identity matrix (inverse should be identity) */
static MunitResult test_identity(const MunitParameter params[], void* data) {
    int n = 4;
    double A[MAX][MAX] = {0};
    double I[MAX][MAX];
    for (int i = 0; i < n; i++) A[i][i] = 1.0;

    double B[MAX][MAX];
    for (int i=0;i<n;i++) for (int j=0;j<n;j++) B[i][j] = A[i][j];

    int status = inverseMatrix(n, B, I);
    munit_assert_int(status, ==, 1);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            munit_assert_true(float_equal(I[i][j], A[i][j]));

    return MUNIT_OK;
}

/* TEST 5 — Diagonal matrix (inverse is reciprocal on diagonal) */
static MunitResult test_diagonal(const MunitParameter params[], void* data) {
    int n = 3;
    double A[MAX][MAX] = {
        {2, 0, 0},
        {0, 3, 0},
        {0, 0, 4}
    };
    double expected[MAX][MAX] = {
        {0.5, 0.0, 0.0},
        {0.0, 1.0/3.0, 0.0},
        {0.0, 0.0, 0.25}
    };

    double B[MAX][MAX];
    double I[MAX][MAX];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];

    int status = inverseMatrix(n, B, I);
    munit_assert_int(status, ==, 1);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            munit_assert_true(float_equal(I[i][j], expected[i][j]));

    return MUNIT_OK;
}

/* TEST 6 — 4x4 matrix: validate by A * inverse = I */
static MunitResult test_4x4_product_identity(const MunitParameter params[], void* data) {
    int n = 4;
    double A[MAX][MAX] = {
        {4, 7, 2, 3},
        {0, 5, 0, 1},
        {1, 0, 3, 2},
        {2, 1, 4, 6}
    };

    double B[MAX][MAX], I[MAX][MAX], prod[MAX][MAX];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];

    int status = inverseMatrix(n, B, I);
    munit_assert_int(status, ==, 1);

    matmul(n, A, I, prod);
    munit_assert_true(is_identity(n, prod));

    return MUNIT_OK;
}

/* TEST 7 — Floating point entries */
static MunitResult test_floating_point(const MunitParameter params[], void* data) {
    int n = 3;
    double A[MAX][MAX] = {
        {1.5, 2.0, 0.5},
        {0.0, 1.25, 0.75},
        {2.5, 0.5, 1.0}
    };

    double B[MAX][MAX], I[MAX][MAX], prod[MAX][MAX];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];

    int status = inverseMatrix(n, B, I);
    munit_assert_int(status, ==, 1);

    matmul(n, A, I, prod);
    munit_assert_true(is_identity(n, prod));

    return MUNIT_OK;
}

/* TEST 8 — Near-singular but invertible (small det) */
static MunitResult test_near_singular(const MunitParameter params[], void* data) {
    int n = 3;
    /* Matrix with small determinant but invertible */
    double A[MAX][MAX] = {
        {1e-6 + 1.0, 1.0, 1.0},
        {1.0, 1.0 + 1e-6, 1.0},
        {1.0, 1.0, 1.0 + 1e-6}
    };

    double B[MAX][MAX], I[MAX][MAX], prod[MAX][MAX];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];

    int status = inverseMatrix(n, B, I);

    /* Depending on implementation, tiny numerical instability can occur.
       We accept either success (1) or failure (0) — but if success, verify product. */
    if (status == 1) {
        matmul(n, A, I, prod);
        munit_assert_true(is_identity(n, prod));
    } else {
        /* if function reports singular, that's acceptable for very ill-conditioned matrix */
        munit_assert_int(status, ==, 0);
    }

    return MUNIT_OK;
}

/* TEST SUITE */
static MunitTest tests[] = {
    { "/inverse_2x2",           test_inverse_2x2,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/singular",              test_singular,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/inverse_3x3",           test_inverse_3x3,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/identity",              test_identity,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/diagonal",              test_diagonal,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/4x4_product_identity",  test_4x4_product_identity,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/floating_point",        test_floating_point,        NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/near_singular",         test_near_singular,         NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/InverseMatrix_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
