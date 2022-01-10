#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "info.h"

void info(node_t *author) {
    hset_itr_t *itr = author->papers;
    while (hset_itr_has_next(itr)) {
        printf("%s\n", (char *)hset_itr_value(itr));
        hset_itr_next(itr);
    }
    return;
}
