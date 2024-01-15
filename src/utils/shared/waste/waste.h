#ifndef WASTE_H

#include <stdbool.h>

#include "../../ipc/sem/sem.h"
#include "../../ipc/shmem/shmem.h"

extern int *global_waste;

void system_waste_init();
void system_waste_get();
void system_waste_add(int atomic_number);
void system_waste_remove();

#endif  // !WASTE_H
