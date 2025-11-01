#include <stdio.h>
#include <math.h>

#define MAX 10   // Maximum matrix size
#define EPS 1e-9 // Small value to check for singularity

// Function to perform LUP Decomposition
int LUP_Decompose(double A[MAX][MAX], int P[MAX], int n) {
    for (int i = 0; i < n; i++)
        P[i] = i;  // Initialize permutation matrix

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
            int tempP = P[k];
            P[k] = P[pivot];
            P[pivot] = tempP;
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

// Function to print a matrix
void printMatrix(double A[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%10.4f ", A[i][j]);
        }
        printf("\n");
    }
}

#ifndef TEST_MODE
int main() {
    int n;
    double A[MAX][MAX];
    int P[MAX];

    printf("Enter matrix size (n x n): ");
    scanf("%d", &n);

    printf("Enter matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    if (LUP_Decompose(A, P, n) != 0)
        return 1;

    printf("\nCombined LU Matrix (stored together):\n");
    printMatrix(A, n);

    // Separate L and U matrices for display
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

    printf("\nL (Lower Triangular) Matrix:\n");
    printMatrix(L, n);

    printf("\nU (Upper Triangular) Matrix:\n");
    printMatrix(U, n);

    printf("\nPermutation Vector P:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", P[i]);
    printf("\n");

    return 0;
}
#endif
