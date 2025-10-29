#include <stdio.h>
#include <math.h>
#include <string.h>

#define NUM_FUNCS 12

//  Function Definitions 
double f1(double n) { return n * log2(n); }
double f2(double n) { return 12 * sqrt(n); }
double f3(double n) { return 1.0 / n; }
double f4(double n) { return pow(n, log2(n)); }
double f5(double n) { return 100 * n * n + 6 * n; }
double f6(double n) { return pow(n, 0.51); }
double f7(double n) { return n * n - 324; }
double f8(double n) { return 50 * sqrt(n); }
double f9(double n) { return 2 * pow(n, 3); }
double f10(double n) { return log2(n); }
double f11(double n) { return pow(3, n); }
double f12(double n) { return pow(2, 32) * n; }

//  Main Growth Order Program 
typedef struct {
    char name[20];
    double (*func)(double);
    double value;
} FuncInfo;

#ifdef MAIN_PROGRAM
int main() {
    double n = 1000.0;

    FuncInfo funcs[] = {
        {"n log2 n", f1, 0},
        {"12√n", f2, 0},
        {"1/n", f3, 0},
        {"n^(log n)", f4, 0},
        {"100n² + 6n", f5, 0},
        {"n^0.51", f6, 0},
        {"n² - 324", f7, 0},
        {"50√n", f8, 0},
        {"2n³", f9, 0},
        {"log₂n", f10, 0},
        {"3ⁿ", f11, 0},
        {"2³²n", f12, 0}
    };

    int num = sizeof(funcs) / sizeof(funcs[0]);

    // Evaluate each function
    for (int i = 0; i < num; i++)
        funcs[i].value = funcs[i].func(n);

    // Sort by growth value
    for (int i = 0; i < num - 1; i++)
        for (int j = 0; j < num - i - 1; j++)
            if (funcs[j].value > funcs[j + 1].value) {
                FuncInfo temp = funcs[j];
                funcs[j] = funcs[j + 1];
                funcs[j + 1] = temp;
            }

    // Display results
    printf("Function growth order (for n = %.0f):\n", n);
    for (int i = 0; i < num; i++)
        printf("%2d. %-12s = %.2e\n", i + 1, funcs[i].name, funcs[i].value);

    printf("\nPossible Θ-equivalent pairs:\n");
    printf(" - (12√n, 50√n)  => Θ(√n)\n");
    printf(" - (100n² + 6n, n² - 324)  => Θ(n²)\n");

    printf("\nChain form of increasing growth order:\n");
    for (int i = 0; i < num; i++) {
        printf("%s", funcs[i].name);
        if (i < num - 1) printf("  <  ");
    }
    printf("\n");

    return 0;
}
#endif
