#ifndef ERROR_LOGGER_H

#define ERRLOG(arg)                                                          \
    {                                                                        \
        char errormsg[1024];                                                 \
        sprintf(errormsg, "ERROR: in file '%s' at line %d for %s", __FILE__, \
                __LINE__, arg);                                              \
        perror(errormsg);                                                    \
    }

#endif  // !ERROR_LOGGER_H
