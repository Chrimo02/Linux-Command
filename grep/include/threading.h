#ifndef THREADING_H
#define THREADING_H

#include <pthread.h>

// Function prototypes for threading
void *threaded_search(void *arg);
int start_threaded_search(const char *dir_path, void (*callback)(const char *file_path));

#endif // THREADING_H
