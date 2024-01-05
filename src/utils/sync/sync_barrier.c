#include "sync_barrier.h"

#define _sync_barrier "/sync_barrier_sem"
#define _height_mutex "/barrier_height_mutex"
#define _height_count "/barrier_height_shmem"

void InitSyncBarrier(unsigned int height) {
    int *barrier_height = (int*) CreateShMem(_height_count, sizeof(int));
    *barrier_height = height; 

    CreateSem(_sync_barrier, 0);
    CreateSem(_height_mutex, 1);
}

void WaitOnSyncBarrier() {
    int *barrier_height = (int*) GetShMem(_height_count, sizeof(int));

    AcquireSem(_height_mutex);
    *barrier_height = *barrier_height - 1;
    ReleaseSem(_height_mutex);

    if (*barrier_height <= 0) {
        ReleaseSem(_sync_barrier);
    }

    AcquireSem(_sync_barrier);
    ReleaseSem(_sync_barrier);
}

void DestroySyncBarrier() {
    UnlinkShMem(_height_count);
    UnlinkSem(_sync_barrier);
    UnlinkSem(_height_mutex);
}
