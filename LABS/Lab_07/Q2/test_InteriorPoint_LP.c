#include "munit.h"
#include <math.h>
#include <stdio.h>

#define MAXN 50
#define MAXM 50
#define TOL 1e-6

/* Forward declaration from the main code */
int interior_point_lp(int n, int m,
                      double A[MAXM][MAXN],
                      double b[MAXM],
                      double c[MAXN],
                      double x[MAXN]);

/* Helper: Check Ax = b residual */
static int check_primal_res(int n, int m, double A[MAXM][MAXN],
                            double b[MAXM], double x[MAXN]) {
    for (int i = 0; i < m; i++) {
        double s = 0.0;
        for (int j = 0; j < n; j++)
            s += A[i][j] * x[j];
        if (fabs(s - b[i]) > TOL)
            return 0;
    }
    return 1;
}

/* Helper: Check positivity */
static int check_positive(int n, double x[MAXN]) {
    for (int i = 0; i < n; i++)
        if (x[i] <= 0)
            return 0;
    return 1;
}

/* TEST 1: Simple feasible case */
static MunitResult test_feasible_basic(const MunitParameter params[], void *data) {

    int n = 3, m = 1;

    double A[MAXM][MAXN] = { {1, 1, 1} };
    double b[MAXM] = {1};
    double c[MAXN] = {1, 2, 3};
    double x[3];

    int rc = interior_point_lp(n, m, A, b, c, x);
    munit_assert_int(rc, ==, 0);

    munit_assert_true(check_primal_res(n, m, A, b, x));
    munit_assert_true(check_positive(n, x));

    /* Optimal should be near (1,0,0) */
    munit_assert_double(x[0], >, 0.5);

    return MUNIT_OK;
}

/* TEST 2: Infeasible system */
static MunitResult test_infeasible(const MunitParameter params[], void *data) {

    int n = 2, m = 1;

    /* x1 + x2 = -1 (impossible for x > 0) */
    double A[MAXM][MAXN] = { {1, 1} };
    double b[MAXM] = {-1};
    double c[MAXN] = {1, 1};
    double x[2];

    int rc = interior_point_lp(n, m, A, b, c, x);

    /* Expect failure */
    munit_assert_int(rc, !=, 0);

    return MUNIT_OK;
}

/* TEST 3: Degenerate but feasible */
static MunitResult test_degenerate(const MunitParameter params[], void *data) {

    int n = 2, m = 1;

    /* x1 + x2 = 1, objective = x1 */
    double A[MAXM][MAXN] = { {1, 1} };
    double b[MAXM] = {1};
    double c[MAXN] = {1, 0};
    double x[2];

    int rc = interior_point_lp(n, m, A, b, c, x);
    munit_assert_int(rc, ==, 0);

    /* Should push solution near x1 = 0, x2 = 1 */
    munit_assert_true(check_primal_res(n, m, A, b, x));
    munit_assert_true(check_positive(n, x));

    munit_assert_double(x[1], >, 0.5);

    return MUNIT_OK;
}

/* TEST 4: Multiple constraints */
static MunitResult test_multi_constraint(const MunitParameter params[], void *data) {

    int n = 3, m = 2;

    /*
       x1 + x2 + x3 = 1
       2x1 + x2 + 3x3 = 2
    */
    double A[MAXM][MAXN] = {
        {1, 1, 1},
        {2, 1, 3}
    };

    double b[MAXM] = {1, 2};
    double c[MAXN] = {3, 1, 2};
    double x[3];

    int rc = interior_point_lp(n, m, A, b, c, x);
    munit_assert_int(rc, ==, 0);

    munit_assert_true(check_positive(n, x));
    munit_assert_true(check_primal_res(n, m, A, b, x));

    return MUNIT_OK;
}

/* TEST 5: Identity constraint */
static MunitResult test_identity(const MunitParameter params[], void *data) {

    int n = 3, m = 3;

    double A[MAXM][MAXN] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    double b[MAXM] = {1, 2, 3};
    double c[MAXN] = {1, 1, 1};
    double x[3];

    int rc = interior_point_lp(n, m, A, b, c, x);
    munit_assert_int(rc, ==, 0);

    /* x should exactly equal b */
    munit_assert_double(x[0], ==, 1);
    munit_assert_double(x[1], ==, 2);
    munit_assert_double(x[2], ==, 3);

    return MUNIT_OK;
}

/* Test suite */
static MunitTest tests[] = {
    {"/feasible-basic", test_feasible_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/infeasible", test_infeasible, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/degenerate", test_degenerate, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/multi-constraint", test_multi_constraint, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/identity", test_identity, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "/interior-point-tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
