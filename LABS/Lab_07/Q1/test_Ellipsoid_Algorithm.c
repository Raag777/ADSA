#include "munit.h"
#include <math.h>
#include <stdio.h>

#define MAXN 20
#define MAXM 50
#define EPS 1e-6

// Forward declaration
int ellipsoidLP(int n, int m, double A[][MAXN], double b[], double x_out[]);

// Helper: Check feasibility
static int check_feasible(int n, int m, double A[][MAXN], double b[], double x[]) {
    for (int i = 0; i < m; i++) {
        double dot = 0;
        for (int j = 0; j < n; j++)
            dot += A[i][j] * x[j];
        if (dot > b[i] + EPS)
            return 0;
    }
    return 1;
}

/* TEST 1 */
static MunitResult test_basic_feasible(const MunitParameter params[], void* data) {

    int n = 2, m = 3;

    double A[MAXM][MAXN] = {
        {1, 1},
        {1, -1},
        {-1, 1}
    };
    double b[MAXM] = {4, 2, 2};
    double x[2];

    int res = ellipsoidLP(n, m, A, b, x);
    munit_assert_int(res, ==, 1);
    munit_assert_true(check_feasible(n, m, A, b, x));

    return MUNIT_OK;
}

/* TEST 2 */
static MunitResult test_infeasible(const MunitParameter params[], void* data) {

    int n = 1, m = 2;

    double A[MAXM][MAXN] = {
        {1},     // x <= 1
        {-1}     // x >= 5
    };
    double b[MAXM] = {1, -5};

    double x[1];

    int res = ellipsoidLP(n, m, A, b, x);
    munit_assert_int(res, ==, 0);

    return MUNIT_OK;
}

/* TEST 3 */
static MunitResult test_3d_feasible(const MunitParameter params[], void* data) {

    int n = 3, m = 4;

    double A[MAXM][MAXN] = {
        {1, 1, 1},
        {-1, 0, 0},
        {0, -1, 0},
        {0, 0, -1}
    };
    double b[MAXM] = {10, 0, 0, 0};

    double x[3];

    int res = ellipsoidLP(n, m, A, b, x);
    munit_assert_int(res, ==, 1);
    munit_assert_true(check_feasible(n, m, A, b, x));

    return MUNIT_OK;
}

/* TEST 4 */
static MunitResult test_redundant(const MunitParameter params[], void* data) {

    int n = 2, m = 4;

    double A[MAXM][MAXN] = {
        {1, 0},
        {0, 1},
        {1, 1},
        {2, 2} // redundant
    };
    double b[MAXM] = {5, 5, 10, 20};

    double x[2];

    int res = ellipsoidLP(n, m, A, b, x);
    munit_assert_int(res, ==, 1);

    return MUNIT_OK;
}

/* TEST 5 */
static MunitResult test_tight(const MunitParameter params[], void* data) {

    int n = 2, m = 2;

    double A[MAXM][MAXN] = {
        {1, 0},    // x <= 2
        {-1, 0}    // x >= 2
    };
    double b[MAXM] = {2, -2};

    double x[2];

    int res = ellipsoidLP(n, m, A, b, x);
    munit_assert_int(res, ==, 1);

    return MUNIT_OK;
}

/* TEST 6 */
static MunitResult test_zero_constraints(const MunitParameter params[], void* data) {

    int n = 3, m = 0;
    double A[MAXM][MAXN] = {0};
    double b[MAXM] = {0};
    double x[3];

    int res = ellipsoidLP(n, m, A, b, x);
    munit_assert_int(res, ==, 1);

    return MUNIT_OK;
}

/*  TEST SUITE  */
static MunitTest tests[] = {
    {"/basic-feasible", test_basic_feasible, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/infeasible", test_infeasible, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/3d-feasible", test_3d_feasible, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/redundant", test_redundant, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/tight-boundary", test_tight, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/zero-constraints", test_zero_constraints, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "/ellipsoid-tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
