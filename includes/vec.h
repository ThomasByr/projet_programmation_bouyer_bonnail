/* vec.h - A simple pointer vector */

#ifndef VEC_H
#define VEC_H

#include "types.h"

#define VEC_MIN_SIZE 1 << 11

struct vec_s {
    void **data;      // this vector only holds pointers
    size_t end_slot;  // index to the end of the vector
    size_t size;      // size of the vector
    size_t free_slot; // index of the last known hole in the vector
    size_t elts;      // number of elements in the vector
};
typedef struct vec_s vec_t;

/**
 * @brief delete and return the last element
 *
 * @param v vector
 * @return void*
 */
void *vec_pop(vec_t *v);

/**
 * @brief return the last element
 *
 * @param v vector
 * @return void*
 */
void *vec_get_end(vec_t *v);

/**
 * @brief get element at index
 *
 * @param v vector
 * @param index index
 * @return void*
 */
void *vec_get_at(vec_t *v, size_t index);

/**
 * @brief invoke callback on each element, stops if the callback returns
 * non-NULL
 *
 * @param v vector
 * @param fe for each callback
 * @param data callback data
 * @return void*
 */
void *vec_for_each(vec_t *v, for_each_callback_t *fe, void *data);

/**
 * @brief set element at index
 *
 * @param v vector
 * @param index index
 * @param ptr pointer to element
 * @return void*
 */
void *vec_set_at(vec_t *v, int index, void *ptr);

/**
 * @brief delete all elements, invoke delete_callback on each element
 *
 * @param v vector
 * @param dc delete callback
 */
void vec_delete_all(vec_t *v, delete_callback_t *dc);

/**
 * @brief delete element at index
 *
 * @param v vector
 * @param index index
 */
void vec_delete_at(vec_t *v, size_t index);

/**
 * @brief free vector underlying structure
 *
 * @param v vector
 */
void vec_free(vec_t *v);

/**
 * @brief initialize vector
 *
 * @param v vector
 */
void vec_init(vec_t *v);

/**
 * @brief create a new vector
 *
 */
vec_t *vec_new(void);

/**
 * @brief return the number of entries in the vector
 *
 * @param v vector
 * @return size_t
 */
size_t vec_used(vec_t *v);

/**
 * @brief return the number of allocated entries in the vector
 *
 * @param v vector
 * @return size_t
 */
size_t vec_size(vec_t *v);

/**
 * @brief push element to the end of the vector and return last slot index
 *
 * @param v vector
 * @param ptr pointer to element
 * @return size_t
 */
size_t vec_push(vec_t *v, void *ptr);

/**
 * @brief reverse the order of the vector
 *
 * @param v vector
 */
void vec_reverse(vec_t *v);

#endif
