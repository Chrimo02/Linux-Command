#ifndef OPTIONS_H
#define OPTIONS_H

#define MAX_FILES 100

typedef struct {
    int ignore_case;
    int invert_match;
    int recursive;
    const char *pattern;
    const char *files[MAX_FILES];
    int file_count;
} options_t;

void parse_arguments(int argc, char *argv[], options_t *options);

#endif // OPTIONS_H