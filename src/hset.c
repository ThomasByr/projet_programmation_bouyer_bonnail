#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hset.h"

static const unsigned int prime_1 = 3079;
static const unsigned int prime_2 = 1572869;

hset_t *_hset_new_args(hset_args_t args) {
    int hash_content = args.hash_content ? args.hash_content : 0;
    return _hset_new(hash_content);
}

hset_t *_hset_new(int hash_content) {
    hset_t *set = calloc(1, sizeof(struct hset_s));

    if (set == NULL) // out of memory
        return NULL;

    set->hash_content = hash_content;
    set->nbits = 3;                            // 2^3 = 8 buckets
    set->capacity = (size_t)(1 << set->nbits); // is increased when needed
    set->mask = set->capacity - 1;             // 2^3 - 1 = 7
    set->items = calloc(set->capacity, sizeof(size_t)); // items array
    if (set->items == NULL) {
        hset_free(set);
        return NULL;
    }
    set->nitems = 0;          // no items yet
    set->n_deleted_items = 0; // no deleted items yet
    return set;
}

hset_t *hset_copy(hset_t *hset) {
    hset_t *set = calloc(1, sizeof(struct hset_s));
    if (set == NULL)
        return NULL;

    set->nbits = hset->nbits;
    set->capacity = hset->capacity;
    set->mask = hset->mask;
    set->items = calloc(set->capacity, sizeof(size_t));
    if (set->items == NULL) {
        free(set);
        return NULL;
    }
    set->nitems = hset->nitems;
    set->n_deleted_items = hset->n_deleted_items;
    size_t n = set->capacity * sizeof(size_t);
    void *dest = memcpy(set->items, hset->items, n);
    ASSERT(dest);
    ASSERT(dest == set->items);
    return set;
}

void hset_free(hset_t *set) {
    if (set == NULL)
        return;
    free(set->items); // free items array
    free(set);        // free set
}

void hset_reset(hset_t *hset) {
    if (hset == NULL)
        return;
    hset->nitems = 0;
    hset->n_deleted_items = 0;
    memset(hset->items, 0, hset->capacity * sizeof(size_t));
}

int _hset_push_item(hset_t *set, void *item) {
    size_t value;
    switch (set->hash_content) {
    case 0:
        value = (size_t)item; // cast item to size_t
        break;
    case 1:
    default:
        value = hash((char *)item); // hash item before casting
        break;
    }
    size_t ii; // index of the bucket

    if (value == 0 || value == 1) // if item casts to 0 or 1
        return -1;                // return error

    ii = set->mask & (prime_1 * value); // hash value modulo capacity

    while (set->items[ii] != 0 &&
           set->items[ii] != 1) // find empty or deleted bucket
    {
        // if item is already in set
        if (compare(set->hash_content, set->items[ii], (size_t)item))
            return 0;                        // return failure
        else                                 // else
            ii = set->mask & (ii + prime_2); // get index of next bucket
    }
    set->nitems++;              // increase number of items
    if (set->items[ii] == 1)    // if bucket is deleted
        set->n_deleted_items--; // decrease number of deleted items

    set->items[ii] = (size_t)item; // insert item
    return 1;                      // return success
}

static int _maybe_rehash(hset_t *set) {
    size_t *old_items;       // old items array
    size_t old_capacity, ii; // old capacity, index of the bucket

    // if load factor is greater than 0.85, increase capacity and rehash
    if (set->nitems + set->n_deleted_items >= (double)set->capacity * 0.85) {
        old_items = set->items;
        old_capacity = set->capacity;
        set->nbits++;
        set->capacity = (size_t)(1 << set->nbits);
        set->mask = set->capacity - 1;
        set->items = calloc(set->capacity, sizeof(size_t));
        if (set->items == NULL) {
            set->nbits--;
            set->capacity = (size_t)(1 << set->nbits);
            set->mask = set->capacity - 1;
            set->items = old_items;
            return 2;
        }

        set->nitems = 0;
        set->n_deleted_items = 0;
        ASSERT(set->items);
        for (ii = 0; ii < old_capacity; ii++)
            _hset_push_item(set, (void *)old_items[ii]);
        free(old_items);
    }
    return 1;
}

int hset_push(hset_t *set, void *item) {
    int rv = _hset_push_item(set, item); // insert item
    int r = _maybe_rehash(set);          // rehash if needed
    return rv == 1 ? r : rv;
}

int hset_contains(hset_t *set, void *item) {
    if (item == NULL)
        return 0; // return error

    size_t value;
    switch (set->hash_content) {
    case 0:
        value = (size_t)item; // cast item to size_t
        break;
    case 1:
    default:
        value = hash((char *)item); // hash item before casting
        break;
    }

    // if set is NULL or item casts to 0 or 1
    if (set == NULL || value == 0 || value == 1)
        return 0; // return error

    size_t ii = set->mask & (prime_1 * value); // hash value modulo capacity

    // continue searching for item until empty bucket is found
    while (set->items[ii] != 0) {
        // if item is already in set
        if (compare(set->hash_content, set->items[ii], (size_t)item))
            return 1;                        // return success
        else                                 // else
            ii = set->mask & (ii + prime_2); // get index of next bucket
    }
    return 0; // return failure
}

int hset_discard(hset_t *set, void *item) {
    if (set == NULL || item == NULL)
        return 0; // return error

    size_t value;
    switch (set->hash_content) {
    case 0:
        value = (size_t)item; // cast item to size_t
        break;
    case 1:
    default:
        value = hash((char *)item); // hash item before casting
        break;
    }

    // if set is NULL or value casts to 0 or 1
    if (set == NULL || value == 0 || value == 1)
        return -1; // return error

    size_t ii = set->mask & (prime_1 * value); // hash value modulo capacity

    // continue searching for item until empty bucket is found
    while (set->items[ii] != 0) {
        // if item is already in set
        if (compare(set->hash_content, set->items[ii], (size_t)item)) {
            set->items[ii] = 1;              // mark bucket as deleted
            set->nitems--;                   // decrease number of items
            set->n_deleted_items++;          // increase number of deleted items
            return 1;                        // return success
        } else                               // else
            ii = set->mask & (ii + prime_2); // get index of next bucket
    }
    return 0; // return failure
}

size_t hset_pop(hset_t *hset) {
    size_t ii, value;

    if (hset->nitems == 0) // if set is empty
        return 0;          // return failure

    for (ii = 0; ii < hset->capacity; ii++) {
        if (hset->items[ii] != 0 && hset->items[ii] != 1) {
            value = hset->items[ii];
            hset->items[ii] = 1;
            hset->nitems--;
            hset->n_deleted_items++;
            return value;
        }
    }
    ASSERT(hset->nitems == 0); // should not even occur
    return 0;
}

size_t hset_nitems(hset_t *set) { return set->nitems; }

hset_itr_t *hset_itr_new(hset_t *set) {
    hset_itr_t *itr = calloc(1, sizeof(struct hset_itr_s));
    if (itr == NULL)
        return NULL;

    itr->set = set;
    itr->index = 0;

    // if (set->nitems > 0)
    //     hset_itr_next(itr);
    return itr;
}

int hset_itr_has_next(hset_itr_t *itr) {
    size_t index;

    // either there are no items or we are at the end of the set
    if (itr->set->nitems == 0 || itr->index >= itr->set->capacity)
        return 0;

    index = itr->index; // don't modify itr->index
    while (index < itr->set->capacity) {
        size_t value = itr->set->items[index++]; // get value at index
        if (value != 0 && value != 1)            // if value is a valid item
            return 1;                            // return success
    }
    return 0; // return failure
}

size_t hset_itr_next(hset_itr_t *itr) {
    if (hset_itr_has_next(itr) == 0) // if there are no more items
        return -1;                   // return failure

    itr->index++; // increase index
    while (itr->index < itr->set->capacity &&
           (itr->set->items[(itr->index)] == 0 ||
            itr->set->items[(itr->index)] == 1))
        itr->index++;

    return itr->index; // return index
}

size_t hset_itr_value(hset_itr_t *itr) {
    // if value is not a valid item
    if (itr->set->items[itr->index] == 0 || itr->set->items[itr->index] == 1)
        hset_itr_next(itr); // get next valid value

    return itr->set->items[itr->index]; // return value at current index
}

void hset_itr_free(hset_itr_t *itr) {
    if (itr == NULL)
        return;
    free(itr);
}

void *hset_itr_for_each(hset_itr_t *itr, for_each_callback_t *fe, void *data) {
    hset_itr_reset(itr); // reset iterator
    if (fe == NULL)
        return NULL;

    while (hset_itr_has_next(itr)) {
        void *value = (void *)hset_itr_value(itr);
        ASSERT(value);
        if (value != NULL) {
            void *p = (fe)(value, data); // call for_each_callback
            if (p != NULL)               // if callback returns non-NULL
                return p;                // return value
        }
        hset_itr_next(itr);
    } // for each valid item
    return NULL;
}

void hset_itr_discard_all(hset_itr_t *itr, delete_callback_t *dc) {
    hset_itr_reset(itr); // reset iterator

    while (hset_itr_has_next(itr)) {
        void *value = (void *)hset_itr_value(itr);
        ASSERT(value);

        if (value != NULL) {
            int p = hset_discard(itr->set, value); // remove value from set
            ASSERT(p == 1);                        // yields success
            if (dc != NULL)
                (dc)(value); // invoke delete callback
        }
        hset_itr_next(itr);
    } // for each valid item
}

void hset_itr_reset(hset_itr_t *itr) { itr->index = 0; }
