#include "sem.h"

#include <sys/semaphore.h>

#include "../../io/logger/error_logger.h"

#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

sem_t *sem_create(const char *sem_name, unsigned int initial_value) {
    sem_t *semaphore = sem_open(sem_name, O_CREAT | O_EXCL | SEM_PERMS,
                                0xffffffff, initial_value);

    if (semaphore == SEM_FAILED) {
        return NULL;
    }

    return semaphore;
}

sem_t *sem_get(const char *sem_name) {
    sem_t *semaphore = sem_open(sem_name, O_RDWR);

    if (semaphore == SEM_FAILED) {
        return NULL;
    }

    return semaphore;
}

void sem_acquire(const char *sem_name) {
    if (sem_wait(sem_get(sem_name)) < 0) {
        ERRLOG("sem_acquire()");
        exit(EXIT_FAILURE);
    }
}

void sem_release(const char *sem_name) {
    if (sem_post(sem_get(sem_name)) < 0) {
        ERRLOG("sem_release()");
        exit(EXIT_FAILURE);
    }
}

void sem_remove(const char *sem_name) { sem_unlink(sem_name); }
