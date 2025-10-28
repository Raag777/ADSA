#include <stdio.h>
#include <math.h>

#define MAX 10   // maximum matrix size
#define EPS 1e-9 // tolerance for singular check

//  LUP Decomposition 
int LUP_Decompose(double A[MAX][MAX], int P[MAX], int n) {
    for (int i = 0; i < n; i++)
        P[i] = i; // Initialize permutation

    for (int k = 0; k < n; k++) {
        // Find pivot
        double max = 0.0;
        int pivot = k;
        for (int i = k; i < n; i++) {
            if (fabs(A[i][k]) > max) {
                max = fabs(A[i][k]);
                pivot = i;
            }
        }

        // Check for singularity
        if (fabs(max) < EPS) {
            printf("Matrix is singular or near singular!\n");
            return -1;
        }

        // Swap rows in A and P
        if (pivot != k) {
            for (int j = 0; j < n; j++) {
                double temp = A[k][j];
                A[k][j] = A[pivot][j];
                A[pivot][j] = temp;
            }
            int temp = P[k];
            P[k] = P[pivot];
            P[pivot] = temp;
        }

        // Eliminate entries below the pivot
        for (int i = k + 1; i < n; i++) {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j < n; j++) {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }

    return 0;
}

//  Forward Substitution (L*y = P*b) 
void forwardSubstitution(double A[MAX][MAX], int P[MAX], double b[MAX], double y[MAX], int n) {
    for (int i = 0; i < n; i++) {
        y[i] = b[P[i]];
        for (int j = 0; j < i; j++) {
            y[i] -= A[i][j] * y[j];
        }
    }
}

//  Backward Substitution (U*x = y) 
void backwardSubstitution(double A[MAX][MAX], double y[MAX], double x[MAX], int n) {
    for (int i = n - 1; i >= 0; i--) {
        double sum = y[i];
        for (int j = i + 1; j < n; j++) {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }
}

//  Solve Ax = b using LUP 
void LUP_Solve(double A[MAX][MAX], int P[MAX], double b[MAX], double x[MAX], int n) {
    double y[MAX];
    forwardSubstitution(A, P, b, y, n);
    backwardSubstitution(A, y, x, n);
}

//  Display Matrix 
void printMatrix(double A[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%10.4f ", A[i][j]);
        }
        printf("\n");
    }
}

//  Display Vector 
void printVector(double v[MAX], int n) {
    for (int i = 0; i < n; i++) {
        printf("%10.4f ", v[i]);
    }
    printf("\n");
}

#ifndef TEST_MODE
int main() {
    int n;
    double A[MAX][MAX], b[MAX], x[MAX];
    int P[MAX];

    printf("Enter matrix size (n x n): ");
    scanf("%d", &n);

    printf("Enter matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    printf("Enter vector b (%d elements):\n", n);
    for (int i = 0; i < n; i++)
        scanf("%lf", &b[i]);

    if (LUP_Decompose(A, P, n) != 0)
        return 1;

    // Display combined LU matrix
    printf("\nCombined LU matrix:\n");
    printMatrix(A, n);

    // Display L and U matrices separately
    double L[MAX][MAX], U[MAX][MAX];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j) {
                L[i][j] = A[i][j];
                U[i][j] = 0.0;
            } else if (i == j) {
                L[i][j] = 1.0;
                U[i][j] = A[i][j];
            } else {
                L[i][j] = 0.0;
                U[i][j] = A[i][j];
            }
        }
    }

    printf("\nL matrix:\n");
    printMatrix(L, n);

    printf("\nU matrix:\n");
    printMatrix(U, n);

    printf("\nPermutation vector P:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", P[i]);
    printf("\n");

    // Solve for x
    LUP_Solve(A, P, b, x, n);

    printf("\nSolution vector x:\n");
    printVector(x, n);

    return 0;
}
#endif
