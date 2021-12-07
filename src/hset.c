#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hset.h"

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}
