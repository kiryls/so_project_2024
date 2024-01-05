#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>
#include <sys/semaphore.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../include/raylib.h"
#include "../utils/ipc/sem/sem.h"
#include "../utils/ipc/shmem/shmem.h"
#include "../utils/sync/sync_barrier.h"
#include "../utils/io/logger/error_logger.h"
#include "../utils/random/random.h"
#include "../utils/globals/config/config.h"

#define FPS 60
#define SCREEN_W 640
#define SCREEN_H 480
#define MASTER_ARGS 2 // 0:master_exec, 1:config_path

pid_t *atom_pids;
int *config;

// barrier lock: https://stackoverflow.com/questions/6331301/implementing-an-n-process-barrier-using-semaphores

void InitAtoms() {
    atom_pids = (pid_t*) malloc(config[CFG_N_ATOMS_INIT] * sizeof(pid_t));
    if (atom_pids == NULL) {
        fprintf(stderr, "ERROR: [master] couldn't allocate atom_pids\n");
        return;
    }

    for (int i = 0; i < config[CFG_N_ATOMS_INIT]; ++i) {
        atom_pids[i] = fork();

        if (atom_pids[i] == 0) {
            char atomic_number[8];
            sprintf(atomic_number, "%d", Rand(1, config[CFG_N_ATOM_MAX]));
            execlp("../../build/src/atom/atom", "atom", atomic_number, NULL);
            ERRLOG("execlp(atom, Z=%s)", atomic_number);
            exit(EXIT_SUCCESS);
        } else if (atom_pids[i] < 0){
            ERRLOG("fork(atom)");
            exit(EXIT_FAILURE);
        }
    }
}

void WaitForEveryone() {
    int status = 0;
    pid_t wpid;
    while ((wpid = wait(&status)) > 0);
}

void ResetIPCs() {
    DestroySyncBarrier();
    DestroyConfig();
}

void Cleanup() {
    free(atom_pids);
    DestroySyncBarrier();
    DestroyConfig();
}

int main(int argc, char *argv[]) {

    if (argc < MASTER_ARGS) {
        printf("ERROR: master process needs more args. Provided:");
        for(int i = 0; i < argc; ++i) {
            printf(" %s", argv[i]);
        }
        printf("\n");
        exit(EXIT_FAILURE);
    }

    ResetIPCs();

    config = LoadConfig(argv[1]);

    InitSyncBarrier(1 + config[CFG_N_ATOMS_INIT]);
    
    InitAtoms();

    WaitOnSyncBarrier();

    printf("MASTER: ready\n");



    char *window_title = "Chain Reaction";
    InitWindow(SCREEN_W, SCREEN_H, window_title);

    char *text = "Boom!";
    int font_size = 20;

    SetTargetFPS(FPS);
    int fps_sync = 0;
    bool text_is_black = true;
    Color text_color;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        if(fps_sync % FPS == 0) {
            if(text_is_black) {
                text_color = BLACK;
            } else {
                text_color = RED;
            }
            text_is_black = !text_is_black;
        }

        DrawText(
            text, 
            GetScreenWidth()/2 - MeasureText(text, font_size)/2, 
            GetScreenHeight()/2 - font_size/2, 
            font_size, 
            text_color
        );

        EndDrawing();

        fps_sync++;
    }

    WaitForEveryone();

    Cleanup();

    return 0;
}
