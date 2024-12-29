#ifndef PATTERN_H
#define PATTERN_H

int pattern_match(const char *line, const char *pattern, int ignore_case, int invert_match);
const char* pattern_case_insensitive_find(const char *haystack, const char *needle);

#endif // PATTERN_H