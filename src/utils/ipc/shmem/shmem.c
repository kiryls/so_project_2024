#include "shmem.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#include "../../io/logger/error_logger.h"

void *shmem_create(const char *shmem_name, size_t size) {
    int shmem_fd = shm_open(shmem_name, O_CREAT | O_EXCL | O_RDWR, 0666);
    if (shmem_fd < 0) {
        char arg[1024];
        sprintf(arg,
                "ERROR: in file %s, line %d - couldn't shm_open(%s, O_CREAT)\n",
                __FILE__, __LINE__, shmem_name);
        ERRLOG(arg);
        return NULL;
    }

    if (ftruncate(shmem_fd, size) < 0) {
        return NULL;
    }

    void *shmem_ptr =
        mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd, 0);
    if (shmem_ptr == MAP_FAILED) {
        return NULL;
    }

    return shmem_ptr;
}

void *shmem_get(const char *shmem_name, size_t size) {
    int shmem_fd = shm_open(shmem_name, O_RDWR, 0);
    if (shmem_fd < 0) {
        char arg[1024];
        sprintf(arg, "ERROR: in file %s, line %d - couldn't shm_open(%s)\n",
                __FILE__, __LINE__, shmem_name);
        ERRLOG(arg);
        return NULL;
    }

    void *shmem_ptr =
        mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd, 0);
    if (shmem_ptr == MAP_FAILED) {
        return NULL;
    }

    return shmem_ptr;
}

void shmem_remove(const char *shmem_name) { shm_unlink(shmem_name); }
