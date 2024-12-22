#include "error_handling.h"
#include <stdio.h>
#include <stdlib.h>

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void handle_error_with_code(const char *msg, int error_code) {
    fprintf(stderr, "Error: %s (code: %d)\n", msg, error_code);
    exit(EXIT_FAILURE);
}
void report_error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}
