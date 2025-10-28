#include <stdio.h>

#define MAX 8   // maximum matrix size (increase if needed)



void add(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}


void subtract(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}


void strassen(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n) {
    if (n == 1) {  // Base case
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;  // Size of submatrices

    // Submatrices
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];
    int M1[MAX][MAX], M2[MAX][MAX], M3[MAX][MAX], M4[MAX][MAX];
    int M5[MAX][MAX], M6[MAX][MAX], M7[MAX][MAX];
    int temp1[MAX][MAX], temp2[MAX][MAX];

    // Step 1: Divide matrices A and B into 4 submatrices each
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }


    // Step 2: Calculate M1 to M7 using Strassen's formulas

    // M1 = (A11 + A22) * (B11 + B22)
    add(A11, A22, temp1, k);
    add(B11, B22, temp2, k);
    strassen(temp1, temp2, M1, k);

    // M2 = (A21 + A22) * B11
    add(A21, A22, temp1, k);
    strassen(temp1, B11, M2, k);

    // M3 = A11 * (B12 - B22)
    subtract(B12, B22, temp2, k);
    strassen(A11, temp2, M3, k);

    // M4 = A22 * (B21 - B11)
    subtract(B21, B11, temp2, k);
    strassen(A22, temp2, M4, k);

    // M5 = (A11 + A12) * B22
    add(A11, A12, temp1, k);
    strassen(temp1, B22, M5, k);

    // M6 = (A21 - A11) * (B11 + B12)
    subtract(A21, A11, temp1, k);
    add(B11, B12, temp2, k);
    strassen(temp1, temp2, M6, k);

    // M7 = (A12 - A22) * (B21 + B22)
    subtract(A12, A22, temp1, k);
    add(B21, B22, temp2, k);
    strassen(temp1, temp2, M7, k);


    // Step 3: Compute the 4 submatrices of result C


    int t1[MAX][MAX], t2[MAX][MAX];

    // C11 = M1 + M4 - M5 + M7
    add(M1, M4, t1, k);
    subtract(t1, M5, t2, k);
    add(t2, M7, C11, k);

    // C12 = M3 + M5
    add(M3, M5, C12, k);

    // C21 = M2 + M4
    add(M2, M4, C21, k);

    // C22 = M1 - M2 + M3 + M6
    subtract(M1, M2, t1, k);
    add(t1, M3, t2, k);
    add(t2, M6, C22, k);


    // Step 4: Combine C11, C12, C21, C22 into result matrix C

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}


// Function to print a matrix
void printMatrix(int A[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
}

// Function to find next power of 2 (for padding)
int nextPowerOf2(int n) {
    int p = 1;
    while (p < n) p *= 2;
    return p;
}

#ifndef TEST_MODE
int main() {
    int n;
    printf("Enter size of square matrices: ");
    scanf("%d", &n);

    int A[MAX][MAX] = {0}, B[MAX][MAX] = {0}, C[MAX][MAX] = {0};

    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    // Adjust matrix size to next power of 2 (padding with 0s)
    int m = nextPowerOf2(n);

    // Perform Strassen multiplication
    strassen(A, B, C, m);

    printf("\nResultant Matrix (A x B):\n");
    printMatrix(C, n);  // print only original n×n part

    return 0;
}
#endif
