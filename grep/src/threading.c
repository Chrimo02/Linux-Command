#include "threading.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *threaded_search(void *arg) {
    const char *dir_path = (const char *)arg;
    // Example function to process directory/file, can be customized
    printf("Searching directory: %s\n", dir_path);
    // Here, you can call the function for directory traversal, file searching, etc.
    return NULL;
}

int start_threaded_search(const char *dir_path, void (*callback)(const char *file_path)) {
    pthread_t thread_id;
    int ret = pthread_create(&thread_id, NULL, threaded_search, (void *)dir_path);
    if (ret != 0) {
        perror("pthread_create");
        return -1;
    }

    pthread_join(thread_id, NULL);  // Wait for thread to finish
    return 0;
}
