#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hset.h"

<<<<<<< HEAD
unsigned long hash(char *str)
{
=======
static const unsigned int prime_1 = 3079;
static const unsigned int prime_2 = 1572869;

unsigned long hash(char *str) {
>>>>>>> 7c92f791ee13737df0c25425f9c58acd01c9783c
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

<<<<<<< HEAD
hset_t *hset_create(size_t capacity, char *(*to_string)(void *))
{
    hset_t *hset = malloc(sizeof(hset_t));
    hset->capacity = capacity;

    void ***buckets = malloc(sizeof(void *) * capacity); // `capacity` buckets
    for (size_t i = 0; i < capacity; i++)                // initialize all buckets to NULL
        buckets[i] = malloc(sizeof(void *));             // each bucket is an array of pointers
    memset(buckets, 0, sizeof(void *) * capacity);
    hset->buckets = buckets;

    int *sizes = malloc(sizeof(int) * capacity);
    for (size_t i = 0; i < capacity; i++)
        sizes[i] = 1;
    hset->sizes = sizes;

    int *counts = malloc(sizeof(int) * capacity);
    for (size_t i = 0; i < capacity; i++)
        counts[i] = 0;
    hset->counts = counts;

    hset->to_string = to_string;

    return hset;
}

void hset_destroy(hset_t *hset)
{
    for (size_t i = 0; i < hset->capacity; i++)
        free(hset->buckets[i]);
    free(hset->buckets);
    free(hset->counts);
    free(hset->sizes);
    free(hset);
}

void hset_insert(hset_t *hset, void *data)
{
    char *str = hset->to_string(data);
    unsigned long hash_value = hash(str);

    int index = hash_value % hset->capacity;
    int size = hset->sizes[index];
    int count = hset->counts[index];

    if (count == size)
    {
        hset->sizes[index] *= 2;
        hset->buckets[index] = realloc(hset->buckets[index], sizeof(void *) * hset->sizes[index]);
    }

    for (int i = 0; i < count; i++)
    {
        if (strcmp(str, hset->buckets[index][i]) == 0)
        {
            free(str); // ?is this necessary?
            return;
        }
    }
    hset->buckets[index][count] = data;
    hset->counts[index]++;
}

int hset_contains(hset_t *hset, void *data)
{
    char *str = hset->to_string(data);
    unsigned long hash_value = hash(str);

    int index = hash_value % hset->capacity;
    int count = hset->counts[index];

    for (int i = 0; i < count; i++)
    {
        if (strcmp(str, hset->buckets[index][i]) == 0)
        {
            free(str);
            return 1;
        }
    }
    free(str);
    return 0;
}

void hset_discard(hset_t *hset, void *data)
{
    char *str = hset->to_string(data);
    unsigned long hash_value = hash(str);

    int index = hash_value % hset->capacity;
    int count = hset->counts[index];

    for (int i = 0; i < count; i++)
    {
        if (strcmp(str, hset->buckets[index][i]) == 0)
        {
            free(str);
            for (int j = i; j < count - 1; j++)
                hset->buckets[index][j] = hset->buckets[index][j + 1];
            hset->counts[index]--;
            return;
        }
    }
    free(str);
}
=======
hset_t *hset_new(void) {
    hset_t *set = calloc(1, sizeof(struct hset_s));

    if (set == NULL) // out of memory
        return NULL;

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

void hset_free(hset_t *set) {
    if (set)              // if set is not NULL
        free(set->items); // free items array
    free(set);            // free set
}

int _hset_push_item(hset_t *set, void *item) {
    size_t value = (size_t)item; // cast item to size_t
    size_t ii;                   // index of the bucket

    if (value == 0 || value == 1) // if item casts to 0 or 1
        return -1;                // return error

    ii = set->mask & (prime_1 * value); // hash value modulo capacity

    while (set->items[ii] != 0 &&
           set->items[ii] != 1) // find empty or deleted bucket
    {
        if (set->items[ii] == value)         // if item is already in set
            return 0;                        // return failure
        else                                 // else
            ii = set->mask & (ii + prime_2); // get index of next bucket
    }
    set->nitems++;              // increase number of items
    if (set->items[ii] == 1)    // if bucket is deleted
        set->n_deleted_items--; // decrease number of deleted items

    set->items[ii] = value; // insert item
    return 1;               // return success
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
    size_t value = (size_t)item;               // cast item to size_t
    size_t ii = set->mask & (prime_1 * value); // hash value modulo capacity

    while (set->items[ii] != 0) // find empty or deleted bucket
    {
        if (set->items[ii] == value)         // if item is already in set
            return 1;                        // return success
        else                                 // else
            ii = set->mask & (ii + prime_2); // get index of next bucket
    }
    return 0; // return failure
}

int hset_discard(hset_t *set, void *item) {
    size_t value = (size_t)item;               // cast item to size_t
    size_t ii = set->mask & (prime_1 * value); // hash value modulo capacity

    while (set->items[ii] != 0) // find empty or deleted bucket
    {
        if (set->items[ii] == value) // if item is already in set
        {
            set->items[ii] = 1;              // mark bucket as deleted
            set->nitems--;                   // decrease number of items
            set->n_deleted_items++;          // increase number of deleted items
            return 1;                        // return success
        } else                               // else
            ii = set->mask & (ii + prime_2); // get index of next bucket
    }
    return 0; // return failure
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

    index = itr->index; // save index
    while (index < itr->set->capacity) {
        size_t value = itr->set->items[index++]; // get value at index
        if (value != 0)                          // if value is not 0
            return 1;                            // return success
    }
    return 0; // return failure
}

size_t hset_itr_next(hset_itr_t *itr) {
    if (hset_itr_has_next(itr) == 0) // if there are no more items
        return -1;                   // return failure

    itr->index++; // increase index
    while (itr->index < itr->set->capacity &&
           itr->set->items[(itr->index)] == 0)
        itr->index++;

    return itr->index; // return index
}

size_t hset_itr_value(hset_itr_t *itr) {
    if (itr->set->items[itr->index] == 0) // if value is 0
        hset_itr_next(itr);               // get next valid value

    return itr->set->items[itr->index]; // return value at current index
}

void hset_itr_free(hset_itr_t *itr) {
    if (itr == NULL)
        return;
    free(itr);
}

void *hset_itr_for_each(hset_itr_t *itr, for_each_callback_t *fe, void *data) {
    hset_itr_reset(itr); // reset iterator

    while (hset_itr_has_next(itr)) {
        void *value = (void *)hset_itr_value(itr);
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
        if (value != NULL) {
            int p = hset_discard(itr->set, value); // remove value from set
            if (p == 0) {
                fprintf(stderr, "hset_itr_discard_all failed : yielded item "
                                "could not be found on original hash set\n");
            } else if (p == 1 && dc != NULL)
                (dc)(value); // invoke delete callback
        }
        hset_itr_next(itr);
    } // for each valid item
}

void hset_itr_reset(hset_itr_t *itr) { itr->index = 0; }
>>>>>>> 7c92f791ee13737df0c25425f9c58acd01c9783c
