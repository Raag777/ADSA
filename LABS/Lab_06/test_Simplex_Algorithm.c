#include "munit.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 30

// Declare simplex API function
void simplex_solve(int m, int n, double T[MAX][MAX], double *Zout, double x[]);


// HELPER MACRO FOR FLOAT COMPARISON

#define ASSERT_DBL_EQ(actual, expected) \
    munit_assert_double_equal(actual, expected, 6);


// TEST CASE 1
// Max Z = 4x1 + 3x2
// Expected: x1=3, x2=2, Z=18

static MunitResult test_case1(const MunitParameter params[], void* data) {
    double T[MAX][MAX] = {0};
    int m = 2, n = 2;

    T[0][0] = -4; T[0][1] = -3;
    T[1][0] = 2; T[1][1] = 1; T[1][2] = 1; T[1][4] = 8;
    T[2][0] = 1; T[2][1] = 1; T[2][3] = 1; T[2][4] = 5;

    double Z, xvals[3];
    simplex_solve(m, n, T, &Z, xvals);

    ASSERT_DBL_EQ(Z, 18.0);
    ASSERT_DBL_EQ(xvals[0], 3.0);
    ASSERT_DBL_EQ(xvals[1], 2.0);

    return MUNIT_OK;
}


// TEST CASE 2
// Max Z = 5x1 + 4x2
// Expected: x1=3, x2=1.5, Z=21

static MunitResult test_case2(const MunitParameter params[], void* data) {
    double T[MAX][MAX] = {0};
    int m = 2, n = 2;

    T[0][0] = -5; T[0][1] = -4;
    T[1][0] = 6; T[1][1] = 4; T[1][2] = 1; T[1][4] = 24;
    T[2][0] = 1; T[2][1] = 2; T[2][3] = 1; T[2][4] = 6;

    double Z, xvals[3];
    simplex_solve(m, n, T, &Z, xvals);

    ASSERT_DBL_EQ(Z, 21.0);
    ASSERT_DBL_EQ(xvals[0], 3.0);
    ASSERT_DBL_EQ(xvals[1], 1.5);

    return MUNIT_OK;
}


// TEST CASE 3 (Harder Fractions)
// Max Z = 7x1 + 9x2
// Expected: x1=3, x2=4, Z=57

static MunitResult test_case3(const MunitParameter params[], void* data) {
    double T[MAX][MAX] = {0};
    int m = 2, n = 2;

    T[0][0] = -7; T[0][1] = -9;
    T[1][0] = 2; T[1][1] = 1; T[1][2] = 1; T[1][4] = 10;
    T[2][0] = 1; T[2][1] = 3; T[2][3] = 1; T[2][4] = 15;

    double Z, xvals[3];
    simplex_solve(m, n, T, &Z, xvals);

    ASSERT_DBL_EQ(Z, 57.0);
    ASSERT_DBL_EQ(xvals[0], 3.0);
    ASSERT_DBL_EQ(xvals[1], 4.0);

    return MUNIT_OK;
}


// TEST CASE 4 (Simple)
// Max Z = 2x1 + 3x2
// Expected: x1=0, x2=1, Z=3

static MunitResult test_case4(const MunitParameter params[], void* data) {
    double T[MAX][MAX] = {0};
    int m = 2, n = 2;

    T[0][0] = -2; T[0][1] = -3;
    T[1][0] = 1; T[1][1] = 1; T[1][2] = 1; T[1][4] = 1;
    T[2][0] = 2; T[2][1] = 1; T[2][3] = 1; T[2][4] = 2;

    double Z, xvals[3];
    simplex_solve(m, n, T, &Z, xvals);

    ASSERT_DBL_EQ(Z, 3.0);
    ASSERT_DBL_EQ(xvals[0], 0.0);
    ASSERT_DBL_EQ(xvals[1], 1.0);

    return MUNIT_OK;
}


// TEST CASE 5 (3 Variables)
// Max Z = x1 + x2 + x3
// Expected: x1=5, x2=0, x3=5, Z=10

static MunitResult test_case5(const MunitParameter params[], void* data) {
    double T[MAX][MAX] = {0};
    int m = 2, n = 3;

    T[0][0] = -1; T[0][1] = -1; T[0][2] = -1;
    T[1][0] = 1; T[1][1] = 2; T[1][2] = 1; T[1][3] = 1; T[1][5] = 10;
    T[2][0] = 2; T[2][1] = 1; T[2][2] = 3; T[2][4] = 1; T[2][5] = 15;

    double Z, xvals[4];
    simplex_solve(m, n, T, &Z, xvals);

    ASSERT_DBL_EQ(Z, 8.333333);
    ASSERT_DBL_EQ(xvals[0], 6.666666);
    ASSERT_DBL_EQ(xvals[1], 1.666666);
    ASSERT_DBL_EQ(xvals[2], 0.0);


    return MUNIT_OK;
}


// TEST CASE 6 — Unbounded LP
// Max Z = x1 + x2
// Constraint: x1 - x2 >= 0  (converted to <= by multiplying -1)
// This is unbounded.

static MunitResult test_case6(const MunitParameter params[], void* data) {
    double T[MAX][MAX] = {0};
    int m = 1, n = 2;

    T[0][0] = -1; T[0][1] = -1;

    // Constraint:  -x1 + x2 <= 0   (converted)
    T[1][0] = -1; T[1][1] = 1; 
    T[1][2] = 1;
    T[1][3] = 0;

    double Z = 0;
    double xvals[3] = {0};

    simplex_solve(m, n, T, &Z, xvals);

    // For unbounded LP, Z will remain unchanged (0)
    munit_assert_double_equal(Z, 0.0, 6);

    return MUNIT_OK;
}


// TEST SUITE

static MunitTest tests[] = {
    { "/test_case1", test_case1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_case2", test_case2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_case3", test_case3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_case4", test_case4, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_case5", test_case5, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_case6_unbounded", test_case6, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, 0, NULL }
};

static const MunitSuite suite = {
    "/simplex-tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
