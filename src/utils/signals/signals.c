#include "signals.h"

#include "../io/logger/error_logger.h"

void signal_set(int signal, SignalHandler handler, bool restart) {
    struct sigaction action;

    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);

    if (restart) {
        action.sa_flags = SA_RESTART;
    }

    if (sigaction(signal, &action, NULL) < 0) {
        ERRLOG("signal_set().sigaction()");
    }
}

char *signal_to_str(int signal) {
    if (signal == SIG_SPLIT) {
        return "SPLIT";
    }

    if (signal == SIG_TERMINATION) {
        return "TERMINATION";
    }

    return "";
}
