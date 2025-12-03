#include <stdio.h>
#define MAX 10
#define EPS 1e-9

int inverseMatrix(int n, double A[MAX][MAX], double I[MAX][MAX]) {

    // Initialize I as identity matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            I[i][j] = (i == j ? 1.0 : 0.0);

    // Perform Gauss–Jordan elimination
    for (int i = 0; i < n; i++) {

        // If diagonal is 0, matrix is singular
        if (A[i][i] == 0) {
            return 0;
        }

        double pivot = A[i][i];

        // Normalize row i
        for (int j = 0; j < n; j++) {
            A[i][j] /= pivot;
            I[i][j] /= pivot;
        }

        // Eliminate all other rows
        for (int r = 0; r < n; r++) {
            if (r != i) {
                double factor = A[r][i];
                for (int c = 0; c < n; c++) {
                    A[r][c] -= factor * A[i][c];
                    I[r][c] -= factor * I[i][c];
                }
            }
        }
    }

    return 1;  // Successfully inverted
}

#ifndef TEST_MODE

int main() {

    int n;
    double A[MAX][MAX], I[MAX][MAX];

    printf("Enter order of matrix (n x n): ");
    scanf("%d", &n);

    printf("Enter matrix elements:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    // Copy A because inverseMatrix modifies it
    double temp[MAX][MAX];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[i][j] = A[i][j];

    if (!inverseMatrix(n, temp, I)) {
        printf("\nMatrix is singular. Inverse does NOT exist.\n");
        return 0;
    }

    printf("\nInverse Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%.4lf ", I[i][j]);
        printf("\n");
    }

    return 0;
}
#endif
