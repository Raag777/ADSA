#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 20
#define MAXM 50
#define MAX_ITER 5000
#define EPS 1e-6

// Print vector
void printVector(int n, double x[]) {
    for (int i = 0; i < n; i++)
        printf("%lf ", x[i]);
    printf("\n");
}

int ellipsoidLP(int n, int m, double A[][MAXN], double b[], double x_out[]) {

    double x[MAXN] = {0};     // Start center at origin
    double Q[MAXN][MAXN];

    double R = 10;            // Reduced radius for stability
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Q[i][j] = (i == j ? R * R : 0.0);

    //  EARLY CONTRADICTION CHECK 
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {

            int opposite = 1;
            for (int k = 0; k < n; k++) {
                if (fabs(A[i][k] + A[j][k]) > EPS) {
                    opposite = 0;
                    break;
                }
            }

            if (opposite) {
                if (b[i] < -b[j] - EPS)
                    return 0; // Contradiction detected
            }
        }
    }

    //  MAIN ELLIPSOID LOOP 
    for (int iter = 0; iter < MAX_ITER; iter++) {

        int violated = -1;

        for (int i = 0; i < m; i++) {
            double dot = 0;
            for (int j = 0; j < n; j++)
                dot += A[i][j] * x[j];

            if (dot > b[i] + EPS) {
                violated = i;
                break;
            }
        }

        // No constraint violated → candidate solution
        if (violated == -1) {

            // Final feasibility validation
            for (int i = 0; i < m; i++) {
                double dot = 0;
                for (int j = 0; j < n; j++)
                    dot += A[i][j] * x[j];

                if (dot > b[i] + EPS)
                    return 0;  // NOT feasible
            }

            for (int i = 0; i < n; i++)
                x_out[i] = x[i];

            return 1; // feasible
        }

        //  Ellipsoid Update 
        double g[MAXN];
        for (int j = 0; j < n; j++)
            g[j] = A[violated][j];

        double Qg[MAXN];
        for (int i = 0; i < n; i++) {
            Qg[i] = 0;
            for (int j = 0; j < n; j++)
                Qg[i] += Q[i][j] * g[j];
        }

        double gQg = 0;
        for (int j = 0; j < n; j++)
            gQg += g[j] * Qg[j];

        for (int i = 0; i < n; i++)
            x[i] -= (1.0 / (n + 1)) * Qg[i] / sqrt(gQg);

        double factor1 = (double)(n*n) / (n*n - 1.0);
        double factor2 = 2.0 / (n + 1);

        double newQ[MAXN][MAXN];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                newQ[i][j] = factor1 * (Q[i][j] - factor2 * (Qg[i] * Qg[j]) / gQg);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                Q[i][j] = newQ[i][j];
    }

    return 0; // infeasible
}

#ifndef TEST_MODE
int main() {

    int n, m;
    double A[MAXM][MAXN];
    double b[MAXM];
    double x_feasible[MAXN];

    printf("Enter number of variables (n): ");
    scanf("%d", &n);

    printf("Enter number of constraints (m): ");
    scanf("%d", &m);

    printf("\nEnter matrix A (each row has %d coefficients):\n", n);
    for (int i = 0; i < m; i++) {
        printf("Constraint %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("\nEnter vector b (RHS values):\n");
    for (int i = 0; i < m; i++) {
        printf("b[%d] = ", i);
        scanf("%lf", &b[i]);
    }

    int ok = ellipsoidLP(n, m, A, b, x_feasible);

    if (ok) {
        printf("\nFeasible solution found:\n");
        printVector(n, x_feasible);
    } else {
        printf("\nNo feasible solution found.\n");
    }

    return 0;
}
#endif
