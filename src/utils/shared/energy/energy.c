#include "energy.h"

#include <stdio.h>
#include <sys/semaphore.h>

#define _system_energy "/system_energy_shmem"
#define _system_energy_mutex "/system_energy_mutex"

int *global_energy;

int energy(int z1, int z2) { return z1 * z2 - (z1 > z2 ? z1 : z2); }

void system_energy_init() {
    global_energy = (int *)shmem_create(_system_energy, sizeof(int));
    if (global_energy == NULL) {
        fprintf(stderr, "ERROR: in file %s, line %d - couldn't create energy\n",
                __FILE__, __LINE__);
        return;
    }

    sem_t *sem = sem_create(_system_energy_mutex, 1);
    if (sem == NULL) {
        fprintf(stderr,
                "ERROR: in file %s, line %d - couldn't create system energy "
                "mutex\n",
                __FILE__, __LINE__);
        return;
    }

    *global_energy = 0;
}

void system_energy_get() {
    global_energy = (int *)shmem_get(_system_energy, sizeof(int));
    if (global_energy == NULL) {
        fprintf(stderr, "ERROR: in file %s, line %d - couldn't get energy\n",
                __FILE__, __LINE__);
        return;
    }
}

void system_energy_supply(int quantity) {
    sem_acquire(_system_energy_mutex);
    *global_energy += quantity;
    sem_release(_system_energy_mutex);
}

void system_energy_absorb(int quantity) {
    sem_acquire(_system_energy_mutex);
    *global_energy -= quantity;
    sem_release(_system_energy_mutex);
}

void system_energy_remove() {
    sem_remove(_system_energy_mutex);
    shmem_remove(_system_energy);
}
