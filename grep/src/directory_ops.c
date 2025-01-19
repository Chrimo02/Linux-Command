#include "directory_ops.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
/*
void list_files_in_directory(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        fprintf(stderr, "grep: %s: %s\n", dir_path, strerror(errno));
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}
*/ // diese Funktion wird nirgends benutzt -> löschen?

void recursive_traversal(const char *dir_path, void (*callback)(const char *file_path)) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        fprintf(stderr, "grep: %s: %s\n", dir_path, strerror(errno));
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            recursive_traversal(full_path, callback);
        } else {
            callback(full_path);  // Pass full path to callback
        }
    }

    closedir(dir);
}
