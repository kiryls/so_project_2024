#ifndef SYNC_BARRIER_H

#include "../ipc/sem/sem.h"
#include "../ipc/shmem/shmem.h"

void sync_barrier_create(unsigned int height);
void sync_barrier_remove();
void sync_barrier_wait();

#endif  // !SYNC_BARRIER_H
