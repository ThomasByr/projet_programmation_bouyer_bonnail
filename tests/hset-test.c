#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hset.h"
#include "macros.h"

typedef struct foo_t {
    int a;
    int b;
    char *id;
} foo_t;

foo_t *foo_new(int id) {
    foo_t *foo = malloc(sizeof(foo_t));
    foo->a = 0;
    foo->b = 0;
    foo->id = malloc(sizeof(char) * 1000000);
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

void hset_test_0(void) {
    hset_t *hset = hset_create();

    foo_t *foo0 = foo_new(0);
    foo_t *foo1 = foo_new(0);
    foo_t *foo2 = foo_new(0);

    hset_insert(hset, foo0);
    hset_insert(hset, foo1);
    hset_insert(hset, foo2);
    hset_insert(hset, foo0);

    foo0->a = 1;
    sprintf(foo0->id, "%d", 42);
    hset_insert(hset, foo0);

    assert_eq(hset_nitems(hset), 3);

    hset_destroy(hset);
    foo_free(foo0);
    foo_free(foo1);
    foo_free(foo2);
}

void hset_test_1(void) {
    hset_t *hset = hset_create();
    hset_itr_t *itr = hset_itr_create(hset);
    size_t n_foo = 1000;

    for (size_t i = 0; i < n_foo; i++) {
        foo_t *foo = foo_new(i);
        foo->a = 42;
        hset_insert(hset, foo);
    }

    assert_eq(hset_nitems(hset), n_foo);
    size_t count = 0;
    while (hset_itr_has_next(itr)) {
        count++;
        foo_t *foo = (foo_t *)hset_itr_val(itr);
        // assert_eq(foo->a, 42);
        foo->a = 1;
        hset_insert(hset, foo);
        hset_itr_next(itr);
    }
    assert_eq(count, n_foo);
    assert_eq(hset_nitems(hset), n_foo);
    hset_itr_reset(itr);

    while (hset_itr_has_next(itr)) {
        foo_t *foo = (foo_t *)hset_itr_val(itr);
        foo_free(foo);
        hset_itr_next(itr);
    }
    hset_itr_destroy(itr);
    hset_destroy(hset);
}

void hset_test_2(void) {
    hset_t *hset = hset_create();
    hset_itr_t *itr = hset_itr_create(hset);
    size_t n_foo = 2;

    for (size_t i = 0; i < n_foo; i++) {
        foo_t *foo = foo_new(i);
        foo->a = 42;
        hset_insert(hset, foo);
    }

    assert_eq(hset_nitems(hset), n_foo);
    int a = 42;
    void *data = &a;
    hset_itr_for_each(itr, foo_cmp_a_void, data);

    hset_itr_discard_all(itr, foo_free_void);
    hset_itr_destroy(itr);
    hset_destroy(hset);
}

void hset_test(void) {
    test_case(hset_test_0);
    test_case(hset_test_1);
    test_case(hset_test_2);
}
