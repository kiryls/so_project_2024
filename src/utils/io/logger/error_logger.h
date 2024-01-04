#ifndef ERROR_LOGGER_H


#define ERRLOG(...)    \
    {                                           \
        char errormsg[256];                     \
        sprintf(errormsg, "ERROR: ");           \
        sprintf(errormsg+7, __VA_ARGS__);       \
        perror(errormsg);                       \
    }

#endif // !ERROR_LOGGER_H
