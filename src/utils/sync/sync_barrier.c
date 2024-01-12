#include "sync_barrier.h"

#define _sync_barrier "/sync_barrier_sem"
#define _height_mutex "/barrier_height_mutex"
#define _height_count "/barrier_height_shmem"

void sync_barrier_create(unsigned int height) {
    int *barrier_height = (int *)shmem_create(_height_count, sizeof(int));
    *barrier_height = height;

    sem_create(_sync_barrier, 0);
    sem_create(_height_mutex, 1);
}

void sync_barrier_wait() {
    int *barrier_height = (int *)shmem_get(_height_count, sizeof(int));

    sem_acquire(_height_mutex);
    *barrier_height = *barrier_height - 1;
    sem_release(_height_mutex);

    if (*barrier_height <= 0) {
        sem_release(_sync_barrier);
    }

    sem_acquire(_sync_barrier);
    sem_release(_sync_barrier);
}

void sync_barrier_remove() {
    shmem_remove(_height_count);
    sem_remove(_sync_barrier);
    sem_remove(_height_mutex);
}
