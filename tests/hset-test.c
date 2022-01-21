#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "foo.h"
#include "hset.h"
#include "macros.h"

void hset_test_0(void) {
    hset_t *hset = hset_new();

    foo_t *foo0 = foo_new(0);
    foo_t *foo1 = foo_new(0);
    foo_t *foo2 = foo_new(0);

    hset_push(hset, foo0);
    hset_push(hset, foo1);
    hset_push(hset, foo2);
    hset_push(hset, foo0);

    foo0->a = 1;
    sprintf(foo0->id, "%d", 42);
    hset_push(hset, foo0);

    assert_eq(hset_nitems(hset), 3);

    hset_free(hset);
    foo_free(foo0);
    foo_free(foo1);
    foo_free(foo2);
}

void hset_test_1(void) {
    hset_t *hset = hset_new();
    hset_itr_t *itr = hset_itr_new(hset);
    size_t n_foo = 1000;

    for (size_t i = 0; i < n_foo; i++) {
        foo_t *foo = foo_new(i);
        foo->a = 42;
        int x = hset_push(hset, foo);
        assert_eq(x, 1);
    }

    assert_eq(hset_nitems(hset), n_foo);
    size_t count = 0;
    while (hset_itr_has_next(itr)) {
        count++;
        foo_t *foo = (foo_t *)hset_itr_value(itr);
        assert_eq(foo->a, 42);
        foo->a = 1;
        hset_push(hset, foo);
        hset_itr_next(itr);
    }
    assert_eq(count, n_foo);
    assert_eq(hset_nitems(hset), n_foo);
    hset_itr_reset(itr);

    while (hset_itr_has_next(itr)) {
        foo_t *foo = (foo_t *)hset_itr_value(itr);
        foo_free(foo);
        hset_itr_next(itr);
    }
    hset_itr_free(itr);
    hset_free(hset);
}

void hset_test_2(void) {
    hset_t *hset = hset_new();
    hset_itr_t *itr = hset_itr_new(hset);
    size_t n_foo = 1000;

    for (size_t i = 0; i < n_foo; i++) {
        foo_t *foo = foo_new(i);
        foo->a = 1;
        hset_push(hset, foo);
        foo->a = 42;
    }

    assert_eq(hset_nitems(hset), n_foo);
    int a = 42;
    void *data = &a;
    hset_itr_for_each(itr, foo_cmp_a_void, data);

    hset_itr_discard_all(itr, foo_free_void);
    hset_itr_free(itr);
    hset_free(hset);
}

void hset_test_3(void) {
    hset_t *hset = hset_new();
    hset_push(hset, (void *)"foo");
    hset_push(hset, (void *)"bar");
    hset_push(hset, (void *)"foo");
    assert_eq(hset_nitems(hset), 2);

    hset_free(hset);
}

void hset_test_4(void) {
    hset_t *hset = hset_new();
    hset_itr_t *itr = hset_itr_new(hset);
    size_t n = 1000;

    for (size_t i = 0; i < n; i++) {
        foo_t *foo = foo_new((int)i);
        foo->a = 42;
        hset_push(hset, foo);
    }
    hset_t *cpy = hset_copy(hset);
    hset_itr_discard_all(itr, NULL);
    hset_itr_free(itr);

    assert_eq(hset_nitems(hset), 0);
    assert_eq(hset_nitems(cpy), n);

    itr = hset_itr_new(cpy);
    int a = 42;
    void *data = &a;
    hset_itr_for_each(itr, foo_cmp_a_void, data);
    hset_itr_discard_all(itr, foo_free_void);

    hset_itr_free(itr);
    hset_free(cpy);
    hset_free(hset);
}

void hset_test_5(void) {
    hset_t *hset = hset_new();
    size_t n = 1000;

    for (size_t i = 0; i < n; i++) {
        foo_t *foo = foo_new((int)i);
        foo->a = 42;
        foo->b = 24;
        hset_push(hset, foo);
    }

    for (size_t i = 0; i < n; i++) {
        size_t item = hset_pop(hset);
        assert_gt(item, 0);
        foo_t *foo = (foo_t *)(item);
        assert_eq(foo->a, 42);
        assert_eq(foo->b, 24);
        assert_geq(atoi(foo->id), 0);
        assert_eq(hset_nitems(hset), n - i - 1);
        foo_free(foo);
    }
    hset_free(hset);
}

void hset_test_6(void) {
    hset_t *hset = hset_new();
    size_t n = 1000;

    for (size_t i = 0; i < n; i++) {
        char id[100];
        sprintf(id, "%s", "test string");
        int rv = hset_push(hset, strdup(id));
        assert_eq(rv, 1);
    }
    for (size_t i = 0; i < n; i++) {
        char *id = (char *)hset_pop(hset);
        assert_eq(strcmp(id, "test string"), 0);
        free(id);
    }
    hset_free(hset);
}

void hset_test_7(void) {
    hset_t *hset0 = hset_new();
    hset_t *hset1 = hset_new(1);

    char *str = "foo";
    char *str1 = strdup(str);
    char *str2 = strdup(str);

    hset_push(hset0, str1);
    hset_push(hset0, str2);
    hset_push(hset1, str1);
    hset_push(hset1, str2);

    assert_eq(hset_nitems(hset0), 2);
    assert_eq(hset_nitems(hset1), 1);

    free(str1);
    free(str2);
    hset_free(hset0);
    hset_free(hset1);
}

void hset_test_8(void) {
    hset_t *hset0 = hset_new();
    hset_t *hset1 = hset_new(1);
    int n = 1000;

    char *str = "foo";
    char *str1 = strdup(str);
    hset_push(hset0, str1);
    hset_push(hset1, str1);

    for (int i = 0; i < n; i++) {
        str1 = strdup(str);
        assert_eq(hset_contains(hset0, str1), 0);
        assert_eq(hset_contains(hset1, str1), 1);
        int rv0 = hset_push(hset0, str1);
        int rv1 = hset_push(hset1, str1);
        assert_eq(rv0, 1);
        assert_eq(rv1, 0);
        assert_eq(hset_contains(hset0, str1), 1);
        assert_eq(hset_contains(hset1, str1), 1);
    }
    assert_eq(hset_nitems(hset0), n + 1);
    assert_eq(hset_nitems(hset1), 1);

    for (int i = 0; i < n + 1; i++) {
        char *str1 = (char *)hset_pop(hset0);
        assert_eq(strcmp(str1, str), 0);
        free(str1);
    }
    hset_free(hset0);
    hset_free(hset1);
}

void hset_test(void) {
    test_case(hset_test_0);
    test_case(hset_test_1);
    test_case(hset_test_2);
    test_case(hset_test_3);
    test_case(hset_test_4);
    test_case(hset_test_5);
    test_case(hset_test_6);
    test_case(hset_test_7);
    test_case(hset_test_8);
}
