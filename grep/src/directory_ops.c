#include "directory_ops.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void list_files_in_directory(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        printf("%s\n", entry->d_name);  // Print each file name
    }

    closedir(dir);
}

void recursive_traversal(const char *dir_path, void (*callback)(const char *file_path)) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct full path for recursion
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);
        callback(full_path);  // Call callback function

        // If directory, recurse into it
        if (entry->d_type == DT_DIR) {
            recursive_traversal(full_path, callback);
        }
    }

    closedir(dir);
}
