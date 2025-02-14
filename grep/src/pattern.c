#include "pattern.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char* pattern_case_insensitive_find(const char *haystack, const char *needle) {
    if (haystack == NULL || needle == NULL) {
        return NULL;
    }

    size_t haystack_len = strlen(haystack);
    size_t needle_len = strlen(needle);

    if (needle_len > haystack_len) {
        return NULL;
    }

    for (size_t i = 0; i <= haystack_len - needle_len; i++) {
        int match = 1;
        for (size_t j = 0; j < needle_len; j++) {
            if (tolower((unsigned char)haystack[i + j]) != tolower((unsigned char)needle[j])) {
                match = 0;
                break;
            }
        }
        if (match) return haystack + i; // Zeiger auf den ersten Treffer
    }

    return NULL;
}


int pattern_match(const char *line, const char *pattern, int ignore_case, int invert_match) {
    int found = ignore_case
                    ? pattern_case_insensitive_find(line, pattern) != NULL
                    : strstr(line, pattern) != NULL;

    return invert_match ? !found : found;
}

