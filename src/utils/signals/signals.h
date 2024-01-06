#ifndef SIGNALS_H

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>

#define EVENT_SPLIT         SIGUSR1
#define EVENT_TERMINATION   SIGTERM

typedef void (*SignalHandler)(int);

void SetSignal(int signal, SignalHandler handler, bool restart);

#endif // !SIGNALS_H
