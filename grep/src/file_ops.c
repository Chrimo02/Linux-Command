

#include "file_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024

char *read_line(FILE *file) {
    char buffer[BUFFER_SIZE];
    if (fgets(buffer, BUFFER_SIZE, file) == NULL) {
        return NULL; // EOF or error
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

void process_file(const char *file_path, int (*callback)(const char *line)) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror(file_path);
        return;
    }

    char *line = NULL;
    while ((line = read_line(file)) != NULL) {
        if (!callback(line)) {
            free(line);
            break;
        }
        free(line);
    }

    fclose(file);
}

void process_stdin(int (*callback)(const char *line)) {
    char *line = NULL;
    while ((line = read_line(stdin)) != NULL) {
        if (!callback(line)) {
            free(line);
            break;
        }
        free(line);
    }
}
