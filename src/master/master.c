#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_size_t.h>
#include <sys/fcntl.h>
#include <sys/semaphore.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../include/raylib.h"
#include "../utils/io/logger/error_logger.h"
#include "../utils/random/random.h"
#include "../utils/shared/atoms/atom_pids.h"
#include "../utils/shared/config/config.h"
#include "../utils/shared/energy/energy.h"
#include "../utils/signals/signals.h"
#include "../utils/sync/sync_barrier.h"

#define FPS 60
#define SCREEN_W 640
#define SCREEN_H 480
#define MASTER_ARGS 2  // 0:master_exec, 1:config_path

int *config;
pid_t activator_pid;

// barrier lock:
// https://stackoverflow.com/questions/6331301/implementing-an-n-process-barrier-using-semaphores

void activator_init() {
    activator_pid = fork();

    if (activator_pid == 0) {
        execlp("../../build/src/activator/activator", "activator", NULL);
        ERRLOG("execlp()");
        exit(EXIT_FAILURE);
    } else if (activator_pid < 0) {
        ERRLOG("fork(atom)");
        exit(EXIT_FAILURE);
    }
}

void atoms_init() {
    atom_pids_create();

    for (int i = 0; i < config[CFG_N_ATOMS_INIT]; ++i) {
        pid_t atom_pid = fork();

        if (atom_pid == 0) {
            char atomic_number[8];
            sprintf(atomic_number, "%d", random_get(1, config[CFG_N_ATOM_MAX]));
            execlp("../../build/src/atom/atom", "atom", atomic_number, NULL);
            ERRLOG("execlp()");
            exit(EXIT_FAILURE);
        } else if (atom_pid < 0) {
            ERRLOG("fork(atom)");
            exit(EXIT_FAILURE);
        }
    }
}

void wait_for_everyone_to_return() {
    int status = 0;
    pid_t wpid;
    while ((wpid = wait(&status)) > 0) {
        // do nothing
    }
}

void ipcs_cleanup() {
    sync_barrier_remove();
    config_remove();
    system_energy_remove();
    atom_pids_remove();
}

int main(int argc, char *argv[]) {
    if (argc < MASTER_ARGS) {
        printf("ERROR: master process needs more args. Provided:");
        for (int i = 0; i < argc; ++i) {
            printf(" %s", argv[i]);
        }
        printf("\n");
        exit(EXIT_FAILURE);
    }

    ipcs_cleanup();

    config = config_load(argv[1]);

    sync_barrier_create(1 + 1 + config[CFG_N_ATOMS_INIT]);

    atoms_init();

    activator_init();

    system_energy_init();

    sync_barrier_wait();

    char *window_title = "Chain Reaction";
    InitWindow(SCREEN_W, SCREEN_H, window_title);

    char text[32];
    sprintf(text, "%d MW", system_energy_get());
    int font_size = 20;

    SetTargetFPS(FPS);
    int fps_sync = 0;
    bool text_is_black = true;
    Color text_color;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        if (fps_sync % FPS == 0) {
            sprintf(text, "%d MW", system_energy_get());

            if (text_is_black) {
                text_color = BLACK;
            } else {
                text_color = RED;
            }
            text_is_black = !text_is_black;
        }

        DrawText(text, GetScreenWidth() / 2 - MeasureText(text, font_size) / 2,
                 GetScreenHeight() / 2 - font_size / 2, font_size, text_color);

        EndDrawing();

        fps_sync++;
    }

    for (size_t i = 0; i < atom_pids_size_get(); ++i) {
        kill(atom_get(i), EVENT_TERMINATION);
    }

    kill(activator_pid, EVENT_TERMINATION);

    printf("MASTER: here\n");

    wait_for_everyone_to_return();

    ipcs_cleanup();

    return 0;
}
