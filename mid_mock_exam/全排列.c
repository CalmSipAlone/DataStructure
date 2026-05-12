#include <stdio.h>

#define MAX_N 10

int n;              // 输入的数字个数
int path[MAX_N];    // 存储当前排列
int used[MAX_N + 1]; // 标记数字1~n是否已被使用

void dfs(int step) {
    if (step == n) {
        for (int i = 0; i < n; i++) {
            if (i > 0) putchar(' ');
            printf("%d", path[i]);
        }
        putchar('\n');
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = 1;
            path[step] = i;
            dfs(step + 1);
            used[i] = 0; // 回溯
        }
    }
}

int main() {
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "error: failed to read input\n");
        return 1;
    }
    if (n < 1 || n > MAX_N) {
        fprintf(stderr, "error: n must be in [1, %d]\n", MAX_N);
        return 1;
    }

    dfs(0);
    return 0;
}