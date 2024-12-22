
#include <stdio.h>
#ifndef FILE_OPS_H
#define FILE_OPS_H

char *read_line(FILE *file);
void process_file(const char *file_path, int (*callback)(const char *line));
void process_stdin(int (*callback)(const char *line));

#endif // FILE_OPS_H
