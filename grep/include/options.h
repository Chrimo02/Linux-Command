#ifndef OPTIONS_H
#define OPTIONS_H

#define MAX_FILES 256

typedef struct {
    int ignore_case;   // -i
    int invert_match;  // -v
    int recursive;     // -r
    int show_line_number; // -n
    int count_matches; // -c
    char *pattern;
    char *files[MAX_FILES];
    int file_count;
} options_t;

// Externe Deklaration der globalen Variable
extern options_t options;

void parse_arguments(int argc, char *argv[], options_t *options);

#endif // OPTIONS_H
