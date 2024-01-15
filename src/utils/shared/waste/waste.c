#include "waste.h"

#include <stdio.h>
#include <sys/semaphore.h>

#define _system_waste "/system_waste_shmem"
#define _system_waste_mutex "/system_waste_mutex"

#define _MAX_ATOMIC_NUMBER 118 + 1  // +1 to index properly

int *global_waste;

void system_waste_init() {
    global_waste =
        (int *)shmem_create(_system_waste, _MAX_ATOMIC_NUMBER * sizeof(int));
    if (global_waste == NULL) {
        fprintf(stderr, "ERROR: in file %s, line %d - couldn't create waste\n",
                __FILE__, __LINE__);
        return;
    }

    sem_t *sem = sem_create(_system_waste_mutex, 1);
    if (sem == NULL) {
        fprintf(
            stderr,
            "ERROR: in file %s, line %d - couldn't create system waste mutex",
            __FILE__, __LINE__);
        return;
    }

    for (int i = 0; i < _MAX_ATOMIC_NUMBER; ++i) {
        global_waste[i] = 0;
    }
}

void system_waste_get() {
    global_waste = shmem_get(_system_waste, _MAX_ATOMIC_NUMBER * sizeof(int));
    if (global_waste == NULL) {
        fprintf(stderr,
                "ERROR: in file %s, line %d - couldn't get system waste\n",
                __FILE__, __LINE__);
        return;
    }
}

void system_waste_add(int Z) {
    if (Z <= 0 || Z > _MAX_ATOMIC_NUMBER) {
        return;
    }

    sem_acquire(_system_waste_mutex);
    global_waste[Z]++;
    sem_release(_system_waste_mutex);
}

void system_waste_remove() {
    sem_remove(_system_waste_mutex);
    shmem_remove(_system_waste);
}
