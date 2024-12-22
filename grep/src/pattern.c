
#include "pattern.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "pattern.h"

int case_insensitive_strstr(const char *haystack, const char *needle) {
    size_t haystack_len = strlen(haystack);
    size_t needle_len = strlen(needle);
    for (size_t i = 0; i <= haystack_len - needle_len; i++) {
        int match = 1;
        for (size_t j = 0; j < needle_len; j++) {
            if (tolower(haystack[i + j]) != tolower(needle[j])) {
                match = 0;
                break;
            }
        }
        if (match) return 1;
    }
    return 0;
}

int pattern_match(const char *line, const char *pattern, int ignore_case, int invert_match) {
    int found = ignore_case ? case_insensitive_strstr(line, pattern) : strstr(line, pattern) != NULL;
    return invert_match ? !found : found;
}