#ifndef SYNC_MECHANISMS_H
#define SYNC_MECHANISMS_H

#include <pthread.h>

pthread_mutex_t *create_mutex();
void lock_mutex(pthread_mutex_t *mutex);
void unlock_mutex(pthread_mutex_t *mutex);
#endif
