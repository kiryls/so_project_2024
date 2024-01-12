#include "random.h"

#include <stdlib.h>

// lower & upper included
int random_get(unsigned int lower, unsigned int upper) {
    return arc4random() % (upper - lower + 1) + lower;
}
