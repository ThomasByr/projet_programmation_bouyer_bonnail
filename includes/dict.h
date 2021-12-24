/*

*/

#ifndef DICT_H
#define DICT_H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

struct dict_s {
    size_t nbits;
    size_t mask;

    size_t capacity;
    size_t *keys;
    void **values;
    size_t nitems;
    size_t n_deleted_items;
};
/**
 * @brief dictionary data structure that maps uniques keys to some value
 *
 */
typedef struct dict_s dict_t;

/**
 * @brief new dictionary
 *
 * @return dict_t*
 */
dict_t *dict_new(void);

/**
 * @brief free dictionary underlying structure.
 * It is caller responsibility to free the values if needed
 *
 * @param dict dictionary to free
 */
void dict_free(dict_t *dict);

/**
 * @brief add new key-value pair to dictionary.
 * If key already exists, the value is replaced.
 *
 * @param dict dictionary
 * @param key key
 * @param value value
 * @return int - 1 if key was added, 0 if key already exists, -1 if error
 */
int dict_push(dict_t *dict, void *key, void *value);

/**
 * @brief get value for given key
 *
 * @param dict dictionary
 * @param key key
 * @return void* - value or NULL if key not found
 */
void *dict_get(dict_t *dict, void *key);

/**
 * @brief remove key-value pair from dictionary
 *
 * @param dict dictionary
 * @param key key
 * @return int - 1 if key was removed, 0 if key not found, -1 if error
 */
int dict_discard(dict_t *dict, void *key);

/**
 * @brief get number of items in dictionary
 *
 * @param dict dictionary
 * @return size_t
 */
size_t dict_nitems(dict_t *dict);

#endif
