#include "munit.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    char str[MAX];
    struct Node* next;
} Node;

extern int dp[MAX][MAX];
extern Node* addToList(Node* head, const char* s);
extern Node* getAllLCS(char* X, char* Y, int m, int n);
extern int computeLCSLength(const char* X, const char* Y);
extern void printOneLCS(char* X, char* Y, int m, int n);

//  TEST CASES 

// 1️⃣ Basic Test — ABCBDAB vs BDCABA
static MunitResult test_basic(const MunitParameter params[], void* data) {
    char X[] = "ABCBDAB";
    char Y[] = "BDCABA";

    int len = computeLCSLength(X, Y);
    munit_assert_int(len, ==, 4);

    Node* list = getAllLCS(X, Y, strlen(X), strlen(Y));

    int found_BCAB = 0, found_BDAB = 0, found_BCBA = 0;

    while (list != NULL) {
        if (strcmp(list->str, "BCAB") == 0) found_BCAB = 1;
        if (strcmp(list->str, "BDAB") == 0) found_BDAB = 1;
        if (strcmp(list->str, "BCBA") == 0) found_BCBA = 1;
        list = list->next;
    }

    munit_assert_true(found_BCAB);
    munit_assert_true(found_BDAB);
    munit_assert_true(found_BCBA);

    return MUNIT_OK;
}

// 2️⃣ No common subsequence
static MunitResult test_no_common(const MunitParameter params[], void* data) {
    char X[] = "AAAA";
    char Y[] = "BBBB";

    int len = computeLCSLength(X, Y);
    munit_assert_int(len, ==, 0);

    Node* list = getAllLCS(X, Y, 4, 4);

    munit_assert_string_equal(list->str, "");

    return MUNIT_OK;
}

// 3️⃣ Identical strings
static MunitResult test_identical(const MunitParameter params[], void* data) {
    char X[] = "ABCDEFG";
    char Y[] = "ABCDEFG";

    int len = computeLCSLength(X, Y);
    munit_assert_int(len, ==, 7);

    Node* list = getAllLCS(X, Y, 7, 7);

    munit_assert_string_equal(list->str, "ABCDEFG");

    return MUNIT_OK;
}

// 4️⃣ Repeated characters
static MunitResult test_repeated(const MunitParameter params[], void* data) {
    char X[] = "AAAAAA";
    char Y[] = "AAA";

    int len = computeLCSLength(X, Y);
    munit_assert_int(len, ==, 3);

    Node* list = getAllLCS(X, Y, 6, 3);

    munit_assert_string_equal(list->str, "AAA");

    return MUNIT_OK;
}

//  TEST SUITE 

static MunitTest tests[] = {
    { "/basic/lcs", test_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/edge/no_common", test_no_common, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/edge/identical", test_identical, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/repeat/chars", test_repeated, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/Q8_LCS_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
