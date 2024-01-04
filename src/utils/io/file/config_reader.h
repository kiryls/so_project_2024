#ifndef CONFIG_READER_H

#define CONFIG_PARAMS 9

typedef enum {
    CFG_ENERGY_DEMAND = 0,
    CFG_N_ATOMS_INIT,
    CFG_N_ATOM_MIN,
    CFG_N_ATOM_MAX,
    CFG_MIN_ATOMIC_N,
    CFG_N_NEW_ATOMS,
    CFG_STEP,
    CFG_SIM_DURATION,
    CFG_ENERGY_EXPLODE_THRESHOLD
} ConfigParams;

extern int config[CONFIG_PARAMS];

void ReadConfig(const char *config_path);

#endif // !CONFIG_READER_H
