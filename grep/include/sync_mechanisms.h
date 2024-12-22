#ifndef SYNC_MECHANISMS_H
#define SYNC_MECHANISMS_H

#include <pthread.h>

// Function prototypes for synchronization mechanisms
pthread_mutex_t *create_mutex();
void lock_mutex(pthread_mutex_t *mutex);
void unlock_mutex(pthread_mutex_t *mutex);
void destroy_mutex(pthread_mutex_t *mutex);

#endif // SYNC_MECHANISMS_H
