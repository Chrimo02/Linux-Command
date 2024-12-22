#include "sync_mechanisms.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t *create_mutex() {
    pthread_mutex_t *mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (mutex == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (pthread_mutex_init(mutex, NULL) != 0) {
        perror("pthread_mutex_init");
        free(mutex);
        exit(EXIT_FAILURE);
    }

    return mutex;
}

void lock_mutex(pthread_mutex_t *mutex) {
    if (pthread_mutex_lock(mutex) != 0) {
        perror("pthread_mutex_lock");
        exit(EXIT_FAILURE);
    }
}

void unlock_mutex(pthread_mutex_t *mutex) {
    if (pthread_mutex_unlock(mutex) != 0) {
        perror("pthread_mutex_unlock");
        exit(EXIT_FAILURE);
    }
}

void destroy_mutex(pthread_mutex_t *mutex) {
    if (pthread_mutex_destroy(mutex) != 0) {
        perror("pthread_mutex_destroy");
        exit(EXIT_FAILURE);
    }
    free(mutex);
}
