/*

*/

#ifndef HSET_H
#define HSET_H

struct hset_s
{
    size_t nbits;
    size_t mask;

    size_t capacity;
    size_t *items;
    size_t nitems;
    size_t n_deleted_items;
};

typedef struct hset_s hset_t;

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

#endif
