#include "shmem.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

void *CreateShMem(const char *shmem_name, size_t size) {
    int shmem_fd = shm_open(shmem_name, O_CREAT | O_EXCL | O_RDWR, 0666);
    if (shmem_fd < 0) {
        fprintf(stderr, "CreateShMem(%s).shm_open() failed\n", shmem_name);
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shmem_fd, size) < 0) {
        fprintf(stderr, "CreateShMem(%s).ftruncate() failed\n", shmem_name);
        exit(EXIT_FAILURE);
    }

    void *shmem_ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd, 0);
    if (shmem_ptr == MAP_FAILED) {
        fprintf(stderr, "CreateShMem(%s).mmap() failed\n", shmem_name);
        exit(EXIT_FAILURE);
    }

    return shmem_ptr;
}

void *GetShMem(const char *shmem_name, size_t size) {
    int shmem_fd = shm_open(shmem_name, O_RDWR, 0);
    if (shmem_fd < 0) {
        fprintf(stderr, "GetShMem(%s).shm_open() failed\n", shmem_name);
        exit(EXIT_FAILURE);
    }
   
    void *shmem_ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd, 0);
    if (shmem_ptr == MAP_FAILED) {
        fprintf(stderr, "GetShMem(%s).mmap() failed\n", shmem_name);
        exit(EXIT_FAILURE);
    }

    return shmem_ptr;
}

void UnlinkShMem(const char *shmem_name) {
    shm_unlink(shmem_name);
}
