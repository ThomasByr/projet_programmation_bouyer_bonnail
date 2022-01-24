#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word.h"

void word(char *word, hset_t *nodes) {
    hset_itr_t *itr = hset_itr_new(nodes);

    while (hset_itr_has_next(itr)) {
        node_t *node = (node_t *)hset_itr_value(itr);
        dict_itr_t *itr_papers = node->papers;

        while (dict_itr_has_next(itr_papers)) {
            char *title = (char *)dict_itr_key(itr_papers);
            if (strstr(title, word) != NULL) {
                printf("%s\n", node->name);
            }
            dict_itr_next(itr_papers);
        }
        hset_itr_next(itr);
    }
    hset_itr_free(itr);
}
