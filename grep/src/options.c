#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_help() {
    printf("Usage: grep [OPTIONS] PATTERN [FILE...]\n");
    printf("Options:\n");
    printf("  -h          Display this help message and exit\n");
    printf("  -i          Ignore case distinctions\n");
    printf("  -v          Invert match\n");
    printf("  -c          Count matches\n");
    printf("  -n          Show line numbers with output\n");
    printf("  -r          Recursively search directories\n");
    printf("  [PATTERN]   Pattern to search for\n");
    printf("  [FILE...]   Files to search\n");
}

void parse_arguments(int argc, char *argv[], options_t *options) {
    memset(options, 0, sizeof(options_t));
    options->pattern = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-help") == 0) {
            options->show_help = 1;
            return;
        }
        if (strcmp(argv[i], "-i") == 0) {
            options->ignore_case = 1;
        } else if (strcmp(argv[i], "-v") == 0) {
            options->invert_match = 1;
        } else if (strcmp(argv[i], "-r") == 0) {
            options->recursive = 1;
        } else if (strcmp(argv[i], "-n") == 0) {
            options->show_line_number = 1;
        } else if (strcmp(argv[i], "-c") == 0) {
            options->count_matches = 1;
        } else if (argv[i][0] != '-') {
            if (options->pattern == NULL) {
                options->pattern = argv[i];
            } else {
                options->files[options->file_count++] = argv[i];
            }
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    if (options->pattern == NULL) {
        fprintf(stderr, "No pattern specified.\n");
        exit(EXIT_FAILURE);
    }
}
