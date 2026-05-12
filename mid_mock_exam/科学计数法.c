#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char input[55];
    fgets(input, 55, stdin);
    input[strcspn(input, "\r\n")] = '\0';

    char mantissa[55];          // 所有数字位（去掉小数点）
    int point_pos = 0;          // 原小数点前的位数
    int idx = 0, j = 0;
    int before_dot = 1;         // 正在读小数点前的部分

    // 读底数部分
    while (input[idx] != 'e' && input[idx] != 'E') {
        if (input[idx] == '.') {
            before_dot = 0;
            idx++;
            continue;
        }
        mantissa[j++] = input[idx];
        if (before_dot) point_pos++;
        idx++;
    }
    mantissa[j] = '\0';

    // 读指数部分
    idx++;  // 跳过 'e'/'E'
    int sign = 1;
    if (input[idx] == '+') idx++;
    else if (input[idx] == '-') { sign = -1; idx++; }
    int exp = 0;
    while (input[idx]) {
        exp = exp * 10 + (input[idx] - '0');
        idx++;
    }
    exp *= sign;

    int len = strlen(mantissa);
    int new_pos = point_pos + exp;   // 新的小数点位置

    if (new_pos <= 0) {
        // 小数点移到最左边甚至更左：前面补零
        printf("0.");
        for (int k = 0; k < -new_pos; k++) putchar('0');
        printf("%s", mantissa);
    } else if (new_pos < len) {
        // 小数点落在数字中间
        for (int k = 0; k < new_pos; k++) putchar(mantissa[k]);
        // 跳过小数部分末尾的 0
        int end = len;
        while (end > new_pos && mantissa[end - 1] == '0') end--;
        if (end > new_pos) {
            putchar('.');
            for (int k = new_pos; k < end; k++) putchar(mantissa[k]);
        }
    } else {
        // 小数点落在所有数字之后
        printf("%s", mantissa);
        for (int k = 0; k < new_pos - len; k++) putchar('0');
    }
    putchar('\n');

    return 0;
}
