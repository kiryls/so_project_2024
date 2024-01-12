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
#include "../utils/signals/signals.h"
#include "../utils/sync/sync_barrier.h"

#define ATOM_ARGS 2  // 0:atom_exec, 1:atomic_number

int Z;
int *config;
bool simulation_is_running = true;

void event_split_handler(int signal) {
    int ignored = signal;
    if (Z <= config[CFG_MIN_ATOMIC_N]) {
        return;
    }

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

    system_energy_supply(energy(Z, split_product));
}

void event_termination_handler(int signal) {
    int ignored = signal;
    simulation_is_running = false;
}

void atom_signals_init() {
    signal_set(EVENT_SPLIT, event_split_handler, true);
    signal_set(EVENT_TERMINATION, event_termination_handler, false);
}

int main(int argc, char *argv[]) {
    if (argc < ATOM_ARGS) {
        fprintf(stderr, "wrong args for %s: needed %d, provided %d\n", argv[0],
                ATOM_ARGS, argc);
        exit(EXIT_FAILURE);
    }

    Z = atoi(argv[1]);

    config = config_get();

    atom_signals_init();

    atom_pids_add(getpid());
    printf("ATOM: (Z = %d, #%d) created\n", Z, getpid());

    sync_barrier_wait();

    while (simulation_is_running) {
        pause();
    }

    return EXIT_SUCCESS;
}
