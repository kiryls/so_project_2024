#include "shmem.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#include "../../io/logger/error_logger.h"

void *shmem_create(const char *shmem_name, size_t size) {
    int shmem_fd = shm_open(shmem_name, O_CREAT | O_EXCL | O_RDWR, 0666);
    if (shmem_fd < 0) {
        ERRLOG("shmem_create().shm_open()");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shmem_fd, size) < 0) {
        ERRLOG("shmem_create().ftruncate()");
        exit(EXIT_FAILURE);
    }

    void *shmem_ptr =
        mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd, 0);
    if (shmem_ptr == MAP_FAILED) {
        ERRLOG("shmem_create().mmap()");
        exit(EXIT_FAILURE);
    }

    return shmem_ptr;
}

void *shmem_get(const char *shmem_name, size_t size) {
    int shmem_fd = shm_open(shmem_name, O_RDWR, 0);
    if (shmem_fd < 0) {
        ERRLOG("shmem_get().shm_open()");
        // exit(EXIT_FAILURE);
        return NULL;
    }

    void *shmem_ptr =
        mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd, 0);
    if (shmem_ptr == MAP_FAILED) {
        ERRLOG("shmem_get().mmap()");
        exit(EXIT_FAILURE);
    }

    return shmem_ptr;
}

void shmem_remove(const char *shmem_name) {
    if (shm_unlink(shmem_name) < 0) {
        ERRLOG("shmem_remove()");
    }
}
