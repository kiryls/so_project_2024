#ifndef SYNC_BARRIER_H

#include "../ipc/sem/sem.h"
#include "../ipc/shmem/shmem.h"

void InitSyncBarrier(unsigned int height);
void DestroySyncBarrier();
void WaitOnSyncBarrier();

#endif // !SYNC_BARRIER_H
