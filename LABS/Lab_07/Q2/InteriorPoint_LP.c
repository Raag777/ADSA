#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 50
#define MAXM 50

#define T_INIT 1.0
#define MU 20.0
#define NEWTON_TOL 1e-12
#define BARRIER_TOL 1e-9
#define MAX_NEWTON_ITERS 100
#define BACKTRACK_ALPHA 0.01
#define BACKTRACK_BETA 0.5
#define EPS 1e-12

/* Utility: print vector */
void print_vec(const char *name, int n, double *v) {
    printf("%s:", name);
    for (int i = 0; i < n; ++i) printf(" %g", v[i]);
    printf("\n");
}

/* tidy small values for nicer output */
void tidy_solution(int n, double x[MAXN], double tol) {
    for (int i = 0; i < n; ++i)
        if (fabs(x[i]) < tol) x[i] = 0.0;
}

/* Dense linear solve (Gaussian elimination) for Ax = b.
   Solves n x n system in-place on a copy of A; returns 0 on success.
*/
int gauss_solve(int n, double A[MAXM][MAXM], double b[MAXM], double x_out[MAXM]) {
    if (n == 0) return 0;
    double M[MAXM][MAXM+1];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) M[i][j] = A[i][j];
        M[i][n] = b[i];
    }

    for (int k = 0; k < n; ++k) {
        int piv = k;
        double maxv = fabs(M[k][k]);
        for (int i = k+1; i < n; ++i) {
            if (fabs(M[i][k]) > maxv) { maxv = fabs(M[i][k]); piv = i; }
        }
        if (maxv < 1e-15) return -1; // singular or ill-conditioned

        if (piv != k) {
            for (int j = k; j <= n; ++j) {
                double tmp = M[k][j]; M[k][j] = M[piv][j]; M[piv][j] = tmp;
            }
        }

        for (int i = k+1; i < n; ++i) {
            double f = M[i][k] / M[k][k];
            for (int j = k; j <= n; ++j) M[i][j] -= f * M[k][j];
        }
    }

    for (int i = 0; i < n; ++i) x_out[i] = 0.0;
    for (int i = n-1; i >= 0; --i) {
        double s = M[i][n];
        for (int j = i+1; j < n; ++j) s -= M[i][j] * x_out[j];
        x_out[i] = s / M[i][i];
    }
    return 0;
}

/* Multiply matrix A (m x n) by vector x (n) -> y (m) */
void matvec_Ax(int m, int n, double A[MAXM][MAXN], double x[MAXN], double y[MAXM]) {
    for (int i = 0; i < m; ++i) {
        double s = 0.0;
        for (int j = 0; j < n; ++j) s += A[i][j] * x[j];
        y[i] = s;
    }
}

/* Multiply A^T (n x m) by vector y (m) -> z (n) */
void matTvec_Ay(int m, int n, double A[MAXM][MAXN], double y[MAXM], double z[MAXN]) {
    for (int i = 0; i < n; ++i) {
        double s = 0.0;
        for (int j = 0; j < m; ++j) s += A[j][i] * y[j];
        z[i] = s;
    }
}

/* Compute diag(x.^2) * v  (since H^{-1} = diag(x^2)) */
void diag_x2_mul(int n, double x[MAXN], double v[MAXN], double out[MAXN]) {
    for (int i = 0; i < n; ++i) out[i] = x[i]*x[i] * v[i];
}

/* Inner product */
double dot(int n, double *a, double *b) {
    double s = 0.0;
    for (int i = 0; i < n; ++i) s += a[i]*b[i];
    return s;
}

/* Solve barrier subproblem for given t:
   minimize t*c^T x - sum(log x) subject to A x = b
   using Newton's method with equality constraints.
   Returns 0 on success and x,y updated (in-place).
*/
int barrier_newton(int n, int m,
                   double A[MAXM][MAXN],
                   double bvec[MAXM],
                   double c[MAXN],
                   double x[MAXN],    // IN/OUT: starting x (>0)
                   double y[MAXM],    // IN/OUT: starting y
                   double t) {

    double X2[MAXN];     // x^2 for H^{-1}
    double grad[MAXN];   // gradient: t*c - 1/x + A^T y
    double r_pri[MAXM];
    double AHinvAt[MAXM][MAXM];
    double tmp_n[MAXN], tmp_m[MAXM], rhs_m[MAXM], dy[MAXM], dx[MAXN];

    for (int iter = 0; iter < MAX_NEWTON_ITERS; ++iter) {
        // Compute gradient r_dual = t*c - 1/x + A^T y
        for (int i = 0; i < n; ++i) {
            if (x[i] <= 0) return -1; // safeguard: x must stay > 0
            grad[i] = t * c[i] - 1.0 / x[i];
        }
        matTvec_Ay(m, n, A, y, tmp_n);
        for (int i = 0; i < n; ++i) grad[i] += tmp_n[i];

        // Primal residual r_pri = A x - b
        matvec_Ax(m, n, A, x, r_pri);
        for (int i = 0; i < m; ++i) r_pri[i] -= bvec[i];

        // Newton decrement estimate: lambda^2 = grad^T H^{-1} grad
        for (int i = 0; i < n; ++i) X2[i] = x[i]*x[i];
        diag_x2_mul(n, x, grad, tmp_n); // tmp_n = H^{-1} * grad
        double lambda2 = dot(n, grad, tmp_n);
        if (!isfinite(lambda2)) return -1;
        if (lambda2 / 2.0 < NEWTON_TOL) {
            // converged for this t
            return 0;
        }

        // Form Schur complement S = A * H^{-1} * A^T (m x m)
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j)
                AHinvAt[i][j] = 0.0;

        for (int k = 0; k < n; ++k) {
            double w = X2[k];
            if (w == 0.0) continue;
            for (int i = 0; i < m; ++i) {
                double Aik = A[i][k];
                if (Aik == 0.0) continue;
                for (int j = 0; j < m; ++j) {
                    AHinvAt[i][j] += Aik * (w * A[j][k]);
                }
            }
        }

        // rhs = r_pri - A * H^{-1} * grad
        diag_x2_mul(n, x, grad, tmp_n); // tmp_n = H^{-1} * grad
        for (int i = 0; i < m; ++i) tmp_m[i] = 0.0;
        for (int i = 0; i < m; ++i)
            for (int k = 0; k < n; ++k)
                tmp_m[i] += A[i][k] * tmp_n[k];
        for (int i = 0; i < m; ++i) rhs_m[i] = r_pri[i] - tmp_m[i];

        // Solve for dy
        int rc = gauss_solve(m, AHinvAt, rhs_m, dy);
        if (rc != 0) {
            return -1; // singular Schur complement
        }

        // Recover dx = -H^{-1}(A^T dy + grad)
        matTvec_Ay(m, n, A, dy, tmp_n);
        for (int i = 0; i < n; ++i) {
            double v = tmp_n[i] + grad[i];
            dx[i] = - X2[i] * v;
        }

        // Backtracking line search to ensure x + alpha*dx > 0
        double alpha = 1.0;
        for (int i = 0; i < n; ++i) {
            if (dx[i] < 0) {
                double a_i = -x[i] / dx[i];
                if (a_i < alpha) alpha = 0.99 * a_i;
            }
        }
        if (alpha <= 0) return -1;

        while (alpha > 1e-12) {
            // try step
            for (int i = 0; i < n; ++i) tmp_n[i] = x[i] + alpha * dx[i];

            // primal residual norm
            matvec_Ax(m, n, A, tmp_n, tmp_m);
            double norm_pri = 0.0;
            for (int i = 0; i < m; ++i) {
                double r = tmp_m[i] - bvec[i];
                norm_pri += r*r;
            }

            // dual residual approx check (simple)
            double norm_dual = 0.0;
            for (int i = 0; i < n; ++i) {
                double rd = t*c[i] - 1.0/tmp_n[i];
                norm_dual += rd*rd;
            }

            if (isfinite(norm_pri) && isfinite(norm_dual)) break;
            alpha *= BACKTRACK_BETA;
        }

        // Update primal and dual variables
        for (int i = 0; i < n; ++i) x[i] += alpha * dx[i];
        for (int i = 0; i < m; ++i) y[i] += alpha * dy[i];
    }

    return -2; // failed to converge within max Newton iters
}

/* Compute objective value c^T x */
double objective(int n, double c[MAXN], double x[MAXN]) {
    double s = 0.0;
    for (int i = 0; i < n; ++i) s += c[i]*x[i];
    return s;
}

/* Basic routine to obtain a starting x that (approximately) satisfies A x = b:
   solve least squares A x = b using normal equations (A^T A) x = A^T b
   then shift x to be strictly positive by adding small constant if needed.
*/
int initial_point(int n, int m, double A[MAXM][MAXN], double bvec[MAXM], double x[MAXN]) {
    double AtA[MAXN][MAXN]; double Atb[MAXN];
    for (int i = 0; i < n; ++i) {
        Atb[i] = 0.0;
        for (int j = 0; j < n; ++j) AtA[i][j] = 0.0;
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            Atb[j] += A[i][j] * bvec[i];
            for (int k = 0; k < n; ++k) AtA[j][k] += A[i][j] * A[i][k];
        }
    }
    double AtA_copy[MAXN][MAXN];
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) AtA_copy[i][j] = AtA[i][j];
    double xls[MAXN];
    for (int i = 0; i < n; ++i) xls[i] = 0.0;
    int rc = gauss_solve(n, AtA_copy, Atb, xls);
    if (rc != 0) {
        for (int i = 0; i < n; ++i) x[i] = 1.0;
        return 0;
    }
    double minv = 1e100;
    for (int i = 0; i < n; ++i) {
        x[i] = xls[i];
        if (x[i] < minv) minv = x[i];
    }
    if (minv <= 0) {
        double shift = 1.0 - minv;
        for (int i = 0; i < n; ++i) x[i] += shift;
    }
    for (int i = 0; i < n; ++i) if (x[i] < 1e-6) x[i] = 1e-6;
    return 0;
}

/* Main interior point driver */
int interior_point_lp(int n, int m,
                      double A[MAXM][MAXN],
                      double bvec[MAXM],
                      double c[MAXN],
                      double x[MAXN]) {

    double y[MAXM]; for (int i = 0; i < m; ++i) y[i] = 0.0;
    initial_point(n, m, A, bvec, x);

    double t = T_INIT;
    int max_outer = 400;
    for (int outer = 0; outer < max_outer; ++outer) {
        int rc = barrier_newton(n, m, A, bvec, c, x, y, t);
        if (rc != 0) {
            return -1;
        }

        double gap = (double)n / t;
        if (gap < BARRIER_TOL) break;
        t *= MU;
    }
    return 0;
}

#ifndef TEST_MODE

int main() {
    int n, m;
    printf("Enter number of variables n (<=%d): ", MAXN);
    if (scanf("%d", &n) != 1) return 0;
    printf("Enter number of equality constraints m (<=%d): ", MAXM);
    if (scanf("%d", &m) != 1) return 0;
    if (n <= 0 || m < 0 || n > MAXN || m > MAXM) { printf("Invalid sizes\n"); return 0; }

    double A[MAXM][MAXN];
    double bvec[MAXM];
    double c[MAXN];
    double x[MAXN];

    printf("Enter matrix A (m rows, n columns):\n");
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%lf", &A[i][j]);

    printf("Enter vector b (length m):\n");
    for (int i = 0; i < m; ++i) scanf("%lf", &bvec[i]);

    printf("Enter objective c (length n):\n");
    for (int i = 0; i < n; ++i) scanf("%lf", &c[i]);

    int rc = interior_point_lp(n, m, A, bvec, c, x);
    if (rc != 0) {
        printf("Solver failed (rc=%d)\n", rc);
        return 0;
    }

    tidy_solution(n, x, 1e-8);

    printf("\nSolution x (approx):\n");
    for (int i = 0; i < n; ++i) printf("%g ", x[i]);
    printf("\nObjective value: %g\n", objective(n, c, x));

    /* Print primal residual norm for verification */
    double rnorm = 0.0, tmp[MAXM];
    matvec_Ax(m, n, A, x, tmp);
    for (int i = 0; i < m; ++i) {
        double r = tmp[i] - bvec[i];
        rnorm += r*r;
    }
    printf("Primal residual norm (squared): %g\n", rnorm);

    return 0;
}
#endif
