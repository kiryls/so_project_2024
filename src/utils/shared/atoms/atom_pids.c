#include "atom_pids.h"

#include <stdio.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_size_t.h>

#include "../../ipc/sem/sem.h"
#include "../../ipc/shmem/shmem.h"

#define _ATOM_PIDS "/atom_pids_shmem"
#define _ATOM_PIDS_INTERNAL "/atom-pids-shmem-internal"
#define _ATOM_PIDS_MUTEX "/atom_pids_mutex"
#define _ATOM_PIDS_INITIAL_CAPACITY 8

AtomPids *atom_pids_create() {
    AtomPids *atoms = shmem_create(_ATOM_PIDS, sizeof(AtomPids));

    atoms->size = 0;
    atoms->cap = _ATOM_PIDS_INITIAL_CAPACITY;
    char pids_shmem_name[64];
    sprintf(pids_shmem_name, "%s_%zu", _ATOM_PIDS_INTERNAL, atoms->cap);
    shmem_create(pids_shmem_name, _ATOM_PIDS_INITIAL_CAPACITY * sizeof(pid_t));
    sem_create(_ATOM_PIDS_MUTEX, 1);

    return atoms;
}

AtomPids *atom_pids_get() { return shmem_get(_ATOM_PIDS, sizeof(AtomPids)); }

size_t atom_pids_size_get() {
    AtomPids *atoms = shmem_get(_ATOM_PIDS, sizeof(AtomPids));
    return atoms->size;
}

size_t atom_pids_cap_get() {
    AtomPids *atoms = shmem_get(_ATOM_PIDS, sizeof(AtomPids));
    return atoms->cap;
}

void atom_pids_add(pid_t atom_pid) {
    AtomPids *atoms = shmem_get(_ATOM_PIDS, sizeof(AtomPids));

    char _old_items_shmem_name[64];
    char _actual_items_shmem_name[64];
    sprintf(_actual_items_shmem_name, "%s_%zu", _ATOM_PIDS_INTERNAL,
            atoms->cap);
    sprintf(_old_items_shmem_name, "%s_%zu", _ATOM_PIDS_INTERNAL, atoms->cap);

    sem_acquire(_ATOM_PIDS_MUTEX);

    if (atoms->size == atoms->cap) {
        pid_t *temp =
            shmem_get(_old_items_shmem_name, atoms->cap * sizeof(pid_t));
        atoms->cap *= 2;
        sprintf(_actual_items_shmem_name, "%s_%zu", _ATOM_PIDS_INTERNAL,
                atoms->cap);
        pid_t *items =
            shmem_create(_actual_items_shmem_name, atoms->cap * sizeof(pid_t));

        for (size_t i = 0; i < atoms->size; ++i) {
            items[i] = temp[i];
        }

        shmem_remove(_old_items_shmem_name);
    }

    pid_t *items =
        shmem_get(_actual_items_shmem_name, atoms->cap * sizeof(pid_t));

    items[atoms->size++] = atom_pid;

    sem_release(_ATOM_PIDS_MUTEX);
}

pid_t atom_get(size_t index) {
    AtomPids *atoms = shmem_get(_ATOM_PIDS, sizeof(AtomPids));

    if (index < 0 || index >= atoms->size) {
        fprintf(stderr, "ERROR: array index out of bounds for AtomPids[%zu]\n",
                index);
        return -1;
    }

    char atom_pids_shmem_name[64];
    sprintf(atom_pids_shmem_name, "%s_%zu", _ATOM_PIDS_INTERNAL, atoms->cap);

    pid_t *items = shmem_get(atom_pids_shmem_name, atoms->cap * sizeof(pid_t));

    return items[index];
}

void atom_delete(size_t index) {
    AtomPids *atoms = shmem_get(_ATOM_PIDS, sizeof(AtomPids));

    if (index < 0 || index >= atoms->size) {
        fprintf(stderr, "ERROR: array index out of bounds for AtomPids[%zu]\n",
                index);
        return;
    }

    char atom_pids_shmem_name[64];
    sprintf(atom_pids_shmem_name, "%s_%zu", _ATOM_PIDS_INTERNAL, atoms->cap);

    pid_t *items = shmem_get(atom_pids_shmem_name, atoms->cap * sizeof(pid_t));

    sem_acquire(_ATOM_PIDS_MUTEX);

    for (size_t i = index; i < atoms->size; ++i) {
        items[i] = items[i + 1];
    }

    atoms->size--;

    sem_release(_ATOM_PIDS_MUTEX);
}

void atom_pids_remove() {
    AtomPids *atoms = shmem_get(_ATOM_PIDS, sizeof(AtomPids));

    if (atoms == NULL) {
        return;
    }

    char atom_pids_shmem_name[64];
    sprintf(atom_pids_shmem_name, "%s_%zu", _ATOM_PIDS_INTERNAL, atoms->cap);

    shmem_remove(atom_pids_shmem_name);
    sem_remove(_ATOM_PIDS_MUTEX);
    shmem_remove(_ATOM_PIDS);
}
