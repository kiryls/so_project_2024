#include "sem.h"
#include <semaphore.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/semaphore.h>

#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

sem_t *CreateSem(const char *sem_name, unsigned int initial_value) {
    sem_t *semaphore = sem_open(sem_name, O_CREAT | O_EXCL | SEM_PERMS, initial_value);
    
    if (semaphore == SEM_FAILED) {
        fprintf(stderr, "CreateSem(%s) failed\n", sem_name);
        exit(EXIT_FAILURE);
    }

    return semaphore;
}

sem_t *GetSem(const char *sem_name) {
    sem_t *semaphore = sem_open(sem_name, O_RDWR);

    if (semaphore == SEM_FAILED) {
        fprintf(stderr, "GetSem(%s) failed\n", sem_name);
        exit(EXIT_FAILURE);
    }

    return semaphore;
}

void AcquireSem(const char *sem_name) {
    if(sem_wait(GetSem(sem_name)) < 0) {
        fprintf(stderr, "AcquireSem(%s) failed\n", sem_name);
        exit(EXIT_FAILURE);
    }
}

void ReleaseSem(const char *sem_name) {
    if(sem_post(GetSem(sem_name)) < 0) {
        fprintf(stderr, "ReleaseSem(%s) failed\n", sem_name);
        exit(EXIT_FAILURE);
    }
}

void CloseSem(const char *sem_name) {
    if(sem_post(GetSem(sem_name)) < 0) {
        fprintf(stderr, "CloseSem(%s) failed\n", sem_name);
        exit(EXIT_FAILURE);
    }
}

void UnlinkSem(const char *sem_name) {
    if(sem_post(GetSem(sem_name)) < 0) {
        fprintf(stderr, "UnlinkSem(%s) failed\n", sem_name);
        exit(EXIT_FAILURE);
    }
}
