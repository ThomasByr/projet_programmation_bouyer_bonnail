#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hset.h"

static const unsigned int prime_1 = 3079;
static const unsigned int prime_2 = 1572869;

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

hset_t *hset_create(void)
{
    hset_t *set = calloc(1, sizeof(struct hset_s));

    if (set == NULL) // out of memory
        return NULL;

    set->nbits = 3;                                     // 2^3 = 8 buckets
    set->capacity = (size_t)(1 << set->nbits);          // is increased when needed
    set->mask = set->capacity - 1;                      // 2^3 - 1 = 7
    set->items = calloc(set->capacity, sizeof(size_t)); // items array
    if (set->items == NULL)
    {
        hset_destroy(set);
        return NULL;
    }
    set->nitems = 0;          // no items yet
    set->n_deleted_items = 0; // no deleted items yet
    return set;
}

void hset_destroy(hset_t *set)
{
    if (set)              // if set is not NULL
        free(set->items); // free items array
    free(set);            // free set
}

int _hset_insert_item(hset_t *set, void *item)
{
    size_t value = (size_t)item; // cast item to size_t
    size_t ii;                   // index of the bucket

    if (value == 0 || value == 1) // if item casts to 0 or 1
        return -1;                // return error

    ii = set->mask & (prime_1 * value); // hash value modulo capacity

    while (set->items[ii] != 0 && set->items[ii] != 1)
    {
        if (set->items[ii] == value)
            return 0;
        else
            ii = set->mask & (ii + prime_2);
    }
    set->nitems++;
    if (set->items[ii] == 1)
        set->n_deleted_items--;

    set->items[ii] = value;
    return 1;
}

static void _maybe_rehash(hset_t *set)
{
    size_t *old_items;
    size_t old_capacity, ii;

    if (set->nitems + set->n_deleted_items >= (double)set->capacity * 0.85)
    {
        old_items = set->items;
        old_capacity = set->capacity;
        set->nbits++;
        set->capacity = (size_t)(1 << set->nbits);
        set->mask = set->capacity - 1;
        set->items = calloc(set->capacity, sizeof(size_t));
        set->nitems = 0;
        set->n_deleted_items = 0;
        assert(set->items);
        for (ii = 0; ii < old_capacity; ii++)
            _hset_insert_item(set, (void *)old_items[ii]);
        free(old_items);
    }
}

int hset_insert(hset_t *set, void *item)
{
    int rv = _hset_insert_item(set, item);
    _maybe_rehash(set);
    return rv;
}

int hset_constains(hset_t *set, void *item)
{

    size_t value = (size_t)item;
    size_t ii = set->mask & (prime_1 * value);

    while (set->items[ii] != 0)
    {
        if (set->items[ii] == value)
            return 1;
        else
            ii = set->mask & (ii + prime_2);
    }
    return 0;
}

int hset_discard(hset_t *set, void *item)
{

    size_t value = (size_t)item;
    size_t ii = set->mask & (prime_1 * value);

    while (set->items[ii] != 0)
    {
        if (set->items[ii] == value)
        {
            set->items[ii] = 1;
            set->nitems--;
            set->n_deleted_items++;
            return 1;
        }
        else
            ii = set->mask & (ii + prime_2);
    }
    return 0;
}

size_t hset_nitems(hset_t *set)
{
    return set->nitems;
}
