#ifndef CONFIG_READER_H

#define CONFIG_PARAMS 9

typedef enum {
    ENERGY_DEMAND = 0,
    N_ATOMS_INIT,
    N_ATOM_MIN,
    N_ATOM_MAX,
    MIN_ATOMIC_N,
    N_NEW_ATOMS,
    STEP,
    SIM_DURATION,
    ENERGY_EXPLODE_THRESHOLD
} ConfigParams;

extern int config[CONFIG_PARAMS];

void ReadConfig(const char *config_path);

#endif // !CONFIG_READER_H
