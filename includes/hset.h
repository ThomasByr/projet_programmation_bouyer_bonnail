/*

*/

#ifndef HSET_H
#define HSET_H

typedef struct hset_t
{
    void ***buckets; // array of arrays of pointers
    int *sizes;      // array of sizes (max number of elements in each bucket)
    int *counts;     // array of counts (actual number of elements in each bucket)
    size_t capacity; // number of buckets (the higher the capacity, the more memory is used but the faster the search)

    // function pointer to extract string representation of element
    char *(*to_string)(void *);
} hset_t;

/**
 * @brief djb2 hash function by Dan Bernstein
 * 
 * @param str string to hash
 * @return unsigned long 
 */
unsigned long hash(char *str);

/**
 * @brief ceate a new hash set with a fixed capacity
 * 
 * @param capacity number of buckets
 * @param to_string function pointer to extract string representation of element
 * @return hset_t* 
 */
hset_t *hset_create(size_t capacity, char *(*to_string)(void *));

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
 * @param data new element
 */
void hset_insert(hset_t *hset, void *data);

/**
 * @brief return 1 if element is present in the hash set, 0 otherwise
 * 
 * @param hset hash set
 * @param data data to check
 * @return int 
 */
int hset_contains(hset_t *hset, void *data);

/**
 * @brief remove data from hash set, does nothing if not present
 * 
 * @param hset hash set
 * @param data data to remove
 */
void hset_discard(hset_t *hset, void *data);

#endif
