#include "signals.h"
#include "../io/logger/error_logger.h"

void SetSignal(int signal, SignalHandler handler, bool restart) {
    struct sigaction action;

    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);

    if (restart) {
        action.sa_flags = SA_RESTART;
    }

    if (sigaction(signal, &action, NULL) < 0) {
        ERRLOG("ERROR: SetSignal(sig_code = %d)", signal);
    }
}
