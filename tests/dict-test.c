#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"
#include "macros.h"

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
    int n = 1000;
    for (int i = 0; i < n; i++) {
        char key[100];
        sprintf(key, "foo%d", i);
        dict_push(dict, (void *)key, (void *)"bar");
    }
    // printf("\nnumber of items: %lu\n", dict_nitems(dict));
    // assert_eq(dict_nitems(dict), n);

    for (int i = 0; i < n; i++) {
        char key[100];
        sprintf(key, "foo%d", i);
        char *value = (char *)dict_get(dict, (void *)key);
        assert_eq(strcmp(value, "bar"), 0);
    }
    dict_free(dict);
}

void dict_test_2(void) {
    dict_t *dict = dict_new();
    dict_push(dict, (void *)"foo1", (void *)"bar");
    dict_push(dict, (void *)"foo2", (void *)"baz");
    assert_eq(dict_nitems(dict), 2);

    dict_discard(dict, (void *)"foo1");
    assert_eq(dict_nitems(dict), 1);
    assert_eq(dict_get(dict, (void *)"foo1"), NULL);
    assert_eq(dict_get(dict, (void *)"foo2"), "baz");

    dict_push(dict, (void *)"foo1", (void *)"bar");
    assert_eq(dict_nitems(dict), 2);
    dict_discard(dict, (void *)"foo2");
    assert_eq(dict_nitems(dict), 1);
    assert_eq(dict_get(dict, (void *)"foo1"), "bar");
    assert_eq(dict_get(dict, (void *)"foo2"), NULL);

    dict_free(dict);
}

void dict_test_3(void) {
    dict_t *dict = dict_new();
    int n = 1000;
    for (int i = 0; i < n; i++) {
        char key[100];
        char value[100];
        sprintf(key, "foo%d", i);
        sprintf(value, "bar%d", i);
        dict_push(dict, (void *)key, (void *)value);
    }

    for (int i = 0; i < n; i++) {
        char key[100];
        char value[100];
        sprintf(key, "foo%d", i);
        sprintf(value, "bar%d", i);
        char *value_ = (char *)dict_get(dict, (void *)key);
        assert_eq(strcmp(value_, value), 0);
    }
    dict_free(dict);
}

void dict_test(void) {
    test_case(dict_test_0);
    test_case(dict_test_1);
    test_case(dict_test_2);
    test_case(dict_test_3);
}
