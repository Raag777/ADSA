#include <stdio.h>
#include <string.h>

#define MAX 200

// Function to compute LPS array
void computeLPS(char pattern[], int m, int lps[]) {
    int len = 0;      // length of previous longest prefix suffix
    int i = 1;
    lps[0] = 0;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Search Function
void KMPsearch(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);

    int lps[m];
    computeLPS(pattern, m, lps);

    int i = 0, j = 0;
    int found = 0;

    printf("\nSearching occurrences...\n");

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
            found = 1;
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if (!found)
        printf("Pattern not found!\n");
}

#ifndef TEST_MODE

int main() {
    char text[MAX], pattern[MAX];
    int choice;

    while (1) {
        printf("\n===== KMP STRING MATCHING MENU =====\n");
        printf("1. Enter Text\n");
        printf("2. Enter Pattern\n");
        printf("3. Search Pattern in Text\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // to flush newline

        switch (choice) {
            case 1:
                printf("Enter text: ");
                fgets(text, MAX, stdin);
                text[strcspn(text, "\n")] = '\0';
                break;

            case 2:
                printf("Enter pattern: ");
                fgets(pattern, MAX, stdin);
                pattern[strcspn(pattern, "\n")] = '\0';
                break;

            case 3:
                if (strlen(text) == 0 || strlen(pattern) == 0)
                    printf("Please enter both text and pattern first.\n");
                else
                    KMPsearch(text, pattern);
                break;

            case 4:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
#endif
