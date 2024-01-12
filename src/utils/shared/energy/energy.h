#ifndef ENERGY_H

#include "../../ipc/sem/sem.h"
#include "../../ipc/shmem/shmem.h"

int energy(int z1, int z2);
int system_energy_init();
int system_energy_get();
void system_energy_supply(int quantity);
void system_energy_absorb(int quantity);
void system_energy_remove();

#endif  // !ENERGY_H
