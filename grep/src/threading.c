#include "threading.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "directory_ops.h"

// Mutex for protecting access to the matches list
static pthread_mutex_t matches_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    const char *dir_path;
    void (*callback)(const char *file_path);
} thread_data_t;

void *threaded_search(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    recursive_traversal(data->dir_path, data->callback);
    free(data);
    return NULL;
}

int start_threaded_search(const char *dir_paths[], int dir_count, void (*callback)(const char *file_path)) {
    pthread_t threads[dir_count];

    for (int i = 0; i < dir_count; i++) {
        thread_data_t *data = malloc(sizeof(thread_data_t));
        if (!data) {
            perror("malloc");
            return -1;
        }
        data->dir_path = dir_paths[i];
        data->callback = callback;

        int ret = pthread_create(&threads[i], NULL, threaded_search, data);
        if (ret != 0) {
            perror("pthread_create");
            free(data);
            return -1;
        }
    }

    for (int i = 0; i < dir_count; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

// Lock and unlock functions for the matches mutex
void lock_matches() {
    pthread_mutex_lock(&matches_mutex);
}

void unlock_matches() {
    pthread_mutex_unlock(&matches_mutex);
}

// Destroy the matches mutex
void destroy_mutex() {
    pthread_mutex_destroy(&matches_mutex);
}
