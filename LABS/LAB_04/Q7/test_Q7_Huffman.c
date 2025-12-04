#include "munit.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHARS 256
#define MAX_CODE_LEN 100

// Declare external functions from Q7_Huffman.c
extern struct Node* buildHuffman(int freq[]);
extern void generateCodes(struct Node* root, char* code, int depth,
                          char codes[MAX_CHARS][MAX_CODE_LEN]);

typedef struct Node Node;

/***********************************************************
 * Helper function — encode text using code table          *
 ***********************************************************/
static void encodeText(const char* text, char codes[MAX_CHARS][MAX_CODE_LEN], char* encoded) {
    encoded[0] = '\0';
    for (int i = 0; text[i] != '\0'; i++) {
        strcat(encoded, codes[(unsigned char)text[i]]);
    }
}

/***********************************************************
 * Test Case 1: Basic string "abcd"                        *
 ***********************************************************/
static MunitResult test_basic_acbd(const MunitParameter params[], void* data) {

    const char* text = "abcd";
    int freq[MAX_CHARS] = {0};

    for (int i = 0; text[i] != '\0'; i++)
        freq[(unsigned char)text[i]]++;

    Node* root = buildHuffman(freq);

    char codes[MAX_CHARS][MAX_CODE_LEN] = {{0}};
    char code[MAX_CODE_LEN];
    generateCodes(root, code, 0, codes);

    // Check all characters got valid codes
    munit_assert_string_not_equal(codes['a'], "");
    munit_assert_string_not_equal(codes['b'], "");
    munit_assert_string_not_equal(codes['c'], "");
    munit_assert_string_not_equal(codes['d'], "");

    // Encode the text
    char encoded[1000];
    encodeText(text, codes, encoded);

    // Output must not be empty
    munit_assert_string_not_equal(encoded, "");

    return MUNIT_OK;
}

/***********************************************************
 * Test Case 2: Repeated characters "aaaaaa"               *
 ***********************************************************/
static MunitResult test_repeated_chars(const MunitParameter params[], void* data) {

    const char* text = "aaaaaa";
    int freq[MAX_CHARS] = {0};

    for (int i = 0; text[i] != '\0'; i++)
        freq[(unsigned char)text[i]]++;

    Node* root = buildHuffman(freq);

    char codes[MAX_CHARS][MAX_CODE_LEN] = {{0}};
    char code[MAX_CODE_LEN];
    generateCodes(root, code, 0, codes);

    munit_assert_int(freq['a'], ==, 6);
    munit_assert_string_not_equal(codes['a'], "");

    char encoded[1000];
    encodeText(text, codes, encoded);

    // Encoded length = frequency * codeLength
    munit_assert_int(strlen(encoded), ==, 6 * strlen(codes['a']));

    return MUNIT_OK;
}

/***********************************************************
 * Test Case 3: Mixed text with spaces                     *
 ***********************************************************/
static MunitResult test_mixed_text(const MunitParameter params[], void* data) {

    const char* text = "hello world";
    int freq[MAX_CHARS] = {0};
    for (int i = 0; text[i] != '\0'; i++)
        freq[(unsigned char)text[i]]++;

    Node* root = buildHuffman(freq);

    char codes[MAX_CHARS][MAX_CODE_LEN] = {{0}};
    char code[MAX_CODE_LEN];
    generateCodes(root, code, 0, codes);

    // Check some important characters
    munit_assert_string_not_equal(codes['h'], "");
    munit_assert_string_not_equal(codes['e'], "");
    munit_assert_string_not_equal(codes['l'], "");
    munit_assert_string_not_equal(codes['o'], "");
    munit_assert_string_not_equal(codes[' '], "");
    munit_assert_string_not_equal(codes['w'], "");
    munit_assert_string_not_equal(codes['r'], "");
    munit_assert_string_not_equal(codes['d'], "");

    char encoded[2000];
    encodeText(text, codes, encoded);

    munit_assert_string_not_equal(encoded, "");

    return MUNIT_OK;
}

/***********************************************************
 * Test Case 4: File creation test (codes.txt and encoded) *
 ***********************************************************/
static MunitResult test_output_files(const MunitParameter params[], void* data) {

    // Create a small temporary file
    FILE* fp = fopen("temp_input.txt", "w");
    fprintf(fp, "abc");
    fclose(fp);

    // Simulate running the Huffman program manually:
    // Step 1 — read file and compute freq
    fp = fopen("temp_input.txt", "r");
    int freq[MAX_CHARS] = {0};
    char text[1000], c;
    int idx = 0;

    while ((c = fgetc(fp)) != EOF) {
        text[idx++] = c;
        freq[(unsigned char)c]++;
    }
    text[idx] = '\0';
    fclose(fp);

    // Step 2 — Build tree
    Node* root = buildHuffman(freq);

    // Step 3 — Generate codes
    char codes[MAX_CHARS][MAX_CODE_LEN] = {{0}};
    char temp[MAX_CODE_LEN];
    generateCodes(root, temp, 0, codes);

    // Step 4 — Write files
    FILE* codeFile = fopen("codes.txt", "w");
    for (int i = 0; i < MAX_CHARS; i++)
        if (freq[i] > 0)
            fprintf(codeFile, "'%c' -> %s\n", i, codes[i]);
    fclose(codeFile);

    FILE* outFile = fopen("encoded_output.txt", "w");
    for (int i = 0; i < idx; i++)
        fprintf(outFile, "%s", codes[(unsigned char)text[i]]);
    fclose(outFile);

    // Check files were created
    munit_assert_true(fopen("codes.txt", "r") != NULL);
    munit_assert_true(fopen("encoded_output.txt", "r") != NULL);

    return MUNIT_OK;
}

/***********************************************************
 * Test Suite                                              *
 ***********************************************************/
static MunitTest tests[] = {
    { "/basic/acbd", test_basic_acbd, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/repeat/aaaaaa", test_repeated_chars, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/mixed/text", test_mixed_text, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/file/output", test_output_files, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/Q7_Huffman_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
