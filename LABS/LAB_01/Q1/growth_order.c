#include <stdio.h>
#include <math.h>
#include <string.h>
#include "growth_functions.c"

#define NUM_FUNCS 12

typedef struct {
    char name[20];
    double (*func)(double);
    double value;
} FuncInfo;

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

    for (int i = 0; i < num; i++)
        funcs[i].value = funcs[i].func(n);

    for (int i = 0; i < num - 1; i++)
        for (int j = 0; j < num - i - 1; j++)
            if (funcs[j].value > funcs[j + 1].value) {
                FuncInfo temp = funcs[j];
                funcs[j] = funcs[j + 1];
                funcs[j + 1] = temp;
            }

    printf("Function growth order (for n = %.0f):\n", n);
    for (int i = 0; i < num; i++)
        printf("%2d. %-10s  = %.2e\n", i + 1, funcs[i].name, funcs[i].value);

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
