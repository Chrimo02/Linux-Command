#ifndef THREADING_H
#define THREADING_H

#include <pthread.h>

// Start a threaded search for multiple directories
int start_threaded_search(const char *dir_paths[], int dir_count, void (*callback)(const char *file_path));

// Mutex control functions for thread-safe operations on shared resources
void lock_matches();
void unlock_matches();
void destroy_mutex();

#endif // THREADING_H
