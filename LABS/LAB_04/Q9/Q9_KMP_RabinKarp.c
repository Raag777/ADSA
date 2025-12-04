#include <stdio.h>
#include <string.h>
#include <math.h>

#define d 256          // Number of characters in input alphabet (for Rabin-Karp)
#define q 101          // A prime number used for hashing


// KMP (Knuth–Morris–Pratt)

// Build LPS (Longest Prefix Suffix) array
void computeLPS(char* pattern, int m, int lps[]) {
    int len = 0;  
    lps[0] = 0;   
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Search
void KMP(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int lps[m];
    computeLPS(pattern, m, lps);

    int i = 0, j = 0;

    printf("\nKMP Matches found at positions: ");

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++; j++;
        }

        if (j == m) {
            printf("%d ", i - j);
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pattern[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    printf("\n");
}


//  Rabin–Karp Algorithm

void RabinKarp(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    int h = 1;  
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    int p = 0;  
    int t = 0;  

    // Initial hash values
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    printf("\nRabin-Karp Matches found at positions: ");

    for (int i = 0; i <= n - m; i++) {

        // Check hash first
        if (p == t) {
            int match = 1;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = 0;
                    break;
                }
            }
            if (match)
                printf("%d ", i);
        }

        // Rolling hash update
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0)
                t += q;
        }
    }

    printf("\n");
}

#ifndef TEST_MODE

int main() {
    char text[500], pattern[100];

    printf("Enter text string: ");
    scanf("%s", text);

    printf("Enter pattern string: ");
    scanf("%s", pattern);

    printf("\n-----------------------------");
    printf("\nKnuth-Morris-Pratt (KMP) Algorithm");
    printf("\n-----------------------------");
    KMP(text, pattern);

    printf("\n-----------------------------");
    printf("\nRabin-Karp Fingerprinting Algorithm");
    printf("\n-----------------------------");
    RabinKarp(text, pattern);

    return 0;
}
#endif
