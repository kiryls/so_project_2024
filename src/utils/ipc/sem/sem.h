#ifndef SEM_H
#include <fcntl.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * returns NULL or a valid semaphore pointer
 */
sem_t *sem_create(const char *sem_name, unsigned int initial_value);

/**
 * returns NULL or a valid semaphore pointer
 */
sem_t *sem_get(const char *sem_name);

/**
 * does exit if sem_wait() returns -1
 */
void sem_acquire(const char *sem_name);

/**
 * does exit if sem_wait() returns -1
 */
void sem_release(const char *sem_name);

/**
 * returns nothing
 */
void sem_remove(const char *sem_name);

#endif  // !SEM_H
