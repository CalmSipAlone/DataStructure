#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

// operator precedence
int prec(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// apply operator to two operands
double apply(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

int main() {
    char expr[MAX];
    char postfix[MAX][MAX];    // postfix tokens
    int  post_len = 0;

    // read entire expression (including spaces)
    fgets(expr, sizeof(expr), stdin);

    // ----- infix to postfix (shunting-yard) -----
    char op_stack[MAX];
    int  op_top = -1;

    int i = 0;
    while (expr[i] != '=' && expr[i] != '\0') {
        if (isspace((unsigned char)expr[i])) {
            i++;
            continue;
        }

        if (isdigit((unsigned char)expr[i])) {
            // parse number
            int j = 0;
            while (isdigit((unsigned char)expr[i]))
                postfix[post_len][j++] = expr[i++];
            postfix[post_len][j] = '\0';
            post_len++;
            continue;
        }

        // operator or parenthesis
        if (expr[i] == '(') {
            op_stack[++op_top] = '(';
        } else if (expr[i] == ')') {
            while (op_top >= 0 && op_stack[op_top] != '(') {
                postfix[post_len][0] = op_stack[op_top--];
                postfix[post_len][1] = '\0';
                post_len++;
            }
            if (op_top >= 0) op_top--; // discard '('
        } else {
            // operator: +, -, *, /
            while (op_top >= 0 && op_stack[op_top] != '(' &&
                   prec(op_stack[op_top]) >= prec(expr[i])) {
                postfix[post_len][0] = op_stack[op_top--];
                postfix[post_len][1] = '\0';
                post_len++;
            }
            op_stack[++op_top] = expr[i];
        }
        i++;
    }

    // pop remaining operators
    while (op_top >= 0) {
        postfix[post_len][0] = op_stack[op_top--];
        postfix[post_len][1] = '\0';
        post_len++;
    }

    // ----- evaluate postfix -----
    double val_stack[MAX];
    int val_top = -1;

    for (int k = 0; k < post_len; k++) {
        if (isdigit((unsigned char)postfix[k][0])) {
            val_stack[++val_top] = atof(postfix[k]);
        } else {
            double b = val_stack[val_top--];
            double a = val_stack[val_top--];
            val_stack[++val_top] = apply(a, b, postfix[k][0]);
        }
    }

    printf("%.2f\n", val_stack[0]);
    return 0;
}
