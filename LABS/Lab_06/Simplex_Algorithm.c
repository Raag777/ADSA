#include <stdio.h>
#include <float.h>
#include <math.h>

#define MAX 30


// PRINT TABLEAU

void printTableau(int rows, int cols, double T[MAX][MAX]) {
    printf("\nSimplex Tableau:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%10.3f ", T[i][j]);
        printf("\n");
    }
}


// FIND PIVOT COLUMN (most negative coefficient in row 0)

int findPivotColumn(int cols, double T[MAX][MAX]) {
    int pc = -1;
    double mostNeg = 0;

    for (int j = 0; j < cols - 1; j++) {  // ignore RHS
        if (T[0][j] < mostNeg) {
            mostNeg = T[0][j];
            pc = j;
        }
    }

    return pc; // -1 means optimal
}


// FIND PIVOT ROW (minimum positive ratio RHS / pivotColEntry)

int findPivotRow(int rows, int pc, int rhsCol, double T[MAX][MAX]) {
    int pr = -1;
    double best = DBL_MAX;

    for (int i = 1; i < rows; i++) {
        if (T[i][pc] > 0) {
            double ratio = T[i][rhsCol] / T[i][pc];
            if (ratio < best) {
                best = ratio;
                pr = i;
            }
        }
    }

    return pr; // -1 means unbounded
}


// PERFORM PIVOT OPERATION

void pivot(int rows, int cols, int pr, int pc, double T[MAX][MAX]) {
    double pivotVal = T[pr][pc];

    // Normalize pivot row
    for (int j = 0; j < cols; j++)
        T[pr][j] /= pivotVal;

    // Eliminate pivot column from other rows
    for (int i = 0; i < rows; i++) {
        if (i != pr) {
            double factor = T[i][pc];
            for (int j = 0; j < cols; j++)
                T[i][j] -= factor * T[pr][j];
        }
    }
}


// SIMPLEX MAIN ROUTINE

void simplex(int m, int n, double T[MAX][MAX]) {
    int rows = m + 1;
    int cols = n + m + 1; // original vars + slack + RHS
    int rhsCol = cols - 1;

    while (1) {
        printTableau(rows, cols, T);

        int pc = findPivotColumn(cols, T);
        if (pc == -1) {
            printf("\nOptimal solution reached.\n");
            break;
        }

        int pr = findPivotRow(rows, pc, rhsCol, T);
        if (pr == -1) {
            printf("\nUnbounded solution!\n");
            return;
        }

        printf("\nPivot at row %d, column %d\n", pr, pc);
        pivot(rows, cols, pr, pc, T);
    }

    // Final objective value
    printf("\nMax Z = %.3f\n", T[0][rhsCol]);

    // Print variable values
    printf("\nSolution:\n");
    for (int j = 0; j < n; j++) {
    double value = 0;
    int basic = 1;

    for (int i = 1; i < rows; i++) {
        if (fabs(T[i][j] - 1.0) < 1e-6) {
            // check column is identity
            for (int k = 1; k < rows; k++) {
                if (k != i && fabs(T[k][j]) > 1e-6) {
                    basic = 0;
                    break;
                }
            }
            if (basic) {
                value = T[i][rhsCol];
                break;
            }
        }
    }

    printf("x%d = %.3f\n", j + 1, value);
}
}

void simplex_solve(int m, int n, double T[MAX][MAX], double *Zout, double x[]) {
    int rows = m + 1;
    int cols = n + m + 1;
    int rhsCol = cols - 1;

    while (1) {
        int pc = findPivotColumn(cols, T);
        if (pc == -1)
            break;

        int pr = findPivotRow(rows, pc, rhsCol, T);
        if (pr == -1) return; // unbounded

        pivot(rows, cols, pr, pc, T);
    }

    *Zout = T[0][rhsCol];

    for (int j = 0; j < n; j++) {
        x[j] = 0;
        for (int i = 1; i <= m; i++) {
            if (fabs(T[i][j] - 1.0) < 1e-6) {
                int good = 1;
                for (int k = 1; k <= m; k++) {
                    if (k != i && fabs(T[k][j]) > 1e-6) good = 0;
                }
                if (good) x[j] = T[i][rhsCol];
            }
        }
    }
}


#ifndef TEST_MODE

int main() {
    int n, m;

    printf("Enter number of variables: ");
    scanf("%d", &n);

    printf("Enter number of constraints: ");
    scanf("%d", &m);

    int cols = n + m + 1;
    double T[MAX][MAX] = {0};

    // OBJECTIVE FUNCTION
    printf("\nEnter coefficients of Objective Function (Max Z):\n");
    for (int j = 0; j < n; j++) {
        scanf("%lf", &T[0][j]);
        T[0][j] *= -1; // Convert max to min form
    }

    // CONSTRAINTS
    printf("\nEnter constraint matrix A and RHS b:\n");
    for (int i = 1; i <= m; i++) {
        printf("\nConstraint %d:\n", i);

        for (int j = 0; j < n; j++)
            scanf("%lf", &T[i][j]);

        T[i][n + i - 1] = 1; // Slack variable

        scanf("%lf", &T[i][cols - 1]); // RHS
    }

    simplex(m, n, T);

    return 0;
}
#endif
