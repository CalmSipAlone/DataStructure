#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_VARS 10
#define MAX_NAME 21

int is_keyword(const char *w) {
    static const char *kw[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "main", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };
    int n = sizeof(kw) / sizeof(kw[0]);
    for (int i = 0; i < n; i++)
        if (strcmp(w, kw[i]) == 0) return 1;
    return 0;
}

int main() {
    FILE *fp = fopen("int.c", "r");
    if (!fp) return 1;

    char vars[MAX_VARS][MAX_NAME];
    int used[MAX_VARS] = {0};
    int nv = 0, in_def = 0;

    char word[MAX_NAME];
    int wi = 0, c;

    while ((c = fgetc(fp)) != EOF) {
        if (isalpha(c)) {
            if (wi < MAX_NAME - 1) word[wi++] = c;
        } else {
            // end of a word
            if (wi > 0) {
                word[wi] = '\0';
                wi = 0;

                if (strcmp(word, "int") == 0) {
                    in_def = 1;                     // start of definition
                } else if (in_def) {
                    if (!is_keyword(word)) {
                        strcpy(vars[nv++], word);   // collect variable name
                    }
                } else {
                    // check if this word is a used variable
                    if (!is_keyword(word)) {
                        for (int i = 0; i < nv; i++)
                            if (strcmp(word, vars[i]) == 0) {
                                used[i] = 1;
                                break;
                            }
                    }
                }
            }

            if (c == ';' && in_def) {
                in_def = 0;                         // end of definition
            }
        }
    }

    fclose(fp);

    for (int i = 0; i < nv; i++)
        if (!used[i]) printf("%s\n", vars[i]);

    return 0;
}
