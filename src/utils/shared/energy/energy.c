#include "energy.h"

#include <stdio.h>

#define _system_energy "/system_energy_shmem"
#define _system_energy_mutex "/system_energy_mutex"

int energy(int z1, int z2) { return z1 * z2 - (z1 > z2 ? z1 : z2); }

int system_energy_init() {
    int *energy = (int *)shmem_create(_system_energy, sizeof(int));
    sem_create(_system_energy_mutex, 1);

    *energy = 0;

    return *energy;
}

int system_energy_get() {
    int *energy = (int *)shmem_get(_system_energy, sizeof(int));
    return *energy;
}

void system_energy_supply(int quantity) {
    int *energy = (int *)shmem_get(_system_energy, sizeof(int));

    printf("SYSTEM: total energy = %d MW\n", *energy);

    sem_acquire(_system_energy_mutex);
    *energy += quantity;
    sem_release(_system_energy_mutex);

    printf("SYSTEM: supplied %d MW, new total = %d MW\n", quantity, *energy);
}

void system_energy_absorb(int quantity) {
    int *energy = (int *)shmem_get(_system_energy, sizeof(int));

    sem_acquire(_system_energy_mutex);
    *energy -= quantity;
    sem_release(_system_energy_mutex);
}

void system_energy_remove() {
    sem_remove(_system_energy_mutex);
    shmem_remove(_system_energy);
}
