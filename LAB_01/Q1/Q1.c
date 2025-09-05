#include <stdio.h>
#include <math.h>
#include <string.h>

// Declare functions
double f1(int n) { return 1.0 / n; }
double f2(int n) { return log2(n); }
double f3(int n) { return 12 * sqrt(n); }
double f4(int n) { return 50 * sqrt(n); }
double f5(int n) { return pow(n, 0.51); }
double f6(int n) { return n * log2(n); }
double f7(int n) { return (double)n * n - 324; }
double f8(int n) { return 100.0 * n * n + 6 * n; }
double f9(int n) { return 2.0 * pow(n, 3); }
double f10(int n) { return pow(n, log2(n)); }
double f11(int n) { return pow(3, n); }
double f12(int n) { return n*pow(2, 32); }

#define NUM_FUNCS 12

int main() {
    int start, end, step;

    char *names[NUM_FUNCS] = {
        "f1(1/n)", "f2(log2(n))", "f3(12*sqrt(n))", "f4(50*sqrt(n))",
        "f5(n^0.51)", "f6(n*log2(n))", "f7(n^2-324)", "f8(100n^2+6n)",
        "f9(2n^3)", "f10(n^(log2(n)))", "f11(3^n)", "f12(n*2^32)"
    };

    // Function pointers
    double (*funcs[NUM_FUNCS])(int) = {
        f1, f2, f3, f4, f5, f6,
        f7, f8, f9, f10, f11, f12
    };

    printf("Enter start value of n: ");
    scanf("%d", &start);
    printf("Enter end value of n: ");
    scanf("%d", &end);
    printf("Enter step size: ");
    scanf("%d", &step);

    // Arrays for sums and averages
    double sums[NUM_FUNCS] = {0};
    double avgs[NUM_FUNCS] = {0};
    int count = 0;

    // Iterate over n
    for (int n = start; n <= end; n += step) {
        for (int i = 0; i < NUM_FUNCS; i++) {
            sums[i] += funcs[i](n);
        }
        count++;
    }

   


    // Compute per-function averages
    for (int i = 0; i < NUM_FUNCS; i++) {
        avgs[i] = sums[i] / count;
    }

     // Print each function’s sum
    printf("\n---------------------------------------------\n");
    printf("Sum of each function over given n range:\n\n");
    for (int i = 0; i < NUM_FUNCS; i++) {
        printf("%-20s  Sum Avg = %.6e\n", names[i], avgs[i]);
    }



    // Sorting
    double sorted_vals[NUM_FUNCS];
    char *sorted_names[NUM_FUNCS];

    for (int i = 0; i < NUM_FUNCS; i++) {
        sorted_vals[i] = avgs[i];
        sorted_names[i] = names[i];
    }

    for (int i = 0; i < NUM_FUNCS - 1; i++) {
        for (int j = i + 1; j < NUM_FUNCS; j++) {
            if (sorted_vals[i] > sorted_vals[j]) {
                double tmpVal = sorted_vals[i];
                sorted_vals[i] = sorted_vals[j];
                sorted_vals[j] = tmpVal;

                char *tmpName = sorted_names[i];
                sorted_names[i] = sorted_names[j];
                sorted_names[j] = tmpName;
            }
        }
    }

    // Final output in chain form
    printf("\n---------------------------------------------\n");
    printf("Ranking of averages (in increasing order):\n\n");

    for (int i = 0; i < NUM_FUNCS; i++) {
        printf("%s", sorted_names[i]);
        if (i < NUM_FUNCS - 1) {
            printf(" < ");
        }
    }
    printf("\n");

    return 0;
}
