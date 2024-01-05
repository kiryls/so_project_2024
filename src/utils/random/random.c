#include "random.h"
#include <stdlib.h>

// lower & upper included
int Rand(unsigned int lower, unsigned int upper) {
    return arc4random() % (upper - lower + 1) + lower;
}
