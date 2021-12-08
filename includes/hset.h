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

struct hset_itr_s
{
    hset_t *set;
    size_t index;
};

typedef struct hset_s hset_t;
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
hset_itr_t *hset_itr(hset_t *set);

/**
 * @brief returns the value at the current index, it is the caller's responsibility to cast the value
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
 * @return int 
 */
size_t hset_itr_next(hset_itr_t *itr);

#endif
