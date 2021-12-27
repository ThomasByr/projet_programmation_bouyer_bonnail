/*

*/

#ifndef FOO_H
#define FOO_H

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"

struct foo_s {
    char *id;
    int a;
    int b;
};
typedef struct foo_s foo_t;

foo_t *foo_new(int id) {
    foo_t *foo = (foo_t *)malloc(sizeof(foo_t));
    foo->id = (char *)malloc(sizeof(char) * 1000000);
    foo->a = 0;
    foo->b = 0;
    sprintf(foo->id, "%d", id);

    return foo;
}

void foo_free(foo_t *foo) {
    free(foo->id);
    free(foo);
}

void foo_free_void(void *foo) {
    foo_t *f = (foo_t *)foo;
    foo_free(f);
}

void *foo_cmp_a_void(void *foo, void *a) {
    foo_t *f = (foo_t *)foo;
    int *i = (int *)a;
    assert_eq(f->a, *i);
    return NULL;
}

#endif
