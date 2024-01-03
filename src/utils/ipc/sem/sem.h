#ifndef SEM_H
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

sem_t *CreateSem(const char *sem_name, unsigned int initial_value);
sem_t *GetSem(const char *sem_name);
void AcquireSem(const char *sem_name);
void ReleaseSem(const char *sem_name);
void UnlinkSem(const char *sem_name);
void DestroySem(const char *sem_name);

#endif // !SEM_H
