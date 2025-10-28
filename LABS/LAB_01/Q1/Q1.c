#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* ======================= Your Functions ======================= */
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
double f12(int n) { return n * pow(2, 32); }

#define NUM_FUNCS 12

double (*funcs[NUM_FUNCS])(int) = {
    f1, f2, f3, f4, f5, f6,
    f7, f8, f9, f10, f11, f12
};

char *names[NUM_FUNCS] = {
    "f1(1/n)", "f2(log2(n))", "f3(12*sqrt(n))", "f4(50*sqrt(n))",
    "f5(n^0.51)", "f6(n*log2(n))", "f7(n^2-324)", "f8(100n^2+6n)",
    "f9(2n^3)", "f10(n^(log2(n)))", "f11(3^n)", "f12(n*2^32)"
};

/* ======================= Core Computation ======================= */
char* compute_ranking(int start, int end, int step) {
    static char output[4096];
    double sums[NUM_FUNCS] = {0};
    double avgs[NUM_FUNCS] = {0};
    int count = 0;

    for (int n = start; n <= end; n += step) {
        for (int i = 0; i < NUM_FUNCS; i++) {
            sums[i] += funcs[i](n);
        }
        count++;
    }

    for (int i = 0; i < NUM_FUNCS; i++) {
        avgs[i] = sums[i] / count;
    }

    // Print sums/averages
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

    // Ranking chain
    printf("\n---------------------------------------------\n");
    printf("Ranking of averages (in increasing order):\n\n");

    output[0] = '\0';
    for (int i = 0; i < NUM_FUNCS; i++) {
        strcat(output, sorted_names[i]);
        if (i < NUM_FUNCS - 1) strcat(output, " < ");
    }
    printf("%s\n", output);

    return output;
}

/* ======================= Embedded Minimal Munit ======================= */
typedef enum { MUNIT_OK, MUNIT_FAIL } MunitResult;
#define munit_assert(expr) if(!(expr)){fprintf(stderr,"Assertion failed: %s\n",#expr); return MUNIT_FAIL;}
#define munit_assert_not_null(ptr) munit_assert((ptr)!=NULL)
#define munit_assert_string_contains(str,sub) munit_assert(strstr((str),(sub))!=NULL)

/* ======================= Tests ======================= */
MunitResult test_small_range() {
    char* result = compute_ranking(1, 5, 1);
    munit_assert_not_null(result);
    munit_assert_string_contains(result, "f1(1/n)");
    return MUNIT_OK;
}

MunitResult test_step_range() {
    char* result = compute_ranking(10, 50, 10);
    munit_assert_not_null(result);
    munit_assert_string_contains(result, "f12(n*2^32)");
    return MUNIT_OK;
}

MunitResult test_ordering() {
    char* result = compute_ranking(2, 4, 1);
    munit_assert_string_contains(result, "<"); // must have ordering
    return MUNIT_OK;
}

void run_all_tests() {
    printf("Running test: small-range\n");
    if (test_small_range() == MUNIT_OK) printf("✅ Passed\n\n");

    printf("Running test: step-range\n");
    if (test_step_range() == MUNIT_OK) printf("✅ Passed\n\n");

    printf("Running test: ordering\n");
    if (test_ordering() == MUNIT_OK) printf("✅ Passed\n\n");

    printf("All tests finished.\n");
}

/* ======================= Interactive Mode ======================= */
void run_interactive() {
    int start, end, step;
    printf("Enter start value of n: ");
    scanf("%d", &start);
    printf("Enter end value of n: ");
    scanf("%d", &end);
    printf("Enter step size: ");
    scanf("%d", &step);

    compute_ranking(start, end, step);
}

/* ======================= Main ======================= */
int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "test") == 0) {
        run_all_tests();
    } else {
        run_interactive();
    }
    return 0;
}
