#ifndef ATOMS_H
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_size_t.h>
#include <sys/semaphore.h>

typedef struct {
    size_t size;
    size_t cap;
} AtomPids;

AtomPids *atom_pids_create();
AtomPids *atom_pids_get();
size_t atom_pids_size_get();
size_t atom_pids_cap_get();
void atom_pids_add(pid_t atom_pid);
pid_t atom_get(size_t index);
void atom_delete(size_t index);
void atom_pids_remove();

#endif  // !ATOMS_H
