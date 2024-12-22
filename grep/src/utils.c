#include "utils.h"
#include <stdio.h>

void print_usage(const char *prog_name) {
    printf("Usage: %s [OPTIONS] PATTERN [FILES...]\n", prog_name);
    printf("Options:\n");
    printf("  -i  Ignore case\n");
    printf("  -v  Invert match\n");
    printf("  -r  Recursive search\n");
}
