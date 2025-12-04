#include <stdio.h>
#include <stdlib.h>

#define MAX 64   // Maximum matrix dimension

//  Utility Functions 

void addMatrix(int n, int A[][MAX], int B[][MAX], int C[][MAX]) {
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subMatrix(int n, int A[][MAX], int B[][MAX], int C[][MAX]) {
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            C[i][j] = A[i][j] - B[i][j];
}

void printMatrix(int n, int A[][MAX]) {
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
}

//  Strassen Algorithm 

void strassen(int n, int A[][MAX], int B[][MAX], int C[][MAX]) {
    
    // Base case: normal multiplication
    if(n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];

    int M1[MAX][MAX], M2[MAX][MAX], M3[MAX][MAX], M4[MAX][MAX];
    int M5[MAX][MAX], M6[MAX][MAX], M7[MAX][MAX];

    int temp1[MAX][MAX], temp2[MAX][MAX];

    // Splitting matrices
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }
    }

    // M1 = (A11 + A22)(B11 + B22)
    addMatrix(k, A11, A22, temp1);
    addMatrix(k, B11, B22, temp2);
    strassen(k, temp1, temp2, M1);

    // M2 = (A21 + A22)B11
    addMatrix(k, A21, A22, temp1);
    strassen(k, temp1, B11, M2);

    // M3 = A11(B12 - B22)
    subMatrix(k, B12, B22, temp1);
    strassen(k, A11, temp1, M3);

    // M4 = A22(B21 - B11)
    subMatrix(k, B21, B11, temp1);
    strassen(k, A22, temp1, M4);

    // M5 = (A11 + A12)B22
    addMatrix(k, A11, A12, temp1);
    strassen(k, temp1, B22, M5);

    // M6 = (A21 - A11)(B11 + B12)
    subMatrix(k, A21, A11, temp1);
    addMatrix(k, B11, B12, temp2);
    strassen(k, temp1, temp2, M6);

    // M7 = (A12 - A22)(B21 + B22)
    subMatrix(k, A12, A22, temp1);
    addMatrix(k, B21, B22, temp2);
    strassen(k, temp1, temp2, M7);

    // C11 = M1 + M4 - M5 + M7
    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++)
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];

    // C12 = M3 + M5
    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++)
            C[i][j+k] = M3[i][j] + M5[i][j];

    // C21 = M2 + M4
    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++)
            C[i+k][j] = M2[i][j] + M4[i][j];

    // C22 = M1 - M2 + M3 + M6
    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++)
            C[i+k][j+k] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
}

#ifndef TEST_MODE

int main() {
    int n;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX] = {0};

    printf("Enter matrix size (n x n MUST be power of 2): ");
    scanf("%d", &n);

    printf("\nEnter matrix A:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d", &A[i][j]);

    printf("\nEnter matrix B:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d", &B[i][j]);

    strassen(n, A, B, C);

    printf("\nResult (Strassen Multiplication):\n");
    printMatrix(n, C);

    return 0;
}
#endif