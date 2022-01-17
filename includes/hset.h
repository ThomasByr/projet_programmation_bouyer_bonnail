/* hset.h
Collection of unique elements using a hash table.

*/

#ifndef HSET_H
#define HSET_H

#include "protocol.h"
#include "types.h"

struct hset_s
{
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

struct hset_itr_s
{
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
 * @brief create a new hash set
 *
 * @return hset_t*
 */
hset_t *hset_new(void);

/**
 * @brief return a new hash set.
 * Does not copy the elements.
 *
 * @param hset original hash set
 * @return hset_t* - copy of the original hash set
 */
hset_t *hset_copy(hset_t *hset);

/**
 * @brief free a hash set underlying structure.
 * It is the caller's responsibility to free the items
 *
 * @param hset
 */
void hset_free(hset_t *hset);

/**
 * @brief add a new element to the hash set, does nothing if already present
 *
 * @param hset hash set
 * @param item new element
 * @return int - `-1` if error (bad item value),
 * `0` if already present (no change),
 * `1` if added (new element),
 * `2` if rehash did not work (set integrity compromised)
 */
int hset_push(hset_t *hset, void *item);

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
 * @return int - `-1` if error (bad item value),
 * `0` if not found (no change),
 * `1` if removed (value removed),
 */
int hset_discard(hset_t *hset, void *item);

/**
 * @brief return an arbitrary item from the hash set and remove it
 *
 * @param hset hash set
 * @return size_t - 0 if empty, otherwise the item
 */
size_t hset_pop(hset_t *hset);

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
hset_itr_t *hset_itr_new(hset_t *set);

/**
 * @brief returns the value at the current index, it is the caller's
 * responsibility to cast the value
 *
 * @param itr iterator
 * @return size_t - value at current index
 */
size_t hset_itr_value(hset_itr_t *itr);

/**
 * @brief return 1 is can advance, 0 otherwise
 *
 * @param itr iterator
 * @return int
 */
int hset_itr_has_next(hset_itr_t *itr);

/**
 * @brief check if iterator can advance, if so advances.
 * Returns current index if can advance and -1 otherwise
 *
 * @param itr iterator
 * @return size_t
 */
size_t hset_itr_next(hset_itr_t *itr);

/**
 * @brief free the iterator's underlying structure.
 * Does not free the hash set
 *
 * @param itr iterator
 */
void hset_itr_free(hset_itr_t *itr);

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
