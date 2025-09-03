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
double f12(int n) { return pow(2, n); }

#define NUM_FUNCS 12

int main() {
    int start, end, step;


    char *names[NUM_FUNCS] = {
        "1/n", "log2(n)", "12*sqrt(n)", "50*sqrt(n)", "n^0.51", "n*log2(n)",
        "n^2 - 324", "100n^2 + 6n", "2n^3", "n^(log2(n))", "3^n", "2^n"
    };


    printf("Enter start value of n: ");
    scanf("%d", &start);
    printf("Enter end value of n: ");
    scanf("%d", &end);
    printf("Enter step size: ");
    scanf("%d", &step);


    for (int n = start; n <= end; n += step) {
        double values[NUM_FUNCS] = {
            f1(n), f2(n), f3(n), f4(n), f5(n), f6(n),
            f7(n), f8(n), f9(n), f10(n), f11(n), f12(n)
        };

        double sum = 0.0;
        for (int i = 0; i < NUM_FUNCS; i++) {
            sum += values[i];
        }
        double avg = sum / NUM_FUNCS;

        
        double sorted_vals[NUM_FUNCS];
        char *sorted_names[NUM_FUNCS];

        for (int i = 0; i < NUM_FUNCS; i++) {
            sorted_vals[i] = values[i];
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

     
        printf("\n---------------------------------------------\n");
        printf("n = %d\nAverage of all functions = %.6e\n", n, avg);
        printf("\nIn increasing order:\n");

        for (int i = 0; i < NUM_FUNCS; i++) {
            const char *cmp;
            if (fabs(sorted_vals[i] - avg) < 1e-9)
                cmp = "= average";
            else if (sorted_vals[i] < avg)
                cmp = "< average";
            else
                cmp = "> average";

            printf("[%-15s] = %.6e   %s\n", sorted_names[i], sorted_vals[i], cmp);
        }
    }

    return 0;
}
