#include "munit.h"
#include <string.h>
#include <ctype.h>

// Declare functions from the main program
void infixToPostfix(char infix[], char postfix[]);
int evaluatePostfix(char postfix[]);

// ----------------------------------------------------------
// Helper: Evaluate postfix WITHOUT user input (mock values)
// ----------------------------------------------------------
int evaluatePostfixMock(char postfix[], int values[]) {
    // Manual stack for evaluation
    int stack[100], top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isdigit(ch)) {
            stack[++top] = ch - '0';
        }
        else if (isalpha(ch)) {
            stack[++top] = values[toupper(ch) - 'A'];
        }
        else {
            int b = stack[top--];
            int a = stack[top--];

            switch (ch) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/': stack[++top] = a / b; break;
            }
        }
    }
    return stack[top];
}

// ----------------------------------------------------------
// TEST 1: Basic infix to postfix
// ----------------------------------------------------------
static MunitResult test_infix_basic(const MunitParameter params[], void* data) {
    char infix[] = "A+B";
    char postfix[100];
    infixToPostfix(infix, postfix);

    munit_assert_string_equal(postfix, "AB+");
    return MUNIT_OK;
}

// ----------------------------------------------------------
// TEST 2: Parentheses
// ----------------------------------------------------------
static MunitResult test_infix_parentheses(const MunitParameter params[], void* data) {
    char infix[] = "(A+B)*C";
    char postfix[100];
    infixToPostfix(infix, postfix);

    munit_assert_string_equal(postfix, "AB+C*");
    return MUNIT_OK;
}

// ----------------------------------------------------------
// TEST 3: Postfix evaluation with known values
// ----------------------------------------------------------
static MunitResult test_eval_simple(const MunitParameter params[], void* data) {
    char postfix[] = "AB+C*"; // (A + B) * C

    int values[26] = {0};
    values['A'-'A'] = 1;
    values['B'-'A'] = 2;
    values['C'-'A'] = 3;

    int result = evaluatePostfixMock(postfix, values);
    munit_assert_int(result, ==, 9); // (1+2)*3 = 9

    return MUNIT_OK;
}

// ----------------------------------------------------------
// TEST 4: Digits only
// ----------------------------------------------------------
static MunitResult test_eval_digits(const MunitParameter params[], void* data) {
    char postfix[] = "23*5+"; // 2*3+5 = 11

    int values[26] = {0}; // not needed

    int result = evaluatePostfixMock(postfix, values);
    munit_assert_int(result, ==, 11);

    return MUNIT_OK;
}

// ----------------------------------------------------------
// TEST SUITE
// ----------------------------------------------------------
static MunitTest tests[] = {
    {"/infix/basic", test_infix_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/infix/parentheses", test_infix_parentheses, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/eval/variables", test_eval_simple, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/eval/digits", test_eval_digits, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "/Q3_Infix_Postfix_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
