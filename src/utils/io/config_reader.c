#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config_reader.h"

#define MAX_LINE_LEN 64
#define MAX_PARAM_NAME_LEN 32

// these are default settings
int config[] = {
    [CFG_ENERGY_DEMAND] =               10,     // system demands 10 units of energy each cycle
    [CFG_N_ATOMS_INIT] =                10,     // starting atoms quantity
    [CFG_N_ATOM_MAX] =                  118,    // Oganesson (Og) biggest known atom
    [CFG_MIN_ATOMIC_N] =                1,      // atomic waste threshold set on Hydrogen (H)
    [CFG_N_NEW_ATOMS] =                 10,     // every STEP ns we feed this many atoms in the system
    [CFG_STEP] =                        1000000,// nanoseconds
    [CFG_SIM_DURATION] =                5,      // simulation duration in seconds
    [CFG_ENERGY_EXPLODE_THRESHOLD] =    1000    // boom threshold
};

void ReadConfig(const char *config_path) {
    FILE *fp = fopen(config_path, "r");
    if (fp == NULL) {
        printf("ERROR: master couldn't read file at '%s'\n", config_path);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];
    char key[MAX_PARAM_NAME_LEN];
    int val;

    while(fgets(line, MAX_LINE_LEN, fp) != NULL) {
        sscanf(line, "%s %d", key, &val);
        printf("key:%s, val:%d\n", key, val);

        if(strstr(key, "ENERGY_DEMAND") != NULL) {
            config[CFG_ENERGY_DEMAND] = val;
        }

        if(strstr(key, "N_ATOMS_INIT") != NULL) {
            config[CFG_N_ATOMS_INIT] = val;
        }

        if(strstr(key, "N_ATOM_MAX") != NULL) {
            config[CFG_N_ATOM_MAX] = val;
        }

        if(strstr(key, "MIN_ATOMIC_N") != NULL) {
            config[CFG_MIN_ATOMIC_N] = val;
        }

        if(strstr(key, "N_NEW_ATOMS") != NULL) {
            config[CFG_N_NEW_ATOMS] = val;
        }

        if(strstr(key, "STEP") != NULL) {
            config[CFG_STEP] = val;
        }

        if(strstr(key, "SIM_DURATION") != NULL) {
            config[CFG_SIM_DURATION] = val;
        }

        if(strstr(key, "ENERGY_EXPLODE_THRESHOLD") != NULL) {
            config[CFG_ENERGY_EXPLODE_THRESHOLD] = val;
        }
    }

    fclose(fp);
}
