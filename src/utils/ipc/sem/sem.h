#ifndef SEM_H
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

sem_t *sem_create(const char *sem_name, unsigned int initial_value);
sem_t *sem_get(const char *sem_name);
void sem_acquire(const char *sem_name);
void sem_release(const char *sem_name);
void sem_remove(const char *sem_name);

#endif  // !SEM_H
