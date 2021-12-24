#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

static const unsigned int prime_1 = 73;
static const unsigned int prime_2 = 5009;

dict_t *dict_new(void) {
    dict_t *d = calloc(1, sizeof(struct dict_s));

    if (d == NULL) // out of memory
        return NULL;

    d->nbits = 3;                                    // 2^3 = 8 buckets
    d->capacity = (size_t)(1 << d->nbits);           // is increased when needed
    d->mask = d->capacity - 1;                       // 2^3 - 1 = 7
    d->keys = calloc(d->capacity, sizeof(size_t));   // keys array
    d->values = calloc(d->capacity, sizeof(void *)); // values array

    if (d->keys == NULL || d->values == NULL) {
        dict_free(d);
        return NULL;
    }
    d->nitems = 0;          // no items yet
    d->n_deleted_items = 0; // no deleted items yet
    return d;
}

void dict_free(dict_t *d) {
    if (d) {
        free(d->keys);
        free(d->values);
    }
    free(d);
}

int _dict_push_item(dict_t *dict, void *key, void *value) {
    size_t k = (size_t)key; // cast key to size_t
    // size_t v = (size_t)value; // cast value to size_t
    size_t ii; // index of the bucket

    if (k == 0 || k == 1) // if key casts to 0 or 1
        return -1;        // return error

    ii = dict->mask & (prime_1 * k); // hash value modulo capacity

    while (dict->keys[ii] != 0 &&
           dict->keys[ii] != 1) // find empty or deleted bucket
    {
        if (dict->keys[ii] == k) {    // if key is already in set
            dict->values[ii] = value; // update value
            return 0;                 // return success 0
        } else {
            ii = dict->mask & (ii + prime_2); // get index of next bucket
        }
    }
    dict->nitems++;              // increase number of items
    if (dict->keys[ii] == 1)     // if bucket is deleted
        dict->n_deleted_items--; // decrease number of deleted items

    dict->keys[ii] = k;       // insert key
    dict->values[ii] = value; // insert value
    return 1;                 // return success 1
}

static void _maybe_rehash(dict_t *dict) {
    size_t *old_keys;        // old keys array
    void **old_values;       // old values array
    size_t old_capacity, ii; // old capacity, index of the bucket

    if (dict->nitems + dict->n_deleted_items >= (double)dict->capacity * 0.85) {
        old_keys = dict->keys;
        old_values = dict->values;
        old_capacity = dict->capacity;
        dict->nbits++;
        dict->capacity = (size_t)(1 << dict->nbits);
        dict->mask = dict->capacity - 1;
        dict->keys = calloc(dict->capacity, sizeof(size_t));
        dict->values = calloc(dict->capacity, sizeof(void *));

        dict->nitems = 0;
        dict->n_deleted_items = 0;
        assert(dict->keys);
        for (ii = 0; ii < old_capacity; ii++) {
            if (old_keys[ii] != 0 && old_keys[ii] != 1) {
                _dict_push_item(dict, (void *)old_keys[ii], old_values[ii]);
            }
        }
        free(old_keys);
        free(old_values);
    }
}

int dict_push(dict_t *dict, void *key, void *value) {
    if (dict == NULL) // if dict is NULL
        return -1;    // return error

    int rv = _dict_push_item(dict, key, value); // insert item
    _maybe_rehash(dict);                        // maybe rehash
    return rv;                                  // return result
}

void *dict_get(dict_t *dict, void *key) {
    size_t k = (size_t)key; // cast key to size_t
    size_t ii;              // index of the bucket

    if (dict == NULL || k == 0 ||
        k == 1)      // if dict is NULL or key casts to 0 or 1
        return NULL; // return NULL

    ii = dict->mask & (prime_1 * k); // hash value modulo capacity

    while (dict->keys[ii] != 0 &&
           dict->keys[ii] != 1) // find empty or deleted bucket
    {
        if (dict->keys[ii] == k) {   // if key is found
            return dict->values[ii]; // return value
        } else {
            ii = dict->mask & (ii + prime_2); // get index of next bucket
        }
    }
    return NULL; // return NULL if key is not found
}

int dict_discard(dict_t *dict, void *key) {
    size_t k = (size_t)key; // cast key to size_t
    size_t ii;              // index of the bucket

    if (dict == NULL || k == 0 ||
        k == 1)    // if dict is NULL or key casts to 0 or 1
        return -1; // return error

    ii = dict->mask & (prime_1 * k); // hash value modulo capacity

    while (dict->keys[ii] != 0 &&
           dict->keys[ii] != 1) // find empty or deleted bucket
    {
        if (dict->keys[ii] == k) {   // if key is found
            dict->keys[ii] = 1;      // mark bucket as deleted
            dict->nitems--;          // decrease number of items
            dict->n_deleted_items++; // increase number of deleted items
            return 1;                // return success 1
        } else {
            ii = dict->mask & (ii + prime_2); // get index of next bucket
        }
    }
    return 0; // return error if key is not found
}

size_t dict_nitems(dict_t *dict) { return dict->nitems; }
