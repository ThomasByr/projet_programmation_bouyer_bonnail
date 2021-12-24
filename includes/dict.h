/*

*/

#ifndef DICT_H
#define DICT_H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

struct dict_s {
    size_t nbits;
    size_t mask;

    size_t capacity;
    size_t *keys;
    void **values;
    size_t nitems;
    size_t n_deleted_items;
};

typedef struct dict_s dict_t;

dict_t *dict_new(void);

void dict_destroy(dict_t *dict);

int dict_push(dict_t *dict, void *key, void *value);

void *dict_get(dict_t *dict, void *key);

int dict_discard(dict_t *dict, void *key);

size_t dict_nitems(dict_t *dict);

#endif
