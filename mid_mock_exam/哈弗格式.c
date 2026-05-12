/**
 * 哈佛格式参考文献提取
 *
 * 思路：
 * 1. 逐字符扫描文本，遇到 '(' 进入引用提取模式
 * 2. 提取括号内的 "Author, Year" 字符串
 * 3. 解析出 author 和 year
 * 4. 查重：已出现过则跳过，否则加入列表
 * 5. 按首次出现顺序输出
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT 10000   // 文本最大长度
#define MAX_REF  100     // 最大参考文献数
#define MAX_NAME 31     // 作者姓名最大长度

// 存储一条参考文献
typedef struct {
    char author[MAX_NAME + 1];
    int  year;
} Reference;

/**
 * 判断 (author, year) 是否已经在 refs 中出现过
 * 返回下标（找到）或 -1（没找到）
 */
int find_ref(Reference refs[], int count, const char *author, int year) {
    for (int i = 0; i < count; i++) {
        if (refs[i].year == year && strcmp(refs[i].author, author) == 0) {
            return i;  // 找到了（同名同年）
        }
    }
    return -1;  // 没找到
}

int main() {
    char text[MAX_TEXT + 1];
    Reference refs[MAX_REF];   // 存放不重复的参考文献
    int ref_count = 0;         // 不重复的文献数量

    // 1. 读取整行文本（包含空格）
    if (fgets(text, sizeof(text), stdin) == NULL) {
        return 1;
    }

    // 去掉末尾的换行符（如果有）
    int len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
        len--;
    }

    // 2. 逐字符扫描，寻找 '('
    int i = 0;
    while (i < len) {
        if (text[i] == '(') {
            // 找到左括号，开始提取引用内容
            int start = i + 1;   // 引用内容的起始位置

            // 找匹配的右括号 ')'
            int j = start;
            while (j < len && text[j] != ')') {
                j++;
            }

            if (j < len) {
                // 提取括号内的字符串 "Author, Year"
                int cite_len = j - start;
                char citation[MAX_NAME + 10];  // 足够装 "Author, YYYY"

                if (cite_len < (int)sizeof(citation)) {
                    strncpy(citation, text + start, cite_len);
                    citation[cite_len] = '\0';

                    // 解析 author 和 year
                    // 格式: "Author, Year"
                    char *comma = strchr(citation, ',');
                    if (comma != NULL) {
                        *comma = '\0';           // 将逗号变成结束符
                        char *author = citation;  // author 指向逗号前
                        char *year_str = comma + 2;  // 跳过 ", " 指向年份

                        // 检查 year_str 是否是纯数字（跳过空格后）
                        char *py = year_str;
                        while (*py == ' ') py++;  // 跳过可能的空格

                        int year = atoi(py);

                        // 去重检查
                        if (find_ref(refs, ref_count, author, year) == -1) {
                            // 没出现过，加入列表
                            strncpy(refs[ref_count].author, author, MAX_NAME);
                            refs[ref_count].author[MAX_NAME] = '\0';  // 确保截断
                            refs[ref_count].year = year;
                            ref_count++;
                        }
                    }
                }
                i = j;  // 跳到右括号位置，i++后会到右括号下一个字符
            }
        }
        i++;
    }

    // 3. 按首次出现顺序输出
    for (int i = 0; i < ref_count; i++) {
        printf("%s %d\n", refs[i].author, refs[i].year);
    }

    return 0;
}
