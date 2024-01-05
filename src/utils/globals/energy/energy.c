#include "energy.h"

#define _system_energy "/system_energy_shmem"
#define _system_energy_mutex "/system_energy_mutex"

int InitSystemEnergy() {
    int *energy = (int*) CreateShMem(_system_energy, sizeof(int));
    CreateSem(_system_energy_mutex, 1);

    *energy = 0;

    return *energy;
}

int GetSystemEnergy() {
    int *energy = (int*) GetShMem(_system_energy, sizeof(int));
    return *energy;
}

void SupplyEnergyToSystem(int quantity) {
    int *energy = (int*) GetShMem(_system_energy, sizeof(int));

    AcquireSem(_system_energy_mutex);
    *energy += quantity;
    ReleaseSem(_system_energy_mutex);
}

void AbsorbEnergyFromSystem(int quantity) {
    int *energy = (int*) GetShMem(_system_energy, sizeof(int));

    AcquireSem(_system_energy_mutex);
    *energy -= quantity;
    ReleaseSem(_system_energy_mutex);
}

void DestroySystemEnergy() {
    UnlinkSem(_system_energy_mutex);
    UnlinkShMem(_system_energy);
}
