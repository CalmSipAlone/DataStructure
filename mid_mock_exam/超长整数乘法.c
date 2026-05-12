#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 80

int main() {
    char num1[MAX_DIGITS + 3], num2[MAX_DIGITS + 3]; // 80 digits + \r\n + \0
    int a[MAX_DIGITS], b[MAX_DIGITS], res[MAX_DIGITS * 2];
    int len1, len2, i, j;

    // read input
    fgets(num1, sizeof(num1), stdin);
    fgets(num2, sizeof(num2), stdin);
    num1[strcspn(num1, "\r\n")] = '\0';
    num2[strcspn(num2, "\r\n")] = '\0';

    // strip leading zeros
    char *p1 = num1;
    while (*p1 == '0' && *(p1 + 1)) p1++;  // leave at least one digit
    char *p2 = num2;
    while (*p2 == '0' && *(p2 + 1)) p2++;

    len1 = strlen(p1);
    len2 = strlen(p2);

    // store digits in reverse order (least significant first)
    for (i = 0; i < len1; i++)
        a[i] = p1[len1 - 1 - i] - '0';
    for (i = 0; i < len2; i++)
        b[i] = p2[len2 - 1 - i] - '0';

    // initialize result to 0
    memset(res, 0, sizeof(res));

    // multiply
    for (i = 0; i < len1; i++) {
        for (j = 0; j < len2; j++) {
            res[i + j] += a[i] * b[j];
            res[i + j + 1] += res[i + j] / 10;
            res[i + j] %= 10;
        }
    }

    // find highest non-zero digit
    int res_len = len1 + len2;
    while (res_len > 1 && res[res_len - 1] == 0) res_len--;

    // output in reverse
    for (i = res_len - 1; i >= 0; i--)
        printf("%d", res[i]);
    printf("\n");

    return 0;
}
