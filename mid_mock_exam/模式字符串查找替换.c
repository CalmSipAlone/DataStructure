#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PAT 20
#define MAX_REP 20

// case-insensitive character match
int ch_match(char a, char b) {
    return tolower((unsigned char)a) == tolower((unsigned char)b);
}

// check if character is in the bracket set
int in_bracket(char ch, const char *bracket, int len) {
    ch = tolower((unsigned char)ch);
    for (int i = 0; i < len; i++) {
        if (ch == tolower((unsigned char)bracket[i])) return 1;
    }
    return 0;
}

int main() {
    char pattern[MAX_PAT + 1];
    char replacement[MAX_REP + 1];
    char text[100000];

    // read pattern and replacement
    fgets(pattern, sizeof(pattern), stdin);
    fgets(replacement, sizeof(replacement), stdin);
    pattern[strcspn(pattern, "\r\n")] = '\0';
    replacement[strcspn(replacement, "\r\n")] = '\0';

    // read article
    int text_len = 0;
    char line[1000];
    while (fgets(line, sizeof(line), stdin)) {
        int len = strlen(line);
        if (text_len + len < (int)sizeof(text)) {
            memcpy(text + text_len, line, len + 1);
            text_len += len;
        }
    }

    // parse pattern: prefix [bracket] suffix
    char prefix[MAX_PAT + 1] = "";
    char bracket[MAX_PAT + 1] = "";
    char suffix[MAX_PAT + 1] = "";

    int pre_len = 0, brk_len = 0, suf_len = 0;
    int has_bracket = 0;
    int i, len = strlen(pattern);

    // read prefix
    for (i = 0; i < len && pattern[i] != '['; i++)
        prefix[pre_len++] = pattern[i];
    prefix[pre_len] = '\0';

    // read bracket content
    if (i < len && pattern[i] == '[') {
        has_bracket = 1;
        i++;  // skip '['
        while (i < len && pattern[i] != ']')
            bracket[brk_len++] = pattern[i++];
        bracket[brk_len] = '\0';
        if (i < len) i++;  // skip ']'
    }

    // read suffix
    while (i < len)
        suffix[suf_len++] = pattern[i++];
    suffix[suf_len] = '\0';

    int pat_len = pre_len + (has_bracket ? 1 : 0) + suf_len;

    // scan and replace
    int pos = 0;
    while (pos < text_len) {
        // check if pattern matches at current position
        if (pos + pat_len <= text_len) {
            int match = 1;

            // check prefix
            for (int j = 0; j < pre_len; j++) {
                if (!ch_match(text[pos + j], prefix[j])) { match = 0; break; }
            }

            // check bracket
            if (match && has_bracket) {
                if (!in_bracket(text[pos + pre_len], bracket, brk_len))
                    match = 0;
            }

            // check suffix
            if (match) {
                for (int j = 0; j < suf_len; j++) {
                    if (!ch_match(text[pos + pre_len + (has_bracket ? 1 : 0) + j], suffix[j]))
                    { match = 0; break; }
                }
            }

            if (match) {
                printf("%s", replacement);
                pos += pat_len;
                continue;
            }
        }

        putchar(text[pos]);
        pos++;
    }

    return 0;
}
