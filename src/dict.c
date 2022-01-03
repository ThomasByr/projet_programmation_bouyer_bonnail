#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

static const unsigned int prime_1 = 3079;
static const unsigned int prime_2 = 1572869;

dict_t *dict_new(void) {
    dict_t *d = calloc(1, sizeof(struct dict_s));

    if (d == NULL) // out of memory
        return NULL;

    d->nbits = 3;                                    // 2^3 = 8 buckets
    d->capacity = (size_t)(1 << d->nbits);           // is increased when needed
    d->mask = d->capacity - 1;                       // 2^3 - 1 = 7
    d->keys = calloc(d->capacity, sizeof(size_t));   // keys array
    d->values = calloc(d->capacity, sizeof(size_t)); // values array

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
    size_t k = (size_t)key;   // cast key to size_t
    size_t v = (size_t)value; // cast value to size_t
    size_t ii;                // index of the bucket

    if (k == 0 || k == 1) // if key casts to 0 or 1
        return -1;        // return error

    ii = dict->mask & (prime_1 * k); // hash value modulo capacity

    while (dict->keys[ii] != 0 &&
           dict->keys[ii] != 1) // find empty or deleted bucket
    {
        if (dict->keys[ii] == k) { // if key is already in set
            dict->values[ii] = v;  // update value
            return 0;              // return success 0
        } else {
            ii = dict->mask & (ii + prime_2); // get index of next bucket
        }
    }
    dict->nitems++;              // increase number of items
    if (dict->keys[ii] == 1)     // if bucket is deleted
        dict->n_deleted_items--; // decrease number of deleted items

    dict->keys[ii] = k;   // insert key
    dict->values[ii] = v; // insert value
    return 1;             // return success 1
}

static int _maybe_rehash(dict_t *dict) {
    size_t *old_keys;        // old keys array
    size_t *old_values;      // old values array
    size_t old_capacity, ii; // old capacity, index of the bucket

    if (dict->nitems + dict->n_deleted_items >= (double)dict->capacity * 0.85) {
        old_keys = dict->keys;
        old_values = dict->values;
        old_capacity = dict->capacity;
        dict->nbits++;
        dict->capacity = (size_t)(1 << dict->nbits);
        dict->mask = dict->capacity - 1;
        dict->keys = calloc(dict->capacity, sizeof(size_t));
        dict->values = calloc(dict->capacity, sizeof(size_t));
        if (dict->keys == NULL || dict->values == NULL) {
            free(dict->keys);
            free(dict->values);
            dict->keys = old_keys;
            dict->values = old_values;
            dict->capacity = old_capacity;
            dict->nbits--;
            return 2;
        }

        dict->nitems = 0;
        dict->n_deleted_items = 0;
        ASSERT(dict->keys);
        ASSERT(dict->values);
        for (ii = 0; ii < old_capacity; ii++) {
            if (old_keys[ii] != 0 && old_keys[ii] != 1) {
                _dict_push_item(dict, (void *)old_keys[ii],
                                (void *)old_values[ii]);
            }
        }
        free(old_keys);
        free(old_values);
    }
    return 1;
}

int dict_push(dict_t *dict, void *key, void *value) {
    if (dict == NULL) // if dict is NULL
        return -1;    // return error

    int rv = _dict_push_item(dict, key, value); // insert item
    int r = _maybe_rehash(dict);                // rehash if needed
    return rv == 1 ? r : rv;
}

size_t dict_get(dict_t *dict, void *key) {
    size_t k = (size_t)key; // cast key to size_t
    size_t ii;              // index of the bucket

    if (dict == NULL || k == 0 ||
        k == 1)    // if dict is NULL or key casts to 0 or 1
        return -1; // return NULL

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
    return 0; // return 0 if key is not found
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

dict_itr_t *dict_itr_new(dict_t *dict) {
    dict_itr_t *itr = calloc(1, sizeof(dict_itr_t));
    if (itr == NULL)
        return NULL;
    itr->dict = dict;
    itr->index = 0;
    return itr;
}

int dict_itr_has_next(dict_itr_t *itr) {
    size_t index;

    // either there are no items or we are at the end of the dict
    if (itr->dict->nitems == 0 || itr->index >= itr->dict->capacity)
        return 0;

    index = itr->index;
    while (index < itr->dict->capacity) {
        size_t value = itr->dict->keys[index++];
        if (value != 0)
            return 1;
    }
    return 0;
}

size_t dict_itr_next(dict_itr_t *itr) {
    if (dict_itr_has_next(itr) == 0)
        return -1;

    itr->index++;
    while (itr->index < itr->dict->capacity &&
           itr->dict->keys[(itr->index)] == 0)
        itr->index++;

    return itr->index;
}

size_t dict_itr_key(dict_itr_t *itr) {
    if (itr->dict->keys[itr->index] == 0)
        dict_itr_next(itr);

    return itr->dict->keys[itr->index];
}

size_t dict_itr_value(dict_itr_t *itr) {
    if (itr->dict->keys[itr->index] == 0)
        dict_itr_next(itr);

    return itr->dict->values[itr->index];
}

void dict_itr_free(dict_itr_t *itr) {
    if (itr == NULL)
        return;
    free(itr);
}

void dict_itr_reset(dict_itr_t *itr) { itr->index = 0; }
