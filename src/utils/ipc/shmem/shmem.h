#ifndef SHMEM_H

#include <stdlib.h>

void *CreateShMem(const char *shmem_name, size_t size);
void *GetShMem(const char *shmem_name, size_t size);
void UnlinkShMem(const char *shmem_name);

#endif // !SHMEM_H
