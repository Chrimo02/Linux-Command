
#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_arguments(int argc, char *argv[], options_t *options) {
    memset(options, 0, sizeof(options_t));
    options->pattern = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            options->ignore_case = 1;
        } else if (strcmp(argv[i], "-v") == 0) {
            options->invert_match = 1;
        } else if (strcmp(argv[i], "-r") == 0) {
            options->recursive = 1;
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