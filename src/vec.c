/* vec.c - A simple pointer vector library */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vec.h"

/* This vector is just a simple container for pointers. It
 * doesn't know whether your pointers are from malloc or
 * const static strings. It is useful for storing lists of
 * pointers and iterating over them quickly. Building
 * abstractions on top of it is very useful */

size_t vec_push(vec_t *v, void *ptr)
{
    ASSERT_IF_LOCKED(v);

    if (v->size == 0)
    {
        v->size = VEC_MIN_SIZE;
        v->data = (void *)malloc(sizeof(void *) * v->size);
        memset(v->data, 0x0, v->size);
    }

    /* Sometimes the vector has a free slot, lets use it */
    if (v->free_slot != 0)
    {
        v->data[v->free_slot] = ptr;
        int32_t free_slot = v->free_slot;
        v->free_slot = 0;
        return free_slot;
    }

    if (v->end_slot == v->size)
    {
        v->size *= 2;
        v->data = (void *)realloc(v->data, sizeof(void *) * v->size);
    }

    v->data[v->end_slot] = ptr;
    v->elts++;
    return v->end_slot++;
}

void *vec_pop(vec_t *v)
{
    ASSERT_IF_LOCKED(v);

    if (v->end_slot == 0)
        return NULL;

    void *last = v->data[v->end_slot - 1];
    size_t last_index = v->end_slot - 1;

    v->data[last_index] = 0x0;
    v->end_slot--;
    v->elts--;

    return last;
}

void *vec_get_end(vec_t *v) { return v->data[v->end_slot]; }

void *vec_get_at(vec_t *v, size_t index)
{
    if (index >= v->end_slot)
    {
        return NULL;
    }

    return v->data[index];
}

void *vec_for_each(vec_t *v, for_each_callback_t *fe, void *data)
{
    ASSERT_IF_LOCKED(v);

    void *ret = NULL;
    if (fe == NULL)
        return NULL;

    LOCK_VEC(v);

    for (size_t sz = 0; sz < vec_used(v); sz++)
    {
        void *p = vec_get_at(v, sz);

        if (p == NULL)
            continue;

        ret = (fe)(p, data);
        if (ret != NULL)
        {
            UNLOCK_VEC(v);
            return ret;
        }
    }

    UNLOCK_VEC(v);
    return NULL;
}

void *vec_set_at(vec_t *v, int index, void *ptr)
{
    ASSERT_IF_LOCKED(v);

    if ((size_t)index >= v->end_slot)
        return NULL;

    v->data[index] = ptr;
    v->end_slot++;
    return v->data[index];
}

size_t vec_used(vec_t *v) { return v->end_slot; }

size_t vec_size(vec_t *v) { return v->elts; }

void vec_delete_at(vec_t *v, size_t index, delete_callback_t *dc)
{
    ASSERT_IF_LOCKED(v);

    if (index >= v->end_slot)
        return;
    void *ptr = v->data[index];
    v->data[index] = 0x0;
    v->end_slot--;
    v->elts--;

    if (dc != NULL && ptr != NULL)
        (dc)(ptr);
}

void vec_delete_all(vec_t *v, delete_callback_t *dc)
{
    ASSERT_IF_LOCKED(v);

    void *p = NULL;
    while ((p = vec_pop(v)) != NULL)
    {
        v->elts--;
        if (dc != NULL)
            (dc)(p);
    }
}

void vec_free(vec_t *v)
{
    ASSERT_IF_LOCKED(v);
    // memset(v->data, 0x0, v->size);
    free(v->data);
    free(v);
}

void vec_init(vec_t *v)
{
    UNLOCK_VEC(v);
    v->data = NULL;
    v->size = 0;
    v->end_slot = 0;
    v->free_slot = 0;
    v->elts = 0;
}

vec_t *vec_new(void)
{
    vec_t *v = malloc(sizeof(vec_t));
    vec_init(v);
    return v;
}

void vec_reverse(vec_t *v)
{
    ASSERT_IF_LOCKED(v);

    void *tmp = NULL;
    for (size_t i = 0; i < v->end_slot / 2; i++)
    {
        tmp = v->data[i];
        v->data[i] = v->data[v->end_slot - i - 1];
        v->data[v->end_slot - i - 1] = tmp;
    }
}

void vec_print(vec_t *v, print_callback_t *pc)
{
    if (pc == NULL)
        return;

    for (size_t i = 0; i < v->end_slot; i++)
    {
        void *p = v->data[i];
        if (p == NULL)
            continue;

        (pc)(p);
    }
}

void **vec_to_array(vec_t *v)
{
    void **arr = malloc(sizeof(void *) * v->end_slot);
    memcpy(arr, v->data, sizeof(void *) * v->end_slot);
    return arr;
}

vec_t *vec_from_array(void **array, size_t size)
{
    vec_t *v = vec_new();
    for (size_t i = 0; i < size; i++)
    {
        vec_push(v, array[i]);
    }
    return v;
}

void vec_qsort(vec_t *v, compare_fn_t *cmp)
{
    ASSERT_IF_LOCKED(v);
    qsort(v->data, v->end_slot, sizeof(void *), cmp);
}

vec_t *vec_copy(vec_t *v)
{
    vec_t *v2 = vec_new();
    void *p = NULL;
    for (size_t i = 0; i < v->end_slot; i++)
    {
        p = vec_get_at(v, i);
        if (p == NULL)
            continue;

        vec_push(v2, p);
    }
    return v2;
}
