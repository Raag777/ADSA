#include <stdio.h>
#include <math.h>

int main() {
    int n, start, end, step;

    // Input range of n values
    printf("Enter start value of n: ");
    scanf("%d", &start);
    printf("Enter end value of n: ");
    scanf("%d", &end);
    printf("Enter step size: ");
    scanf("%d", &step);

    for (n = start; n <= end; n += step) {
        // Declare functions as double
        double f1 = 1.0/n;
        double f2 = log2(n);
        double f3 = 12*sqrt(n);
        double f4 = sqrt(n);
        double f5 = pow(n, 0.51);
        double f6 = 50*sqrt(n);
        double f7 = n*log2(n);
        double f8 = 100.0*n*n + 6*n;
        double f9 = (double)n*n - 324;
        double f10 = 2*pow(n,3);
        double f11 = pow(2,32)*n;
        double f12 = pow(n, log2(n));
        double f13 = HUGE_VAL;  // 3^n is too large

        // Put them in arrays
        double values[13] = {f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13};
        char *names[13] = {
            "1/n","log2(n)","12*sqrt(n)","sqrt(n)","n^0.51","50*sqrt(n)",
            "n*log2(n)","100n^2+6n","n^2-324","2n^3","2^32*n","n^(log2(n))","3^n"
        };

        // Sort using simple bubble sort
        for (int i=0; i<13; i++) {
            for (int j=i+1; j<13; j++) {
                if (values[i] > values[j]) {
                    double tempVal = values[i];
                    values[i] = values[j];
                    values[j] = tempVal;

                    char *tempName = names[i];
                    names[i] = names[j];
                    names[j] = tempName;
                }
            }
        }

        // Print result
        printf("\n===== At n = %d =====\n", n);
        for (int i=0; i<13; i++) {
            if (values[i] == HUGE_VAL)
                printf("%s = very large\n", names[i]);
            else
                printf("%s = %.3e\n", names[i], values[i]);
        }
    }

    return 0;
}
