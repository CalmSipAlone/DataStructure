#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// ASCII可见字符范围：32(空格) ~ 126(~)，共固定95个字符
#define ASCII_MIN  32
#define ASCII_MAX  126
#define CHAR_COUNT 95  // 固定总字符数
#define MAX_KEY    33  // 密钥最长32个字符

int main() {
    // ===================== 1. 读取密钥 =====================
    char key[MAX_KEY];
    fgets(key, MAX_KEY, stdin);
    // 去除fgets读取的换行符
    key[strcspn(key, "\n")] = '\0';

    // ===================== 2. 密钥去重 =====================
    bool exist[128] = {false};  // 标记字符是否已存在
    char unique_key[CHAR_COUNT] = {0};
    int unique_len = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        char ch = key[i];
        // 只处理可见字符，且未重复
        if (ch >= ASCII_MIN && ch <= ASCII_MAX && !exist[(int)ch]) {
            exist[(int)ch] = true;
            unique_key[unique_len++] = ch;
        }
    }

    char ring[CHAR_COUNT];  // 模拟循环环的数组
    int ring_len = 0;
    // 第一步：放入去重后的密钥
    for (int i = 0; i < unique_len; i++) {
        ring[ring_len++] = unique_key[i];
    }
    // 第二步：按升序加入剩余的可见字符
    for (int ch = ASCII_MIN; ch <= ASCII_MAX; ch++) {
        if (!exist[ch]) {
            ring[ring_len++] = (char)ch;
        }
    }  
    char map[128] = {0};  
    char start_char = ring[0];  
    int pos = 0;               


    while (ring_len > 1) {
        char plain = ring[pos];
        int step = (int)plain;  

        for (int i = pos; i < ring_len - 1; i++) {
            ring[i] = ring[i + 1];
        }
        ring_len--;  

        if (pos >= ring_len) {
            pos = 0;  
        }

        pos = (pos + step - 1) % ring_len;

        char cipher = ring[pos];
        map[(int)plain] = cipher;
    }

    map[(int)ring[0]] = start_char;

    FILE *fin = fopen("in.txt", "r");
    FILE *fout = fopen("in_crpyt.txt", "w");
    if (fin == NULL || fout == NULL) {
        printf("文件打开失败！\n");
        return 1;
    }

    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        if (ch >= ASCII_MIN && ch <= ASCII_MAX) {
            fputc(map[ch], fout);
        } else {
            fputc(ch, fout);
        }
    }

    // 关闭文件
    fclose(fin);
    fclose(fout);

    return 0;
}