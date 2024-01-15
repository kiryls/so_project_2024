#ifndef CONFIG_H

typedef enum {
    CFG_ENERGY_DEMAND = 0,
    CFG_N_ATOMS_INIT,
    CFG_N_ATOM_MAX,
    CFG_MIN_ATOMIC_N,
    CFG_N_NEW_ATOMS,
    CFG_STEP,
    CFG_SIM_DURATION,
    CFG_ENERGY_EXPLODE_THRESHOLD,
    CFG_PARAMS
} ConfigParams;

extern int *global_config;

void config_load(char *filepath);
void config_get();
void config_remove();

#endif  // !CONFIG_H
