/* vec.h
A simple pointer vector

*/

#ifndef VEC_H
#define VEC_H

#ifdef DEBUG
#include <assert.h>
#endif

#include "types.h"

#define VEC_MIN_SIZE 1 << 11

struct vec_s
{
    void **data;      // this vector only holds pointers
    size_t end_slot;  // index to the end of the vector
    size_t size;      // size of the vector
    size_t free_slot; // index of the last known hole in the vector
    size_t elts;      // number of elements in the vector
#ifdef DEBUG
    int lock;
#endif
};
typedef struct vec_s vec_t;

#if DEBUG
#define LOCK_VEC(v) v->lock = 1;
#define UNLOCK_VEC(v) v->lock = 0;
#define IS_VEC_LOCKED(v) (v->lock == 1)
#define IS_VEC_UNLOCKED(v) (v->lock == 0)
#define ASSERT_IF_LOCKED(v) assert(!IS_VEC_LOCKED(v))
#else
#define LOCK_VEC(v)
#define UNLOCK_VEC(v)
#define IS_VEC_LOCKED(v)
#define IS_VEC_UNLOCKED(v)
#define ASSERT_IF_LOCKED(v)
#endif

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
 * @brief delete element at index and invoke delete_callback on it
 *
 * @param v vector
 * @param index index
 * @param dc delete callback
 */
void vec_delete_at(vec_t *v, size_t index, delete_callback_t *dc);

/**
 * @brief free vector underlying structure.
 * It is user's responsability to free the elements.
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

/**
 * @brief print each non-NULL element in the vector
 *
 * @param v vector
 * @param pc print callback
 */
void vec_print(vec_t *v, print_callback_t *pc);

/**
 * @brief sort the vector.
 * User should probably remove all NULL elements before calling this.
 *
 * @param v vector
 * @param cmp compare callback
 */
void vec_qsort(vec_t *v, compare_fn_t *cmp);

/**
 * @brief return the array representation of the vector
 *
 * @param v vector
 * @return void**
 */
void **vec_to_array(vec_t *v);

/**
 * @brief make a new vector from an array
 *
 * @param array array of void*
 * @param size size of array
 * @return vec_t* - new vector
 */
vec_t *vec_from_array(void **array, size_t size);

/**
 * @brief copy vector (shallow copy of non-NULL elements)
 *
 * @param v vector
 * @return vec_t* - new vector
 */
vec_t *vec_copy(vec_t *v);

/**
 * @brief print the size of the vector
 * @param v vector
 * @return void
 */

void vec_print_elts(vec_t *vec);

void vec_print(vec_t *vec, void print_elt(void *));

#endif
