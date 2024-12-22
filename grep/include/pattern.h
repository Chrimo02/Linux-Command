#ifndef PATTERN_H
#define PATTERN_H

int case_insensitive_strstr(const char *haystack, const char *needle);
int pattern_match(const char *line, const char *pattern, int ignore_case, int invert_match);

#endif // PATTERN_H