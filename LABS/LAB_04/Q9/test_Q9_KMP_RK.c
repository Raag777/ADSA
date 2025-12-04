#include "munit.h"
#include <stdio.h>
#include <string.h>

#define MAX 500

extern void computeLPS(char* pattern, int m, int lps[]);
extern void KMP(char* text, char* pattern);
extern void RabinKarp(char* text, char* pattern);

//  Helper function to capture printed output 
static void capture_output(void (*func)(char*, char*), char* text, char* pattern, char* buffer) {
    // Redirect stdout to a temporary file
    FILE* temp = freopen("temp_output.txt", "w", stdout);
    func(text, pattern);
    fflush(stdout);

    // Restore stdout
    freopen("CON", "w", stdout);

    // Read captured output
    FILE* fp = fopen("temp_output.txt", "r");
    buffer[0] = '\0';
    char line[200];

    while (fgets(line, sizeof(line), fp)) {
        strcat(buffer, line);
    }

    fclose(fp);
}


// 1️⃣ Test LPS Array


static MunitResult test_lps(const MunitParameter params[], void* data) {
    char pattern[] = "ABABCABAB";
    int lps[9];

    computeLPS(pattern, 9, lps);

    int expected[] = {0,0,1,2,0,1,2,3,4};

    for (int i = 0; i < 9; i++) {
        munit_assert_int(lps[i], ==, expected[i]);
    }

    return MUNIT_OK;
}


// 2️⃣ KMP Basic Match Test


static MunitResult test_kmp_basic(const MunitParameter params[], void* data) {
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";

    char output[500];
    capture_output(KMP, text, pattern, output);

    // Expect match at position 10
    munit_assert_not_null(strstr(output, "10"));

    return MUNIT_OK;
}


// 3️⃣ Rabin-Karp Basic Match Test


static MunitResult test_rk_basic(const MunitParameter params[], void* data) {
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";

    char output[500];
    capture_output(RabinKarp, text, pattern, output);

    munit_assert_not_null(strstr(output, "10"));

    return MUNIT_OK;
}


// 4️⃣ Pattern not in text


static MunitResult test_no_match(const MunitParameter params[], void* data) {
    char text[] = "HELLOWORLD";
    char pattern[] = "XYZ";

    char output1[500], output2[500];

    capture_output(KMP, text, pattern, output1);
    capture_output(RabinKarp, text, pattern, output2);

    // Should not contain any numeric match positions
    munit_assert_null(strpbrk(output1, "0123456789"));
    munit_assert_null(strpbrk(output2, "0123456789"));

    return MUNIT_OK;
}


// 5️⃣ Multiple Matches (repeating patterns)


static MunitResult test_multiple_matches(const MunitParameter params[], void* data) {
    char text[] = "AAAAAA";
    char pattern[] = "AAA";

    char output1[500], output2[500];

    capture_output(KMP, text, pattern, output1);
    capture_output(RabinKarp, text, pattern, output2);

    // Expected matches: 0, 1, 2, 3
    int expected[] = {0,1,2,3};

    for (int i = 0; i < 4; i++) {
        char pos[5];
        sprintf(pos, "%d", expected[i]);

        munit_assert_not_null(strstr(output1, pos));
        munit_assert_not_null(strstr(output2, pos));
    }

    return MUNIT_OK;
}


// 6️⃣ Pattern equals text


static MunitResult test_exact_match(const MunitParameter params[], void* data) {
    char text[] = "PATTERN";
    char pattern[] = "PATTERN";

    char output1[500], output2[500];

    capture_output(KMP, text, pattern, output1);
    capture_output(RabinKarp, text, pattern, output2);

    munit_assert_not_null(strstr(output1, "0"));
    munit_assert_not_null(strstr(output2, "0"));

    return MUNIT_OK;
}


//  Test Suite


static MunitTest tests[] = {
    { "/lps/compute", test_lps, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/kmp/basic", test_kmp_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/rk/basic", test_rk_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/match/none", test_no_match, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/match/multiple", test_multiple_matches, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/match/exact", test_exact_match, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/Q9_KMP_RK_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
