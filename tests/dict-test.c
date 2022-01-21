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
    char *str0 = "foo0";
    char *str1 = "foo1";

    dict_push(dict, (void *)str0, (void *)str0);
    dict_push(dict, (void *)str1, (void *)str1);
    assert_eq(dict_nitems(dict), 2);

    char *value = (char *)dict_get(dict, (void *)str0);
    assert_eq(strcmp(value, str0), 0);

    value = (char *)dict_get(dict, (void *)str1);
    assert_eq(strcmp(value, str1), 0);

    dict_discard(dict, (void *)str0);
    assert_eq(dict_nitems(dict), 1);

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
    dict_itr_discard_all(itr, foo_free_void, foo_free_void);
    dict_itr_free(itr);
    dict_free(dict);
}

void dict_test_4(void) {
    dict_t *dict1 = dict_new();
    dict_t *dict2 = dict_new();
    dict_itr_t *itr = dict_itr_new(dict1);
    int n = 1000;
    for (int i = 0; i < n; i++) {
        foo_t *foo1 = foo_new(i);
        foo_t *foo2 = foo_new(i);
        foo1->a = 42;
        foo2->a = 24;
        int x = dict_push(dict1, foo1, foo2);
        assert_eq(x, 1);
        x = dict_push(dict2, foo1, foo2);
        assert_eq(x, 1);
    }
    assert_eq(dict_nitems(dict1), n);
    assert_eq(dict_nitems(dict2), n);

    size_t rv = dict_merge(dict1, dict2);
    assert_eq(rv, 0);
    assert_eq(dict_nitems(dict1), n);
    assert_eq(dict_nitems(dict2), n);

    dict_itr_discard_all(itr, foo_free_void, foo_free_void);
    dict_itr_free(itr);
    dict_free(dict1);
    dict_free(dict2);
}

void dict_test_5(void) {
    dict_t *dict1 = dict_new();
    dict_t *dict2 = dict_new();
    dict_itr_t *itr = dict_itr_new(dict1);
    int n = 1000;
    for (int i = 0; i < n; i++) {
        foo_t *foo1 = foo_new(i);
        foo_t *foo2 = foo_new(i);
        foo1->a = 42;
        foo2->a = 24;
        int x = dict_push(dict1, foo1, foo1);
        assert_eq(x, 1);
        x = dict_push(dict2, foo2, foo2);
        assert_eq(x, 1);
    }
    assert_eq(dict_nitems(dict1), n);
    assert_eq(dict_nitems(dict2), n);

    size_t rv = dict_merge(dict1, dict2);
    assert_eq(rv, n);
    assert_eq(dict_nitems(dict1), 2 * n);
    assert_eq(dict_nitems(dict2), n);

    dict_itr_discard_all(itr, foo_free_void, NULL);
    dict_itr_free(itr);
    dict_free(dict1);
    dict_free(dict2);
}

void dict_test_6(void) {
    dict_t *dict1 = dict_new();
    dict_itr_t *itr = dict_itr_new(dict1);
    int n = 1000;
    for (int i = 0; i < n; i++) {
        foo_t *foo = foo_new(i);
        foo->a = 42;
        int x = dict_push(dict1, foo, foo);
        assert_eq(x, 1);
    }
    assert_eq(dict_nitems(dict1), n);

    dict_t *dict2 = dict_copy(dict1);
    assert_eq(dict_nitems(dict2), n);

    for (int i = n; i < 2 * n; i++) {
        foo_t *foo = foo_new(i);
        foo->a = 42;
        int x = dict_push(dict1, foo, foo);
        assert_eq(x, 1);
    }
    assert_eq(dict_nitems(dict1), 2 * n);
    assert_eq(dict_nitems(dict2), n);

    dict_itr_discard_all(itr, foo_free_void, NULL);
    dict_itr_free(itr);
    dict_free(dict1);
    dict_free(dict2);
}

void dict_test_7(void) {
    dict_t *dict1 = dict_new();
    dict_t *dict2 = dict_new();
    dict_itr_t *itr = dict_itr_new(dict1);
    int n = 1000;
    for (int i = 0; i < n; i++) {
        foo_t *foo1 = foo_new(i);
        foo_t *foo2 = foo_new(i);
        foo1->a = 42;
        foo2->a = 24;
        int x = dict_push(dict1, foo1, foo1);
        assert_eq(x, 1);
        x = dict_push(dict2, foo1, foo1);
        assert_eq(x, 1);
        x = dict_push(dict2, foo2, foo2);
        assert_eq(x, 1);
    }
    assert_eq(dict_nitems(dict1), n);
    assert_eq(dict_nitems(dict2), 2 * n);

    size_t rv = dict_merge(dict1, dict2);
    assert_eq(rv, n);
    assert_eq(dict_nitems(dict1), 2 * n);
    assert_eq(dict_nitems(dict2), 2 * n);

    dict_itr_discard_all(itr, foo_free_void, NULL);
    dict_itr_free(itr);
    dict_free(dict1);
    dict_free(dict2);
}

void dict_test_8(void) {
    dict_t *dict0 = dict_new();
    dict_t *dict1 = dict_new(1);
    dict_itr_t *itr = dict_itr_new(dict0);
    int n = 1000;

    char *str = "foo";
    char *str1 = strdup(str);
    dict_push(dict0, str1, str1);
    dict_push(dict1, str1, str1);

    for (int i = 0; i < n; i++) {
        str1 = strdup(str);

        size_t s0 = dict_get(dict0, str1);
        size_t s1 = dict_get(dict1, str1);
        assert_eq(s0, 0);
        assert_gt(s1, 0);
        int rv0 = dict_push(dict0, str1, str1);
        int rv1 = dict_push(dict1, str1, str1);
        assert_eq(rv0, 1);
        assert_eq(rv1, 0);
        s0 = dict_get(dict0, str1);
        s1 = dict_get(dict1, str1);
        assert_gt(s0, 0);
        assert_gt(s1, 0);
    }

    assert_eq(dict_nitems(dict0), n + 1);
    assert_eq(dict_nitems(dict1), 1);

    dict_itr_discard_all(itr, free, NULL);
    dict_itr_free(itr);
    dict_free(dict0);
    dict_free(dict1);
}

void dict_test(void) {
    test_case(dict_test_0);
    test_case(dict_test_1);
    test_case(dict_test_2);
    test_case(dict_test_3);
    test_case(dict_test_4);
    test_case(dict_test_5);
    test_case(dict_test_6);
    test_case(dict_test_7);
    test_case(dict_test_8);
}
