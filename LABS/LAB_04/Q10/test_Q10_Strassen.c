#include "munit.h"
#include <stdio.h>
#include <string.h>

#define MAX 64

extern void strassen(int n, int A[][MAX], int B[][MAX], int C[][MAX]);

//  Standard Matrix Multiplication 
void normalMultiply(int n, int A[][MAX], int B[][MAX], int C[][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

//  Compare Matrices 
static void assert_matrix_equal(int n, int A[][MAX], int B[][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            munit_assert_int(A[i][j], ==, B[i][j]);
}


// 1️⃣ Test Case: 2×2 Simple Matrix Multiplication

static MunitResult test_2x2_basic(const MunitParameter params[], void* data) {
    int A[MAX][MAX] = {{1,2},{3,4}};
    int B[MAX][MAX] = {{5,6},{7,8}};
    int C1[MAX][MAX], C2[MAX][MAX];

    strassen(2, A, B, C1);
    normalMultiply(2, A, B, C2);

    assert_matrix_equal(2, C1, C2);
    return MUNIT_OK;
}


// 2️⃣ Test Case: Identity Matrix

static MunitResult test_identity(const MunitParameter params[], void* data) {
    int A[MAX][MAX] = {{1,2},{3,4}};
    int B[MAX][MAX] = {{1,0},{0,1}};  // Identity
    int C1[MAX][MAX], C2[MAX][MAX];

    strassen(2, A, B, C1);
    normalMultiply(2, A, B, C2);

    assert_matrix_equal(2, C1, C2);
    return MUNIT_OK;
}


// 3️⃣ Test Case: Zero Matrix

static MunitResult test_zero_matrix(const MunitParameter params[], void* data) {
    int A[MAX][MAX] = {{1,2},{3,4}};
    int B[MAX][MAX] = {{0,0},{0,0}};
    int C1[MAX][MAX], C2[MAX][MAX];

    strassen(2, A, B, C1);
    normalMultiply(2, A, B, C2);

    assert_matrix_equal(2, C1, C2);
    return MUNIT_OK;
}


// 4️⃣ Test Case: 4×4 Matrix

static MunitResult test_4x4(const MunitParameter params[], void* data) {

    int A[MAX][MAX] = {
        {1,2,3,4},
        {5,6,7,8},
        {9,1,2,3},
        {4,5,6,7}
    };

    int B[MAX][MAX] = {
        {7,6,5,4},
        {3,2,1,0},
        {9,8,7,6},
        {1,2,3,4}
    };

    int C1[MAX][MAX], C2[MAX][MAX];

    strassen(4, A, B, C1);
    normalMultiply(4, A, B, C2);

    assert_matrix_equal(4, C1, C2);
    return MUNIT_OK;
}


// 5️⃣ Test Case: Random Small Matrix

static MunitResult test_random(const MunitParameter params[], void* data) {
    int A[MAX][MAX], B[MAX][MAX], C1[MAX][MAX], C2[MAX][MAX];

    // Generate 2×2 random matrices
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++){
            A[i][j] = (i+j+3) % 5;
            B[i][j] = (i*2+j) % 7;
        }

    strassen(2, A, B, C1);
    normalMultiply(2, A, B, C2);

    assert_matrix_equal(2, C1, C2);
    return MUNIT_OK;
}


// Test Suite Definition

static MunitTest tests[] = {
    { "/2x2/basic", test_2x2_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/identity", test_identity, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/zero", test_zero_matrix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/4x4", test_4x4, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/random", test_random, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/Q10_Strassen_Tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};


int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
