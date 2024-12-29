#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <stdio.h>

// Callback-Typdefinition
typedef int (*callback_t)(const char *line, int line_number);

// Funktion zum Verarbeiten einer Datei
void process_file(const char *file_path, callback_t callback);

// Funktion zum Verarbeiten von stdin
void process_stdin(callback_t callback);

// Zeile lesen
char *read_line(FILE *file);

#endif // FILE_OPS_H
