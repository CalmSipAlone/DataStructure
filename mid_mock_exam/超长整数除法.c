#include <stdio.h>
#include <string.h>

#define MAX 202  // enough for 80-digit intermediate operations

// Remove leading zeros in-place, return pointer to first non-zero
char *strip_zeros(char *s) {
    while (*s == '0' && *(s + 1)) s++;
    return s;
}

// Compare big integers as strings: return 1 if a>b, 0 if equal, -1 if a<b
int cmp(const char *a, const char *b) {
    int la = strlen(a), lb = strlen(b);
    if (la != lb) return la > lb ? 1 : -1;
    return strcmp(a, b);
}

// Subtract b from a (a >= b), result written back to a
void sub(char *a, const char *b) {
    int la = strlen(a), lb = strlen(b);
    int borrow = 0;
    for (int i = 0; i < lb; i++) {
        int d = (a[la - 1 - i] - '0') - (b[lb - 1 - i] - '0') - borrow;
        if (d < 0) { d += 10; borrow = 1; }
        else borrow = 0;
        a[la - 1 - i] = d + '0';
    }
    for (int i = lb; borrow && i < la; i++) {
        int d = a[la - 1 - i] - '0' - 1;
        if (d < 0) { d += 10; }
        else borrow = 0;
        a[la - 1 - i] = d + '0';
    }
    // remove leading zeros
    char *p = strip_zeros(a);
    if (p != a) memmove(a, p, strlen(p) + 1);
}

// Multiply big integer string a by single digit d (0-9), store in res
void mul_digit(const char *a, int d, char *res) {
    if (d == 0 || strcmp(a, "0") == 0) { strcpy(res, "0"); return; }
    if (d == 1) { strcpy(res, a); return; }

    int len = strlen(a);
    char tmp[MAX] = "";
    int carry = 0, k = 0;

    for (int i = len - 1; i >= 0; i--) {
        int prod = (a[i] - '0') * d + carry;
        tmp[k++] = (prod % 10) + '0';
        carry = prod / 10;
    }
    while (carry) {
        tmp[k++] = (carry % 10) + '0';
        carry /= 10;
    }

    for (int i = 0; i < k; i++)
        res[i] = tmp[k - 1 - i];
    res[k] = '\0';
}

int main() {
    char num1[MAX], num2[MAX];
    fgets(num1, sizeof(num1), stdin);
    fgets(num2, sizeof(num2), stdin);
    num1[strcspn(num1, "\r\n")] = '\0';
    num2[strcspn(num2, "\r\n")] = '\0';

    char *dividend = strip_zeros(num1);
    char *divisor  = strip_zeros(num2);

    // 0 as divisor (should not happen in valid test)
    if (strcmp(divisor, "0") == 0) return 1;

    // if dividend < divisor, quotient is 0
    if (cmp(dividend, divisor) < 0) {
        printf("0\n");
        return 0;
    }

    int len_d = strlen(dividend);
    char remainder[MAX] = "";
    char quotient[MAX]  = "";
    int qi = 0;
    int rlen = 0;

    for (int i = 0; i < len_d; i++) {
        // bring down next digit
        remainder[rlen++] = dividend[i];
        remainder[rlen] = '\0';
        char *rp = strip_zeros(remainder);
        if (rp != remainder) {
            memmove(remainder, rp, strlen(rp) + 1);
            rlen = strlen(remainder);
        }

        // find quotient digit (trial 9..0)
        int qd = 0;
        char prod[MAX];
        for (int d = 9; d >= 0; d--) {
            mul_digit(divisor, d, prod);
            if (cmp(remainder, prod) >= 0) {
                qd = d;
                break;
            }
        }

        quotient[qi++] = qd + '0';

        // subtract
        mul_digit(divisor, qd, prod);
        sub(remainder, prod);
        rlen = strlen(remainder);
    }

    quotient[qi] = '\0';
    printf("%s\n", strip_zeros(quotient));

    return 0;
}
