#include "file_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024

char *read_line(FILE *file) {
    char buffer[BUFFER_SIZE];
    if (fgets(buffer, BUFFER_SIZE, file) == NULL) {
        return NULL;
    }

    size_t len = strlen(buffer);
    char *line = malloc(len + 1);
    if (line == NULL) {
        perror("error at malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(line, buffer);
    return line;
}

void process_file(const char *file_path, callback_t callback) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror(file_path);
        return;
    }

    char *line = NULL;
    int line_number = 0;
    while ((line = read_line(file)) != NULL) {
        line_number++;
        if (!callback(line, line_number)) {
            free(line);
            break;
        }
        free(line);
    }

    fclose(file);
}

void process_stdin(callback_t callback) {
    char *line = NULL;
    int line_number = 0;
    while ((line = read_line(stdin)) != NULL) {
        line_number++;
        if (!callback(line, line_number)) {
            free(line);
            break;
        }
        free(line);
    }
}