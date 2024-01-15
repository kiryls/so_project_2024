#ifndef SHMEM_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * returns NULL or a valid shared memory pointer
 */
void *shmem_create(const char *shmem_name, size_t size);

/**
 * returns NULL or a valid shared memory pointer
 */
void *shmem_get(const char *shmem_name, size_t size);

/**
 * returns true if shm_unlink succeded, false otherwise
 */
void shmem_remove(const char *shmem_name);

#endif  // !SHMEM_H
