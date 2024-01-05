#ifndef ENERGY_H

#include "../../ipc/shmem/shmem.h"
#include "../../ipc/sem/sem.h"

int InitSystemEnergy();
int GetSystemEnergy();
void SupplyEnergyToSystem(int quantity);
void AbsorbEnergyFromSystem(int quantity);
void DestroySystemEnergy();

#endif // !ENERGY_H
