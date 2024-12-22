#ifndef DIRECTORY_OPS_H
#define DIRECTORY_OPS_H

#include <stdio.h>

// Function prototypes for directory traversal
void list_files_in_directory(const char *dir_path);
void recursive_traversal(const char *dir_path, void (*callback)(const char *file_path));

#endif // DIRECTORY_OPS_H
