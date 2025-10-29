#include "munit.h"
#include <stdio.h>
#include "Q3_defective_coin.c"

//  Test 1: Defective coin present in the middle 
static MunitResult test_defective_present(const MunitParameter params[], void* data) {
    int coins[] = {10, 10, 9, 10, 10};
    int expected_index = 2;
    int result = findDefective(coins, 5);
    munit_assert_int(result, ==, expected_index);
    return MUNIT_OK;
}

//  Test 2: All coins perfect 
static MunitResult test_all_perfect(const MunitParameter params[], void* data) {
    int coins[] = {10, 10, 10, 10, 10};
    int expected_index = -1;
    int result = findDefective(coins, 5);
    munit_assert_int(result, ==, expected_index);
    return MUNIT_OK;
}

//  Test 3: Defective coin at start 
static MunitResult test_first_defective(const MunitParameter params[], void* data) {
    int coins[] = {9, 10, 10, 10, 10};
    int expected_index = 0;
    int result = findDefective(coins, 5);
    munit_assert_int(result, ==, expected_index);
    return MUNIT_OK;
}

//  Test 4: Defective coin at end 
static MunitResult test_last_defective(const MunitParameter params[], void* data) {
    int coins[] = {10, 10, 10, 10, 9};
    int expected_index = 4;
    int result = findDefective(coins, 5);
    munit_assert_int(result, ==, expected_index);
    return MUNIT_OK;
}

//  Test 5: Odd number of coins with middle defective 
static MunitResult test_odd_count_middle_defective(const MunitParameter params[], void* data) {
    int coins[] = {10, 10, 9, 10, 10, 10, 10};
    int expected_index = 2;
    int result = findDefective(coins, 7);
    munit_assert_int(result, ==, expected_index);
    return MUNIT_OK;
}

//  Test Suite 
static MunitTest test_suite_tests[] = {
    {"/test_defective_present", test_defective_present, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/test_all_perfect", test_all_perfect, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/test_first_defective", test_first_defective, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/test_last_defective", test_last_defective, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/test_odd_count_middle_defective", test_odd_count_middle_defective, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite test_suite = {
    "/Q3_defective_coin",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

//  Main for running test suite 
int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}
