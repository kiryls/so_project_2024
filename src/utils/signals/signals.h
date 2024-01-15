#ifndef SIGNALS_H

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>

#define SIG_SPLIT SIGUSR1
#define SIG_TERMINATION SIGALRM

typedef void (*SignalHandler)(int);

void signal_set(int signal, SignalHandler handler, bool restart);
char *signal_to_str(int signal);

#endif  // !SIGNALS_H
