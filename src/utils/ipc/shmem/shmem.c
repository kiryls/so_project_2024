#include "shmem.h"
#include "../../io/logger/error_logger.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

void *CreateShMem(const char *shmem_name, size_t size) {
    int shmem_fd = shm_open(shmem_name, O_CREAT | O_EXCL | O_RDWR, 0666);
    if (shmem_fd < 0) {
        ERRLOG("CreateShMem(%s).shm_open()", shmem_name);
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shmem_fd, size) < 0) {
        ERRLOG("CreateShMem(%s).ftruncate()", shmem_name);
        exit(EXIT_FAILURE);
    }

    void *shmem_ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd, 0);
    if (shmem_ptr == MAP_FAILED) {
        ERRLOG("CreateShMem(%s).mmap()", shmem_name);
        exit(EXIT_FAILURE);
    }

    return shmem_ptr;
}

void *GetShMem(const char *shmem_name, size_t size) {
    int shmem_fd = shm_open(shmem_name, O_RDWR, 0);
    if (shmem_fd < 0) {
        ERRLOG("GetShMem(%s).shm_open()", shmem_name);
        exit(EXIT_FAILURE);
    }
   
    void *shmem_ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd, 0);
    if (shmem_ptr == MAP_FAILED) {
        ERRLOG("GetShMem(%s).mmap()", shmem_name);
        exit(EXIT_FAILURE);
    }

    return shmem_ptr;
}

void UnlinkShMem(const char *shmem_name) {
    if(shm_unlink(shmem_name) < 0) {
        ERRLOG("UnlinkShMem(%s).shm_unlink()", shmem_name);
    }
}
