#include "munit.h"
#include <stdio.h>
#include <string.h>

void computeLPS(char pattern[], int m, int lps[]);
void KMPsearch(char text[], char pattern[]);

static int countMatches(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);
    int lps[m];
    computeLPS(pattern, m, lps);

    int i = 0, j = 0;
    int count = 0;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            count++;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return count;
}

/*  Test LPS Computation  */
static MunitResult test_lps(const MunitParameter params[], void* data) {
    char pattern[] = "ABABCABAB";
    int expected[] = {0,0,1,2,0,1,2,3,4};
    int m = strlen(pattern);
    
    int lps[m];
    computeLPS(pattern, m, lps);

    for(int i = 0; i < m; i++)
        munit_assert_int(lps[i], ==, expected[i]);

    return MUNIT_OK;
}

/*  Test Single Occurrence  */
static MunitResult test_single_match(const MunitParameter params[], void* data) {
    char text[] = "ababcabcabababd";
    char pat[] = "ababd";

    int matches = countMatches(text, pat);
    munit_assert_int(matches, ==, 1);

    return MUNIT_OK;
}

/*  Test Multiple Occurrences  */
static MunitResult test_multiple_match(const MunitParameter params[], void* data) {
    char text[] = "aaaaa";
    char pat[] = "aa";

    int matches = countMatches(text, pat);
    munit_assert_int(matches, ==, 4);

    return MUNIT_OK;
}

/*  Test No Match Case  */
static MunitResult test_no_match(const MunitParameter params[], void* data) {
    char text[] = "abcdef";
    char pat[] = "gh";

    int matches = countMatches(text, pat);
    munit_assert_int(matches, ==, 0);

    return MUNIT_OK;
}

/*  Test Pattern = Text  */
static MunitResult test_exact_match(const MunitParameter params[], void* data) {
    char text[] = "abc";
    char pat[] = "abc";

    int matches = countMatches(text, pat);
    munit_assert_int(matches, ==, 1);

    return MUNIT_OK;
}

/*  Test Table  */
static MunitTest tests[] = {
    { "/lps", test_lps, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/single_match", test_single_match, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/multiple_match", test_multiple_match, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/no_match", test_no_match, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/exact_match", test_exact_match, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/*  Suite Definition  */
static const MunitSuite suite = {
    "/kmp_tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
