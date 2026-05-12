#include <stdio.h>

#define SIZE 19

int chess[SIZE][SIZE];

int inBoard(int r, int c) {
    return r >= 0 && r < SIZE && c >= 0 && c < SIZE;
}

int checkLiveFour(int r, int c) {
    int color = chess[r][c];

    // ==================== 方向1：水平向右 → ====================
    if (inBoard(r, c+3) &&
        chess[r][c+1] == color &&
        chess[r][c+2] == color &&
        chess[r][c+3] == color)
    {
        int right = inBoard(r, c+4) && chess[r][c+4] == 0;
        int left  = inBoard(r, c-1) && chess[r][c-1] == 0;
        if (right || left) return color;
    }

    // ==================== 方向2：垂直向下 ↓ ====================
    if (inBoard(r+3, c) &&
        chess[r+1][c] == color &&
        chess[r+2][c] == color &&
        chess[r+3][c] == color)
    {
        int down = inBoard(r+4, c) && chess[r+4][c] == 0;
        int up   = inBoard(r-1, c) && chess[r-1][c] == 0;
        if (down || up) return color;
    }

    // ==================== 方向3：右下斜 ↘ ====================
    if (inBoard(r+3, c+3) &&
        chess[r+1][c+1] == color &&
        chess[r+2][c+2] == color &&
        chess[r+3][c+3] == color)
    {
        int dr = inBoard(r+4, c+4) && chess[r+4][c+4] == 0;
        int ul = inBoard(r-1, c-1) && chess[r-1][c-1] == 0;
        if (dr || ul) return color;
    }

    // ==================== 方向4：左下斜 ↙ ====================
    if (inBoard(r+3, c-3) &&
        chess[r+1][c-1] == color &&
        chess[r+2][c-2] == color &&
        chess[r+3][c-3] == color)
    {
        int dl = inBoard(r+4, c-4) && chess[r+4][c-4] == 0;  // 左下端
        int ur = inBoard(r-1, c+1) && chess[r-1][c+1] == 0;  // 右上端
        if (dl || ur) return color;
    }

    return 0;
}

int main() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &chess[i][j]);
        }
    }


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (chess[i][j] == 0) continue; 

            int res = checkLiveFour(i, j);
            if (res != 0) {
                printf("%d:%d,%d\n", res, i+1, j+1);
                return 0;
            }
        }
    }

    printf("No\n");
    return 0;
}