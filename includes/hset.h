/*

*/

#ifndef HSET_H
#define HSET_H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

struct hset_s {
    size_t nbits;
    size_t mask;

    size_t capacity;
    size_t *items;
    size_t nitems;
    size_t n_deleted_items;
};
/**
 * @brief hash set data structure that holds a collection of unique items
 *
 */
typedef struct hset_s hset_t;

struct hset_itr_s {
    hset_t *set;
    size_t index;
};
/**
 * @brief iterator for hash set, somehow order is preserved but not guaranteed
 *
 */
typedef struct hset_itr_s hset_itr_t;

/**
 * @brief djb2 hash function by Dan Bernstein
 *
 * @param str string to hash
 * @return unsigned long
 */
unsigned long hash(char *str);

/**
 * @brief ceate a new hash set
 *
 * @return hset_t*
 */
hset_t *hset_create(void);

/**
 * @brief destroy a hash set
 *
 * @param hset
 */
void hset_destroy(hset_t *hset);

/**
 * @brief add a new element to the hash set, does nothing if already present
 *
 * @param hset hash set
 * @param item new element
 * @return int - 1 if added, 0 if already present and -1 if error
 */
int hset_insert(hset_t *hset, void *item);

/**
 * @brief test if an element is present in the hash set
 *
 * @param hset hash set
 * @param item item to check
 * @return int - 1 if present, 0 if not
 */
int hset_contains(hset_t *hset, void *item);

/**
 * @brief remove item from hash set, does nothing if not present
 *
 * @param hset hash set
 * @param item item to remove
 * @return int - 1 if removed, 0 if not present
 */
int hset_discard(hset_t *hset, void *item);

/**
 * @brief get the number of items in the hash set
 *
 * @param hset hash set
 * @return size_t - number of items
 */
size_t hset_nitems(hset_t *hset);

/**
 * @brief create a hashset iterator, advances to first value is available
 *
 * @param set hash set
 * @return hset_itr_t* - new iterator
 */
hset_itr_t *hset_itr_create(hset_t *set);

/**
 * @brief returns the value at the current index, it is the caller's
 * responsibility to cast the value
 *
 * @param itr iterator
 * @return size_t - value at current index
 */
size_t hset_itr_val(hset_itr_t *itr);

/**
 * @brief return 1 is can advance, 0 otherwise
 *
 * @param itr iterator
 * @return int
 */
int hset_itr_has_next(hset_itr_t *itr);

/**
 * @brief check if iterator can advance, if so advances
 * returns current index if can advance and -1 otherwise
 *
 * @param itr iterator
 * @return size_t
 */
size_t hset_itr_next(hset_itr_t *itr);

/**
 * @brief destroy an iterator
 *
 * @param itr iterator
 */
void hset_itr_destroy(hset_itr_t *itr);

/**
 * @brief apply a function to each item in the hash set,
 * if the function returns non-null, the iteration is stopped
 * and the value is returned
 *
 * @details it is the caller's responsibility to reset the iterator
 * after calling this function
 *
 * @param itr iterator
 * @param fe function to apply
 * @param data data to pass to function
 */
void *hset_itr_for_each(hset_itr_t *itr, for_each_callback_t *fe, void *data);

/**
 * @brief discard all items from the hash set and invoke the delete callback
 *
 * @example hset_itr_discard_all(itr, free_item);
 *
 * @param itr iterator
 * @param dc delete callback
 */
void hset_itr_discard_all(hset_itr_t *itr, delete_callback_t *dc);

/**
 * @brief reset the iterator to the beginning of the set
 *
 * @param itr iterator
 */
void hset_itr_reset(hset_itr_t *itr);

#endif
