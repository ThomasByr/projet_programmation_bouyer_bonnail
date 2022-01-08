#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"
#include "foo.h"
#include "macros.h"
#include "protocol.h"

void dict_test_0(void) {
    dict_t *dict = dict_new();
    dict_push(dict, (void *)"foo1", (void *)"bar");
    dict_push(dict, (void *)"foo2", (void *)"baz");
    assert_eq(dict_nitems(dict), 2);
    char *value = (char *)dict_get(dict, (void *)"foo1");
    assert_eq(strcmp(value, "bar"), 0);
    value = (char *)dict_get(dict, (void *)"foo2");
    assert_eq(strcmp(value, "baz"), 0);
    dict_free(dict);
}

void dict_test_1(void) {
    dict_t *dict = dict_new();
    dict_itr_t *itr = dict_itr_new(dict);
    int n = 1000;
    for (int i = 0; i < n; i++) {
        foo_t *foo = foo_new(i);
        foo->a = 42;
        int x = dict_push(dict, foo, foo);
        assert_eq(x, 1);
    }
    assert_eq(dict_nitems(dict), n);

    size_t count = 0;
    while (dict_itr_has_next(itr)) {
        count++;
        foo_t *foo = (foo_t *)dict_itr_value(itr);
        assert_eq(foo->a, 42);
        foo->a = 1;
        dict_push(dict, foo, foo);
        dict_itr_next(itr);
    }
    assert_eq(count, n);
    assert_eq(dict_nitems(dict), n);
    dict_itr_reset(itr);

    while (dict_itr_has_next(itr)) {
        foo_t *foo = (foo_t *)dict_itr_value(itr);
        foo_free(foo);
        dict_itr_next(itr);
    }
    dict_itr_free(itr);
    dict_free(dict);
}

void dict_test_2(void) {
    dict_t *dict = dict_new();
    dict_push(dict, (void *)"foo1", (void *)"bar");
    dict_push(dict, (void *)"foo2", (void *)"baz");
    assert_eq(dict_nitems(dict), 2);

    dict_discard(dict, (void *)"foo1");
    assert_eq(dict_nitems(dict), 1);
    assert_eq(dict_get(dict, (void *)"foo1"), 0);
    assert_eq((char *)dict_get(dict, (void *)"foo2"), "baz");

    dict_push(dict, (void *)"foo1", (void *)"bar");
    assert_eq(dict_nitems(dict), 2);
    dict_discard(dict, (void *)"foo2");
    assert_eq(dict_nitems(dict), 1);
    assert_eq((char *)dict_get(dict, (void *)"foo1"), "bar");
    assert_eq(dict_get(dict, (void *)"foo2"), 0);

    dict_push(dict, (void *)"foo1", (void *)"bar");
    dict_push(dict, (void *)"foo2", (void *)"baz");
    dict_push(dict, (void *)"foo1", (void *)"baz");
    dict_push(dict, (void *)"foo2", (void *)"bar");

    assert_eq(dict_nitems(dict), 2);
    assert_eq((char *)dict_get(dict, (void *)"foo1"), "baz");
    assert_eq((char *)dict_get(dict, (void *)"foo2"), "bar");

    dict_free(dict);
}

void dict_test_3(void) {
    dict_t *dict = dict_new();
    dict_itr_t *itr = dict_itr_new(dict);
    int n = 1000;
    for (int i = 0; i < n; i++) {
        foo_t *foo1 = foo_new(i);
        foo_t *foo2 = foo_new(i);
        foo1->a = 42;
        foo2->a = 24;
        int x = dict_push(dict, foo1, foo2);
        assert_eq(x, 1);
    }
    assert_eq(dict_nitems(dict), n);

    int a = 42;
    void *data1 = &a;
    int b = 24;
    void *data2 = &b;
    dict_itr_for_each(itr, foo_cmp_a_void, data1, foo_cmp_a_void, data2);
    dict_itr_discatd_all(itr, foo_free_void, foo_free_void);
    dict_itr_free(itr);
    dict_free(dict);
}

void dict_test(void) {
    test_case(dict_test_0);
    test_case(dict_test_1);
    test_case(dict_test_2);
    test_case(dict_test_3);
}
