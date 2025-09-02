#include <stdio.h>
#include <math.h>

 // Declare functions as double
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
double f13 = HUGE_VAL;  // 3^n is too large

int main() {
    int n, start, end, step;

    // Input range of n values
    printf("Enter start value of n: ");
    scanf("%d", &start);
    printf("Enter end value of n: ");
    scanf("%d", &end);
    printf("Enter step size: ");
    scanf("%d", &step);

    double values[13] = {0};

    // Put them in arrays
        char *names[13] = {
            "1/n","log2(n)","12*sqrt(n)","sqrt(n)","n^0.51","50*sqrt(n)",
            "n*log2(n)","100n^2+6n","n^2-324","2n^3","2^32*n","n^(log2(n))","3^n"
        }; 


    for (n = start; n <= end; n += step) {
        double values[13] = {
            f1(n),f2(n),f3(n),f4(n),f5(n),f6(n),f7(n),f8(n),
            f9(n),f10(n),f11(n),f12(n),f13
        };
    }

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
        printf("\n Increasing order at n = %d \n", n-2);
        for (int i=0; i<13; i++) {
            if (values[i] == HUGE_VAL)
                printf("%s = very large\n", names[i]);
            else
                printf("%s = %.3e\n", names[i], values[i]);
        }    

    return 0;
}
