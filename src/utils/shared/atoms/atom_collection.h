#ifndef ATOM_COLLECTION_H

#include <sys/_types/_pid_t.h>

typedef struct {
    int size, cap;
    pid_t pids[];
} AtomCollection;

extern AtomCollection *global_atoms;

void atom_collection_init();
void atom_collection_get();
pid_t atom_collection_get_pid(int index);
void atom_collection_add_pid(pid_t pid);
void atom_collection_delete_pid(pid_t pid);
void atom_collection_remove();

#endif  // !ATOM_COLLECTION_H
