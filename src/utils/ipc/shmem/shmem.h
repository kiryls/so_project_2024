#ifndef SHMEM_H

#include <stdlib.h>

void *shmem_create(const char *shmem_name, size_t size);
void *shmem_get(const char *shmem_name, size_t size);
void shmem_remove(const char *shmem_name);

#endif  // !SHMEM_H
