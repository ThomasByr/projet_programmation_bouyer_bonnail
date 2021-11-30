/* vec.h - A simple pointer vector */

#ifndef VEC_H
#define VEC_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#if DEBUG || WRITE_LOCK
#include <assert.h>
#endif

#define VEC_MIN_SIZE 1024

typedef struct vec
{
    void **data;      // this vector only holds pointers
    size_t end_slot;  // index to the end of the vector
    size_t size;      // size of the vector
    size_t free_slot; // index of the last known hole in the vector
    size_t elts;      // number of elements in the vector
#if DEBUG || WRITE_LOCK
    /* Write lock. Not thread safe!
     * Only used with -DWRITE_LOCK or -DDEBUG */
    int32_t lock;
#endif
} vec;

#if DEBUG || WRITE_LOCK
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

typedef void *(for_each_callback_t)(void *, void *);
typedef void(delete_callback_t)(void *);

/**
 * @brief delete and return the last element
 * 
 * @param v vector
 * @return void* 
 */
void *vec_pop(vec *v);

/**
 * @brief return the last element
 * 
 * @param v vector
 * @return void* 
 */
void *vec_get_end(vec *v);

/**
 * @brief get element at index
 * 
 * @param v vector
 * @param index index
 * @return void* 
 */
void *vec_get_at(vec *v, size_t index);

/**
 * @brief invoke callback on each element, stops if the callback returns non-NULL
 * 
 * @param v vector
 * @param fe for each callback
 * @param data callback data
 * @return void* 
 */
void *vec_for_each(vec *v, for_each_callback_t *fe, void *data);

/**
 * @brief set element at index
 * 
 * @param v vector
 * @param index index
 * @param ptr pointer to element
 * @return void* 
 */
void *vec_set_at(vec *v, int index, void *ptr);

/**
 * @brief delete all elements, invoke delete_callback on each element
 * 
 * @param v vector
 * @param dc delete callback
 */
void vec_delete_all(vec *v, delete_callback_t *dc);

/**
 * @brief delete element at index
 * 
 * @param v vector
 * @param index index
 */
void vec_delete_at(vec *v, size_t index);

/**
 * @brief free vector underlying structure
 * 
 * @param v vector
 */
void vec_free(vec *v);

/**
 * @brief initialize vector
 * 
 * @param v vector
 */
void vec_init(vec *v);

/**
 * @brief create a new vector
 * 
 */
vec *vec_new(void);

/**
 * @brief return the number of entries in the vector
 * 
 * @param v vector
 * @return size_t 
 */
size_t vec_used(vec *v);

/**
 * @brief return the number of allocated entries in the vector
 * 
 * @param v vector
 * @return size_t 
 */
size_t vec_size(vec *v);

/**
 * @brief push element to the end of the vector and return last slot index
 * 
 * @param v vector
 * @param ptr pointer to element
 * @return int32_t 
 */
int32_t vec_push(vec *v, void *ptr);

#endif
