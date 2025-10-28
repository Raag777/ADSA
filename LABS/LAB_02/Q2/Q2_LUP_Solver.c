#include <stdio.h>
#include <math.h>

#define N 3
#define EPS 1e-9

// Function to perform LUP decomposition
int LUP_Decompose(double A[N][N], int P[N]) {
    for (int i = 0; i < N; i++)
        P[i] = i;

    for (int k = 0; k < N; k++) {
        double max = 0.0;
        int pivot = k;

        // Find pivot
        for (int i = k; i < N; i++) {
            if (fabs(A[i][k]) > max) {
                max = fabs(A[i][k]);
                pivot = i;
            }
        }

        // Check for singularity
        if (fabs(A[pivot][k]) < EPS)
            return -1;

        // Swap rows
        if (pivot != k) {
            for (int j = 0; j < N; j++) {
                double temp = A[k][j];
                A[k][j] = A[pivot][j];
                A[pivot][j] = temp;
            }
            int tempP = P[k];
            P[k] = P[pivot];
            P[pivot] = tempP;
        }

        // Elimination
        for (int i = k + 1; i < N; i++) {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j < N; j++)
                A[i][j] -= A[i][k] * A[k][j];
        }
    }
    return 0;
}

// Function to solve Ax = b using LUP decomposition
void LUP_Solve(double A[N][N], int P[N], double b[N], double x[N]) {
    double y[N];

    // Forward substitution for Ly = Pb
    for (int i = 0; i < N; i++) {
        double sum = b[P[i]];
        for (int j = 0; j < i; j++)
            sum -= A[i][j] * y[j];
        y[i] = sum;
    }

    // Backward substitution for Ux = y
    for (int i = N - 1; i >= 0; i--) {
        double sum = y[i];
        for (int j = i + 1; j < N; j++)
            sum -= A[i][j] * x[j];
        x[i] = sum / A[i][i];
    }
}

// Utility: print matrix
void print_matrix(const char *name, double A[N][N]) {
    printf("%s =\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf(" %8.4f", A[i][j]);
        printf("\n");
    }
}

// Utility: print vector
void print_vector(const char *name, double v[N]) {
    printf("%s = [", name);
    for (int i = 0; i < N; i++)
        printf(" %.4f", v[i]);
    printf(" ]\n");
}

#ifndef TEST_MODE
int main() {
    double A[N][N] = {
        {2, 3, 1},
        {4, 7, -1},
        {-2, 4, 5}
    };
    double b[N] = {1, 6, -3};
    double x[N];
    int P[N];

    printf("=== LUP Solver ===\n");
    print_matrix("A", A);
    print_vector("b", b);
    printf("\n");

    if (LUP_Decompose(A, P) == -1) {
        printf("Matrix is singular or nearly singular.\n");
        return 1;
    }

    LUP_Solve(A, P, b, x);

    printf("Solution of Ax = b:\n");
    print_vector("x", x);

    return 0;
}
#endif
