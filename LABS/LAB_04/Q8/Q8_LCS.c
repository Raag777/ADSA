#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

int dp[MAX][MAX];  // DP table

//  Utility to store all LCS results 
typedef struct Node {
    char str[MAX];
    struct Node* next;
} Node;

Node* addToList(Node* head, const char* s) {
    Node* t = head;
    while (t != NULL) {
        if (strcmp(t->str, s) == 0)
            return head;
        t = t->next;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->str, s);
    newNode->next = head;
    return newNode;
}

//  Recursive collection of ALL LCS strings 
Node* getAllLCS(char* X, char* Y, int m, int n) {
    if (m == 0 || n == 0) {
        Node* head = NULL;
        head = addToList(head, "");
        return head;
    }

    if (X[m-1] == Y[n-1]) {
        Node* temp = getAllLCS(X, Y, m-1, n-1);
        Node* result = NULL;

        while (temp != NULL) {
            char newStr[MAX];
            sprintf(newStr, "%s%c", temp->str, X[m-1]);
            result = addToList(result, newStr);
            temp = temp->next;
        }
        return result;
    }

    Node* result = NULL;

    if (dp[m-1][n] >= dp[m][n-1]) {
        Node* temp = getAllLCS(X, Y, m-1, n);
        while (temp != NULL) {
            result = addToList(result, temp->str);
            temp = temp->next;
        }
    }

    if (dp[m][n-1] >= dp[m-1][n]) {
        Node* temp = getAllLCS(X, Y, m, n-1);
        while (temp != NULL) {
            result = addToList(result, temp->str);
            temp = temp->next;
        }
    }

    return result;
}

//  Compute LCS Length (exported) 
int computeLCSLength(const char* X, const char* Y) {
    int m = strlen(X), n = strlen(Y);

    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++) {
            dp[i][j] = (i == 0 || j == 0)
                ? 0
                : (X[i-1] == Y[j-1]
                    ? 1 + dp[i-1][j-1]
                    : (dp[i-1][j] > dp[i][j-1] ? dp[i-1][j] : dp[i][j-1]));
        }

    return dp[m][n];
}

//  Print ONE LCS 
void printOneLCS(char* X, char* Y, int m, int n) {
    char result[MAX];
    int index = 0;

    while (m > 0 && n > 0) {
        if (X[m-1] == Y[n-1]) {
            result[index++] = X[m-1];
            m--; n--;
        }
        else if (dp[m-1][n] > dp[m][n-1])
            m--;
        else
            n--;
    }

    result[index] = '\0';

    for (int i = 0; i < index/2; i++) {
        char t = result[i];
        result[i] = result[index-i-1];
        result[index-i-1] = t;
    }

    printf("One LCS: %s\n", result);
}

#ifndef TEST_MODE

int main() {
    char X[MAX], Y[MAX];

    printf("Enter first string: ");
    scanf("%s", X);

    printf("Enter second string: ");
    scanf("%s", Y);

    int m = strlen(X), n = strlen(Y);

    printf("\nLength of LCS = %d\n", computeLCSLength(X, Y));

    printOneLCS(X, Y, m, n);

    printf("\nAll LCS strings:\n");

    Node* list = getAllLCS(X, Y, m, n);
    Node* t = list;

    while (t != NULL) {
        printf("%s\n", t->str);
        t = t->next;
    }

    return 0;
}
#endif
