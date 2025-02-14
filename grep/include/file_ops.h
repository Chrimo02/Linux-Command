#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <stdio.h>

typedef int (*callback_t)(const char *line, int line_number);

void process_file(const char *file_path, callback_t callback);

void process_stdin(callback_t callback);

char *read_line(FILE *file);

#endif
