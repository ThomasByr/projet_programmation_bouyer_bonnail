#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "info.h"

void info(node_t *author) {
    dict_itr_t *itr = author->papers;
    dict_itr_reset(itr);
    while (dict_itr_has_next(itr)) {
        printf("%s\n", (char *)dict_itr_key(itr));
        dict_itr_next(itr);
    }
    return;
}
