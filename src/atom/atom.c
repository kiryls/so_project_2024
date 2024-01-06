#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <unistd.h>

#include "../utils/sync/sync_barrier.h"
#include "../utils/shared/config/config.h"
#include "../utils/random/random.h"
#include "../utils/io/logger/error_logger.h"
#include "../utils/shared/energy/energy.h"

#define ATOM_ARGS 2 // 0:atom_exec, 1:atomic_number

int Z;
int *config;

void SplitAtom() {
    pid_t split_atom_pid = fork();

    int split_product = Rand(1, Z-1);

    if(split_atom_pid == 0) {
        char atomic_number[8];
        sprintf(atomic_number, "%d", split_product);
        execlp("../../build/src/atom/atom", "atom", atomic_number, NULL);
        ERRLOG("SplitAtom().execlp(): %d -> %d %d", Z, Z-split_product, split_product);
        exit(EXIT_SUCCESS);
    } else if(split_atom_pid < 0) {
        ERRLOG("SplitAtom(Z=%d).fork()", Z);
        exit(EXIT_FAILURE);
    }

    Z = Z - split_product;

    SupplyEnergyToSystem(Energy(Z, split_product));
}

int main(int argc, char *argv[]) {

    if (argc < ATOM_ARGS) {
        fprintf(stderr, "wrong args number: needed %d, provided %d\n", ATOM_ARGS, argc);
        exit(EXIT_FAILURE);
    }

    Z = atoi(argv[1]);

    config = GetConfig();

    WaitOnSyncBarrier(); 

    printf("ATOM: (Z = %d) created\n", Z);

    if(Z >= config[CFG_MIN_ATOMIC_N]) {
        for (int i = 5; i > 0; i--) {
            printf("ATOM (Z=%d): %ds to split...\n", Z, i);
            sleep(1);
        }

        SplitAtom();
    }

    printf("ATOM: (Z = %d) created\n", Z);

    return EXIT_SUCCESS;
}
