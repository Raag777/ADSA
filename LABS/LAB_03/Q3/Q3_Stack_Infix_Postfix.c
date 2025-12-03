#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100


// STACK for characters (operators)

typedef struct {
    char arr[MAX];
    int top;
} CharStack;

void initCharStack(CharStack *s) { s->top = -1; }
int isCharEmpty(CharStack *s) { return s->top == -1; }
int isCharFull(CharStack *s) { return s->top == MAX - 1; }
void pushChar(CharStack *s, char ch) { if (!isCharFull(s)) s->arr[++s->top] = ch; }
char popChar(CharStack *s) { return isCharEmpty(s) ? '\0' : s->arr[s->top--]; }
char peekChar(CharStack *s) { return isCharEmpty(s) ? '\0' : s->arr[s->top]; }


// STACK for integers (evaluation)

typedef struct {
    int arr[MAX];
    int top;
} IntStack;

void initIntStack(IntStack *s) { s->top = -1; }
int isIntEmpty(IntStack *s) { return s->top == -1; }
void pushInt(IntStack *s, int x) { s->arr[++s->top] = x; }
int popInt(IntStack *s) { return s->arr[s->top--]; }


// Priority of operators

int precedence(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    return 0;
}


// INFIX TO POSTFIX CONVERSION

void infixToPostfix(char infix[], char postfix[]) {
    CharStack s;
    initCharStack(&s);

    int k = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isspace(ch)) continue;  // ignore spaces

        // Operand (letter or digit)
        if (isalnum(ch)) {
            postfix[k++] = ch;
        }
        else if (ch == '(') {
            pushChar(&s, ch);
        }
        else if (ch == ')') {
            while (!isCharEmpty(&s) && peekChar(&s) != '(')
                postfix[k++] = popChar(&s);
            popChar(&s); // pop '('
        }
        else { // Operator
            while (!isCharEmpty(&s) && precedence(peekChar(&s)) >= precedence(ch))
                postfix[k++] = popChar(&s);
            pushChar(&s, ch);
        }
    }

    while (!isCharEmpty(&s))
        postfix[k++] = popChar(&s);

    postfix[k] = '\0';
}


// EVALUATE POSTFIX EXPRESSION

int evaluatePostfix(char postfix[]) {
    IntStack s;
    initIntStack(&s);

    int values[26];          // A–Z variable values
    int used[26] = {0};

    // First pass: ask user only once per variable
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalpha(postfix[i])) {
            int id = toupper(postfix[i]) - 'A';
            if (!used[id]) {
                printf("Enter value for %c: ", postfix[i]);
                scanf("%d", &values[id]);
                used[id] = 1;
            }
        }
    }

    // Second pass: evaluation
    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isdigit(ch)) {
            pushInt(&s, ch - '0');
        }
        else if (isalpha(ch)) {
            pushInt(&s, values[toupper(ch) - 'A']);
        }
        else {
            int b = popInt(&s);
            int a = popInt(&s);

            switch (ch) {
                case '+': pushInt(&s, a + b); break;
                case '-': pushInt(&s, a - b); break;
                case '*': pushInt(&s, a * b); break;
                case '/': pushInt(&s, a / b); break;
            }
        }
    }
    return popInt(&s);
}


// MAIN PROGRAM

#ifndef TEST_MODE
int main() {
    char infix[100], postfix[100];

    printf("Enter infix expression: ");
    fgets(infix, sizeof(infix), stdin);

    infixToPostfix(infix, postfix);

    printf("\nPostfix Expression: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Postfix Evaluation Result: %d\n", result);

    return 0;
}
#endif
