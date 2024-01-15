#ifndef ENERGY_H

#include <stdbool.h>

#include "../../ipc/sem/sem.h"
#include "../../ipc/shmem/shmem.h"

extern int *global_energy;

int energy(int z1, int z2);
void system_energy_init();
void system_energy_get();
void system_energy_supply(int quantity);
void system_energy_absorb(int quantity);
void system_energy_remove();

#endif  // !ENERGY_H
