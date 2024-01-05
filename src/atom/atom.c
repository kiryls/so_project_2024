#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../utils/sync/sync_barrier.h"

#define ATOM_ARGS 2 // 0:atom_exec, 1:atomic_number

int Z;

int main(int argc, char *argv[]) {

    if (argc < ATOM_ARGS) {
        fprintf(stderr, "wrong args number: needed %d, provided %d\n", ATOM_ARGS, argc);
        exit(EXIT_FAILURE);
    }

    Z = atoi(argv[1]);

    WaitOnSyncBarrier(); 

    printf("ATOM: (Z = %d) created\n", Z);

    return EXIT_SUCCESS;
}
