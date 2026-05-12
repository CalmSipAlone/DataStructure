#include <stdio.h>
#include <string.h>

int calc(int a, int b, char ch) {
    switch (ch) {
        case '*': return a * b;
        case '/': 
            if (b == 0) { 
                printf("错误:除数不能为0!");
                return 0;
            }
            return a / b; 
        case '+': return a + b;
        case '-': return a - b;
        default: return 0;
    }
}

int num_stack[100]; 
char op_stack[100]; 
int num_top = 0;   
int op_top = -1;    

int main() {
    int num;
    char ch;
    scanf("%d", &num);
    num_stack[num_top++] = num;

    while (1) {
        while (scanf(" %c", &ch) == 1 && ch == ' ');
        op_stack[++op_top] = ch;

        if (ch == '=') break;

        scanf("%d", &num);
        num_stack[num_top++] = num;

        if (ch == '*' || ch == '/') {
            int b = num_stack[--num_top];
            int a = num_stack[--num_top];
            num_stack[num_top++] = calc(a, b, ch);
            op_top--;
        }
    }

    int res = num_stack[0];
    for (int i = 0; i < op_top; i++) {
        if (op_stack[i] == '+') {
            res += num_stack[i+1];
        } else if (op_stack[i] == '-') {
            res -= num_stack[i+1];
        }
    }

    printf("%d", res);
    return 0;
}