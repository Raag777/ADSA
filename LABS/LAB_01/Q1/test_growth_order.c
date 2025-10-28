#include <stdio.h>
#include <math.h>
#include "munit.h"
#include "growth_functions.c"

// ---------- Test 1: Check monotonic growth ----------
static MunitResult test_growth_functions(const MunitParameter params[], void* data) {
    double n1 = 100.0, n2 = 1000.0;

    munit_assert_double(f1(n2), >, f1(n1));
    munit_assert_double(f2(n2), >, f2(n1));
    munit_assert_double(f5(n2), >, f5(n1));
    munit_assert_double(f9(n2), >, f9(n1));

    // Decreasing function
    munit_assert_double(f3(n2), <, f3(n1));

    return MUNIT_OK;
}

// ---------- Test 2: Check Θ-equivalence pairs ----------
static MunitResult test_theta_equivalents(const MunitParameter params[], void* data) {
    double n = 1000.0;
    double ratio1 = f2(n) / f8(n);
    double ratio2 = f5(n) / f7(n);

    munit_assert_double(ratio1, >, 0.1);
    munit_assert_double(ratio1, <, 10.0);
    munit_assert_double(ratio2, >, 0.1);
    munit_assert_double(ratio2, <, 200.0);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/growth", test_growth_functions, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/theta", test_theta_equivalents, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/function-growth-tests", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
