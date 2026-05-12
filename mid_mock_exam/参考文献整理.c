#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_REF 100
#define MAX_LINE 512

typedef struct {
    int id;
    char *authors;
    int year;
    char *title;
    char *proceedings;
    int input_order;
} Reference;

// ---------- helper functions ----------

char *str_dup(const char *s) {
    char *copy = (char*)malloc(strlen(s) + 1);
    strcpy(copy, s);
    return copy;
}

// trim leading and trailing whitespace in-place, returns pointer
char *trim(char *s) {
    while (isspace((unsigned char)*s)) s++;
    if (*s == '\0') return s;
    char *end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
    return s;
}

// capitalize first letter of each word (split by space or hyphen)
void capitalize_name(char *name) {
    if (name[0] == '\0') return;
    // capitalize first character
    name[0] = toupper((unsigned char)name[0]);
    // handle hyphens: if a '-' is found, capitalize next char
    for (char *p = name; *p; p++) {
        if (*p == '-' && *(p + 1)) {
            *(p + 1) = toupper((unsigned char)*(p + 1));
        }
    }
}

// Format a single author name: trim and capitalize each part
char *format_single_author(const char *raw) {
    char buf[MAX_LINE];
    strcpy(buf, raw);
    char *trimmed = trim(buf);
    if (*trimmed == '\0') return str_dup("");

    // Tokenize by spaces, capitalize each token, rebuild
    char result[MAX_LINE] = "";
    char *token = strtok(trimmed, " \t");
    while (token) {
        capitalize_name(token);
        if (result[0] != '\0') strcat(result, " ");
        strcat(result, token);
        token = strtok(NULL, " \t");
    }
    return str_dup(result);
}

// ---------- authors parsing ----------

// Parse raw author string, produce formatted authors string and first author name
void parse_authors(const char *raw, char **authors_out, char **first_author_out) {
    char buf[MAX_LINE];
    strcpy(buf, raw);
    char *trimmed = trim(buf);

    // Step 1: replace all " and " with ","
    char *p = trimmed;
    while ((p = strstr(p, " and ")) != NULL) {
        // replace " and " (5 chars) with "," (1 char)
        *p = ',';
        memmove(p + 1, p + 5, strlen(p + 5) + 1);
    }

    // Step 2: split by "," to get individual author name strings
    char *tokens[MAX_REF];
    int n = 0;
    p = strtok(trimmed, ",");
    while (p && n < MAX_REF) {
        tokens[n++] = p;
        p = strtok(NULL, ",");
    }

    if (n == 0) {
        *authors_out = str_dup("");
        *first_author_out = str_dup("");
        return;
    }

    // Step 3: format each author name
    char *formatted[MAX_REF];
    for (int i = 0; i < n; i++) {
        formatted[i] = format_single_author(tokens[i]);
    }

    // Step 4: save first author for sorting
    *first_author_out = str_dup(formatted[0]);

    // Step 5: build formatted authors string
    char result[MAX_LINE] = "";
    if (n == 1) {
        strcpy(result, formatted[0]);
    } else if (n == 2) {
        sprintf(result, "%s and %s", formatted[0], formatted[1]);
    } else {
        // 3+ authors: A, B, C and D  (no Oxford comma)
        int pos = 0;
        // first author (no leading comma+space)
        int len0 = strlen(formatted[0]);
        memcpy(result + pos, formatted[0], len0);
        pos += len0;
        // middle authors: ", name"
        for (int i = 1; i < n - 1; i++) {
            result[pos++] = ',';
            result[pos++] = ' ';
            int len = strlen(formatted[i]);
            memcpy(result + pos, formatted[i], len);
            pos += len;
        }
        result[pos] = '\0';
        strcat(result, " and ");
        strcat(result, formatted[n - 1]);
    }

    *authors_out = str_dup(result);

    // free temporary formatted strings
    for (int i = 0; i < n; i++) free(formatted[i]);
}

// ---------- line parsing ----------

// Find year in line, extract parts.
// Returns 1 on success, 0 on failure.
int parse_line(const char *line, char **authors_raw, int *year,
               char **title, char **proceedings) {
    // Find pattern: . followed by optional spaces, then 4 digits (year), then .
    const char *p = line;
    while ((p = strchr(p, '.')) != NULL) {
        const char *after = p + 1;
        while (*after == ' ') after++;
        if (isdigit((unsigned char)after[0]) && isdigit((unsigned char)after[1]) &&
            isdigit((unsigned char)after[2]) && isdigit((unsigned char)after[3])) {
            // Skip optional spaces between year digits and trailing '.'
            const char *after_year = after + 4;
            while (*after_year == ' ') after_year++;
            if (*after_year != '.') {
                p = after_year;
                continue;
            }
            // Found year
            *year = (after[0] - '0') * 1000 + (after[1] - '0') * 100 +
                    (after[2] - '0') * 10 + (after[3] - '0');

            // Extract authors (everything before this '.')
            int auth_len = p - line;
            char *auth_buf = (char*)malloc(auth_len + 1);
            strncpy(auth_buf, line, auth_len);
            auth_buf[auth_len] = '\0';
            *authors_raw = str_dup(trim(auth_buf));
            free(auth_buf);

            // Extract rest (after "YYYY.")
            const char *rest_start = after_year + 1; // skip "YYYY."
            while (*rest_start == ' ') rest_start++;
            // Some inputs have extra ". " separator between year and title
            if (*rest_start == '.') {
                rest_start++;
                while (*rest_start == ' ') rest_start++;
            }
            char rest_buf[MAX_LINE];
            strcpy(rest_buf, rest_start);
            char *rest_trimmed = trim(rest_buf);

            // Split rest into title and proceedings.
            // Find ". " followed by "In " (robust to spacing variations)
            char *in_split = NULL;
            for (char *s = rest_trimmed; *s; s++) {
                if (*s == '.') {
                    char *t = s + 1;
                    while (*t == ' ') t++;
                    if (*t == 'I' && *(t + 1) == 'n' && *(t + 2) == ' ') {
                        in_split = s;
                        break;
                    }
                }
            }
            if (in_split) {
                *in_split = '\0';
                *title = str_dup(trim(rest_trimmed));
                char *proc = in_split + 1; // " In ..."
                while (*proc == ' ') proc++;
                char *proc_trimmed = proc;
                // Remove trailing '.'
                int len = strlen(proc_trimmed);
                if (len > 0 && proc_trimmed[len - 1] == '.')
                    proc_trimmed[len - 1] = '\0';
                *proceedings = str_dup(trim(proc_trimmed));
            } else {
                *title = str_dup(rest_trimmed);
                *proceedings = str_dup("");
            }

            // Capitalize first letter of title and strip trailing period
            if (**title) {
                **title = toupper((unsigned char)**title);
                int tlen = strlen(*title);
                if (tlen > 0 && (*title)[tlen - 1] == '.')
                    (*title)[tlen - 1] = '\0';
            }

            return 1;
        }
        p = after;  // continue searching
    }
    return 0;
}

// ---------- sorting ----------

int cmp_ref(const void *a, const void *b) {
    const Reference *ra = (const Reference*)a;
    const Reference *rb = (const Reference*)b;
    // year descending
    if (ra->year != rb->year)
        return rb->year - ra->year;
    // same year: compare first author name
    // We need to extract first author from authors string for comparison
    // Compare up to first " and " or "," to get first author
    char fa_a[MAX_LINE], fa_b[MAX_LINE];

    const char *end_a = NULL;
    const char *and_a = strstr(ra->authors, " and ");
    const char *comma_a = strchr(ra->authors, ',');
    if (and_a && comma_a)
        end_a = (and_a < comma_a) ? and_a : comma_a;
    else if (and_a)
        end_a = and_a;
    else if (comma_a)
        end_a = comma_a;
    if (end_a) {
        int len = end_a - ra->authors;
        strncpy(fa_a, ra->authors, len);
        fa_a[len] = '\0';
    } else {
        strcpy(fa_a, ra->authors);
    }

    const char *end_b = NULL;
    const char *and_b = strstr(rb->authors, " and ");
    const char *comma_b = strchr(rb->authors, ',');
    if (and_b && comma_b)
        end_b = (and_b < comma_b) ? and_b : comma_b;
    else if (and_b)
        end_b = and_b;
    else if (comma_b)
        end_b = comma_b;
    if (end_b) {
        int len = end_b - rb->authors;
        strncpy(fa_b, rb->authors, len);
        fa_b[len] = '\0';
    } else {
        strcpy(fa_b, rb->authors);
    }

    int name_cmp = strcmp(fa_a, fa_b);
    if (name_cmp != 0) return name_cmp;
    // same first author: input order
    return ra->input_order - rb->input_order;
}

// ---------- main ----------

int main() {
    Reference refs[MAX_REF];
    int count = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), stdin)) {
        // Remove trailing newline/carriage return
        line[strcspn(line, "\r\n")] = '\0';
        // Skip empty lines
        if (line[0] == '\0') continue;

        // Strip leading/trailing spaces for processing
        char *trimmed_line = trim(line);
        if (*trimmed_line == '\0') continue;

        char *authors_raw = NULL;
        int year = 0;
        char *title = NULL;
        char *proceedings = NULL;

        if (!parse_line(trimmed_line, &authors_raw, &year, &title, &proceedings)) {
            continue;
        }

        // Format authors
        char *authors_formatted = NULL;
        char *first_author = NULL;
        parse_authors(authors_raw, &authors_formatted, &first_author);

        // Store
        refs[count].id = count + 1;
        refs[count].authors = authors_formatted;
        refs[count].year = year;
        refs[count].title = title;
        refs[count].proceedings = proceedings;
        refs[count].input_order = count;
        count++;

        free(authors_raw);
        // first_author was used only during parse_authors, authors_formatted is what we need
        // Actually parse_authors allocated first_author but we didn't use it outside
        // Let's fix: I need first_author for sorting too.
        // But I'm extracting first author in cmp_ref, so I don't need to store it.
        free(first_author);

        if (count >= MAX_REF) break;
    }

    // Sort
    qsort(refs, count, sizeof(Reference), cmp_ref);

    // Output
    for (int i = 0; i < count; i++) {
        printf("[%d] %s. %d. %s. %s.\n",
               i + 1,
               refs[i].authors,
               refs[i].year,
               refs[i].title,
               refs[i].proceedings);
    }

    // Free memory
    for (int i = 0; i < count; i++) {
        free(refs[i].authors);
        free(refs[i].title);
        free(refs[i].proceedings);
    }

    return 0;
}
