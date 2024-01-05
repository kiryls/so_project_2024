#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../utils/sync/sync_barrier.h"

#define ATOM_ARGS 2 // 0:atom_exec, 1:atom_index

int main(int argc, char *argv[]) {

    if (argc < ATOM_ARGS) {
        fprintf(stderr, "wrong args number: needed %d, provided %d\n", ATOM_ARGS, argc);
        exit(EXIT_FAILURE);
    }

    // for (int i = 3; i >= 0; i--) {
    //     sleep(1);
    //     printf("ATOM %s: %d ...\n", argv[1], i);
    // } 

    // WaitOnSyncBarrier(); 

    int r = arc4random() % 10 + 1;

    printf("ATOM %s: ready with random value %d\n", argv[1], r);

    return EXIT_SUCCESS;
}
