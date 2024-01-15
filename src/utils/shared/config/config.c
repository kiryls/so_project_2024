#include "config.h"

#include <stdio.h>
#include <string.h>

#include "../../ipc/shmem/shmem.h"

#define MAX_LINE_LEN 1024
#define MAX_PARAM_NAME_LEN 1024

#define _config_shmem "/config_shmem"

int *global_config;

// these are default settings
int defaults[] = {
    [CFG_ENERGY_DEMAND] = 10,  // system demands 10 units of energy each cycle
    [CFG_N_ATOMS_INIT] = 10,   // starting atoms quantity
    [CFG_N_ATOM_MAX] = 118,    // Oganesson (Og) biggest known atom
    [CFG_MIN_ATOMIC_N] = 1,    // atomic waste threshold set on Hydrogen (H)
    [CFG_N_NEW_ATOMS] = 10,    // nanoseconds interval between every feeding
    [CFG_STEP] = 1000000,      // interval in nanoseconds
    [CFG_SIM_DURATION] = 5,    // simulation duration in seconds
    [CFG_ENERGY_EXPLODE_THRESHOLD] = 1000  // boom threshold
};

void __config_read__(char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("ERROR: master couldn't read file at '%s'\n", filepath);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];
    char key[MAX_PARAM_NAME_LEN];
    int val;

    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
        sscanf(line, "%s %d", key, &val);
        printf("CONFIG: %s = %d\n", key, val);

        if (strstr(key, "ENERGY_DEMAND") != NULL) {
            global_config[CFG_ENERGY_DEMAND] = val;
        }

        if (strstr(key, "N_ATOMS_INIT") != NULL) {
            global_config[CFG_N_ATOMS_INIT] = val;
        }

        if (strstr(key, "N_ATOM_MAX") != NULL) {
            global_config[CFG_N_ATOM_MAX] = val;
        }

        if (strstr(key, "MIN_ATOMIC_N") != NULL) {
            global_config[CFG_MIN_ATOMIC_N] = val;
        }

        if (strstr(key, "N_NEW_ATOMS") != NULL) {
            global_config[CFG_N_NEW_ATOMS] = val;
        }

        if (strstr(key, "STEP") != NULL) {
            global_config[CFG_STEP] = val;
        }

        if (strstr(key, "SIM_DURATION") != NULL) {
            global_config[CFG_SIM_DURATION] = val;
        }

        if (strstr(key, "ENERGY_EXPLODE_THRESHOLD") != NULL) {
            global_config[CFG_ENERGY_EXPLODE_THRESHOLD] = val;
        }
    }

    fclose(fp);
}

void config_load(char *filepath) {
    global_config =
        (int *)shmem_create(_config_shmem, CFG_PARAMS * sizeof(int));

    memcpy(global_config, defaults, CFG_PARAMS * sizeof(int));

    __config_read__(filepath);
}

void config_get() {
    global_config = shmem_get(_config_shmem, CFG_PARAMS * sizeof(int));
    if (global_config == NULL) {
        fprintf(stderr, "ERROR: in file %s, line %d - couldn't shmem_get(%s)\n",
                __FILE__, __LINE__, _config_shmem);
    }
}

void config_remove() { shmem_remove(_config_shmem); }
