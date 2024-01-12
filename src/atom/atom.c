#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <unistd.h>

#include "../utils/io/logger/error_logger.h"
#include "../utils/random/random.h"
#include "../utils/shared/atoms/atom_pids.h"
#include "../utils/shared/config/config.h"
#include "../utils/shared/energy/energy.h"
#include "../utils/sync/sync_barrier.h"

#define ATOM_ARGS 2  // 0:atom_exec, 1:atomic_number

int Z;
int *config;

void atom_split() {
    int split_product = random_get(1, Z - 1);

    pid_t split_atom_pid = fork();

    if (split_atom_pid == 0) {
        char atomic_number[8];
        sprintf(atomic_number, "%d", split_product);
        execlp("../../build/src/atom/atom", "atom", atomic_number, NULL);
        ERRLOG("execlp()");
        exit(EXIT_SUCCESS);
    } else if (split_atom_pid < 0) {
        ERRLOG("fork()");
        exit(EXIT_FAILURE);
    }

    Z = Z - split_product;

    printf(
        "SYSTEM: atom (Z = %d) split into (Z1 = %d) and (Z2 = %d) providing %d "
        "energy to the system\n",
        Z + split_product, Z, split_product, energy(Z, split_product));

    system_energy_supply(energy(Z, split_product));
}

int main(int argc, char *argv[]) {
    if (argc < ATOM_ARGS) {
        fprintf(stderr, "wrong args number: needed %d, provided %d\n",
                ATOM_ARGS, argc);
        exit(EXIT_FAILURE);
    }

    Z = atoi(argv[1]);

    config = config_get();

    atom_pids_add(getpid());
    printf("ATOM xxx: (Z = %d) created\n", Z);

    sync_barrier_wait();

    if (Z >= config[CFG_MIN_ATOMIC_N]) {
        for (int i = 3; i > 0; i--) {
            printf("ATOM: (Z = %d) %ds to split...\n", Z, i);
            sleep(1);
        }

        atom_split();
    }

    pause();

    return EXIT_SUCCESS;
}
