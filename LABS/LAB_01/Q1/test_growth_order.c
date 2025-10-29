#include <stdio.h>
#include <math.h>
#include "munit.h"
#include "growth_order.c" 

//  TEST 1: Check monotonic growth 
static MunitResult test_growth_functions(const MunitParameter params[], void* data) {
    double n1 = 100.0, n2 = 1000.0;

    munit_assert_double(f1(n2), >, f1(n1));  // n log n increases
    munit_assert_double(f2(n2), >, f2(n1));  // sqrt growth increases
    munit_assert_double(f5(n2), >, f5(n1));  // quadratic increases
    munit_assert_double(f9(n2), >, f9(n1));  // cubic increases

    // Decreasing function
    munit_assert_double(f3(n2), <, f3(n1));  // 1/n decreases

    return MUNIT_OK;
}

//  TEST 2: Check Θ-equivalent pairs 
static MunitResult test_theta_equivalents(const MunitParameter params[], void* data) {
    double n = 1000.0;
    double ratio1 = f2(n) / f8(n);  // 12√n vs 50√n
    double ratio2 = f5(n) / f7(n);  // 100n²+6n vs n²-324

    munit_assert_double(ratio1, >, 0.1);
    munit_assert_double(ratio1, <, 10.0);
    munit_assert_double(ratio2, >, 0.1);
    munit_assert_double(ratio2, <, 200.0);

    return MUNIT_OK;
}

//  TEST 3: Verify growth order chain 
static MunitResult test_chain_order(const MunitParameter params[], void* data) {
    double n = 1000.0;

    // Correct ascending order based on growth_order.c
    double values[12] = {
        f3(n),   // 1/n
        f10(n),  // log₂n
        f6(n),   // n^0.51
        f2(n),   // 12√n
        f8(n),   // 50√n
        f1(n),   // n log₂n
        f7(n),   // n² - 324
        f5(n),   // 100n² + 6n
        f9(n),   // 2n³
        f12(n),  // 2³²n
        f4(n),   // n^(log n)
        f11(n)   // 3ⁿ
    };

    for (int i = 0; i < 11; i++) {
        if (!(values[i] < values[i + 1])) {
            printf("Chain break: f%d(n)=%.3e >= f%d(n)=%.3e\n",
                   i + 1, values[i], i + 2, values[i + 1]);
            munit_error("Growth order chain violated!");
        }
    }

    return MUNIT_OK;
}

//  TEST SUITE 
static MunitTest tests[] = {
    { "/growth", test_growth_functions, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/theta", test_theta_equivalents, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/chain", test_chain_order, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/function-growth-tests", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
