#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// ---------- STACKS ----------
char opStack[MAX];   // for operators
int opTop = -1;

int valStack[MAX];   // for values (during evaluation)
int valTop = -1;

// ---------- STACK FUNCTIONS ----------
void pushOp(char c) { opStack[++opTop] = c; }
char popOp() { return opTop >= 0 ? opStack[opTop--] : '\0'; }
char peekOp() { return opTop >= 0 ? opStack[opTop] : '\0'; }

void pushVal(int v) { valStack[++valTop] = v; }
int popVal() { return valTop >= 0 ? valStack[valTop--] : 0; }

// ---------- PRECEDENCE ----------
int precedence(char c) {
    switch (c) {
        case '*': case '/': return 2;
        case '+': case '-': return 1;
        default: return -1;
    }
}

// ---------- INFIX TO POSTFIX ----------
void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isdigit(ch)) { 
            postfix[k++] = ch;
        }
        else if (ch == '(') {
            pushOp(ch);
        }
        else if (ch == ')') {
            while (opTop != -1 && peekOp() != '(') {
                postfix[k++] = popOp();
            }
            if (opTop != -1 && peekOp() == '(')
                popOp(); // remove '('
        }
        else { // operator
            while (opTop != -1 && precedence(ch) <= precedence(peekOp())) {
                if (peekOp() == '(') break;
                postfix[k++] = popOp();
            }
            pushOp(ch);
        }
    }

    while (opTop != -1) {
        postfix[k++] = popOp();
    }

    postfix[k] = '\0';
}

// ---------- EVALUATE POSTFIX ----------
int evaluatePostfix(char postfix[]) {
    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isdigit(ch)) {
            pushVal(ch - '0');  // convert char to int
        } else {
            int val2 = popVal();
            int val1 = popVal();
            switch (ch) {
                case '+': pushVal(val1 + val2); break;
                case '-': pushVal(val1 - val2); break;
                case '*': pushVal(val1 * val2); break;
                case '/': pushVal(val1 / val2); break;
            }
        }
    }
    return popVal();
}

// ---------- MAIN ----------
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    char postfix[MAX];
    infixToPostfix(argv[1], postfix);

    printf("Infix:   %s\n", argv[1]);
    printf("Postfix: %s\n", postfix);
    printf("Result:  %d\n", evaluatePostfix(postfix));

    return 0;

}
