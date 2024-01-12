#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../utils/random/random.h"
#include "../utils/shared/atoms/atom_pids.h"
#include "../utils/shared/config/config.h"
#include "../utils/signals/signals.h"
#include "../utils/sync/sync_barrier.h"

#define ACTIVATOR_ARGS 1  // 0:exec_name

bool simulation_is_running = true;

void event_termination_handler(int signal) {
    int ignored = signal;
    simulation_is_running = false;
}

void activator_signals_init() {
    signal_set(EVENT_TERMINATION, event_termination_handler, false);
}

void send_split_event() {
    int atom_pid = atom_get(random_get(0, atom_pids_size_get() - 1));
    kill(atom_pid, EVENT_SPLIT);
    printf("ACTIVATOR: sent SPLIT EVENT to atom #%d\n", atom_pid);
}

int main(int argc, char *argv[]) {
    if (argc < ACTIVATOR_ARGS) {
        fprintf(stderr, "wrong args for %s: needed %d, provided %d\n", argv[0],
                ACTIVATOR_ARGS, argc);
        exit(EXIT_FAILURE);
    }

    int *config = config_get();
    int day = config[CFG_SIM_DURATION];

    activator_signals_init();

    printf("ACTIVATOR: created\n");

    sync_barrier_wait();

    while (simulation_is_running) {
        sleep(1);
        send_split_event();
    }

    return EXIT_SUCCESS;
}
