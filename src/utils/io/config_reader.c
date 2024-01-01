#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "config_reader.h"

#define MAX_LINE_LEN 64

int config[] = {
    [ENERGY_DEMAND] = 1,
    [N_ATOMS_INIT] = 2,
    [N_ATOM_MIN] = 3,
    [N_ATOM_MAX] = 4,
    [MIN_ATOMIC_N] = 5,
    [N_NEW_ATOMS] = 6,
    [STEP] = 7,
    [SIM_DURATION] = 8,
    [ENERGY_EXPLODE_THRESHOLD] = 9
};

void ReadConfig(const char *config_path) {
    FILE *fp = fopen(config_path, "r");
    if (fp == NULL) {
        printf("ERROR: master couldn't read file at '%s'\n", config_path);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];

    while(fgets(line, MAX_LINE_LEN, fp) != NULL) {
        printf("%s", line);
    }

    fclose(fp);
}
