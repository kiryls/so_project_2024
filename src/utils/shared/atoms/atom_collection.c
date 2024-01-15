#include "atom_collection.h"

#include <stdio.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_size_t.h>

#include "../../ipc/sem/sem.h"
#include "../../ipc/shmem/shmem.h"
#include "../config/config.h"

#define __ATOMS__ "/atoms-shared-mem"
#define __ATOMS_MUTEX__ "/atoms-mutex"

AtomCollection *global_atoms;

void atom_collection_init() {
    size_t upperbound =
        global_config[CFG_N_ATOMS_INIT] * global_config[CFG_N_ATOM_MAX] +
        global_config[CFG_SIM_DURATION] * global_config[CFG_N_NEW_ATOMS] *
            global_config[CFG_N_ATOM_MAX];

    global_atoms = shmem_create(
        __ATOMS__, sizeof(AtomCollection) + upperbound * sizeof(pid_t));

    sem_create(__ATOMS_MUTEX__, 1);

    global_atoms->size = 0;
    global_atoms->cap = upperbound;
}

void atom_collection_get() {
    size_t upperbound =
        global_config[CFG_N_ATOMS_INIT] * global_config[CFG_N_ATOM_MAX] +
        global_config[CFG_SIM_DURATION] * global_config[CFG_N_NEW_ATOMS] *
            global_config[CFG_N_ATOM_MAX];

    global_atoms = shmem_get(
        __ATOMS__, sizeof(AtomCollection) + upperbound * sizeof(pid_t));
}
pid_t atom_collection_get_pid(int index) {
    if (index < 0 || index >= global_atoms->size) {
        fprintf(stderr,
                "ERROR: atom_collection_get_pid(%d): index out of bounds\n",
                index);
        return 0;
    }

    return global_atoms->pids[index];
}

void atom_collection_add_pid(pid_t pid) {
    sem_acquire(__ATOMS_MUTEX__);
    global_atoms->pids[global_atoms->size] = pid;
    global_atoms->size++;
    sem_release(__ATOMS_MUTEX__);
}

void atom_collection_delete_pid(pid_t pid) {
    int found_at = -1;
    for (int i = 0; i < global_atoms->size; ++i) {
        if (global_atoms->pids[i] == pid) {
            found_at = i;
            break;
        }
    }

    if (found_at < 0) {
        return;
    }

    sem_acquire(__ATOMS_MUTEX__);
    for (int i = found_at; i < global_atoms->size; ++i) {
        global_atoms->pids[i] = global_atoms->pids[i + 1];
    }
    sem_release(__ATOMS_MUTEX__);
}

void atom_collection_remove() {
    shmem_remove(__ATOMS__);
    sem_remove(__ATOMS_MUTEX__);
}
