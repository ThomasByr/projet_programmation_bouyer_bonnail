#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"
#include "macros.h"

void dict_test_0(void) {
    dict_t *dict = dict_create();
    dict_insert(dict, (void *)"foo1", (void *)"bar");
    dict_insert(dict, (void *)"foo2", (void *)"baz");
    char *value = (char *)dict_get(dict, (void *)"foo1");
    assert_eq(strcmp(value, "bar"), 0);
    value = (char *)dict_get(dict, (void *)"foo2");
    assert_eq(strcmp(value, "baz"), 0);
    dict_destroy(dict);
}

void dict_test_1(void) {
    dict_t *dict = dict_create();
    int n = 1000;
    for (int i = 0; i < n; i++) {
        char key[100];
        sprintf(key, "foo%d", i);
        dict_insert(dict, (void *)key, (void *)"bar");
    }
    for (int i = 0; i < n; i++) {
        char key[100];
        sprintf(key, "foo%d", i);
        char *value = (char *)dict_get(dict, (void *)key);
        assert_eq(strcmp(value, "bar"), 0);
    }
    dict_destroy(dict);
}

void dict_test_2(void) {
    dict_t *dict = dict_create();
    dict_insert(dict, (void *)"foo1", (void *)"bar");
    dict_insert(dict, (void *)"foo2", (void *)"baz");

    dict_discard(dict, (void *)"foo1");
    assert_eq(dict_get(dict, (void *)"foo1"), NULL);
    assert_eq(dict_get(dict, (void *)"foo2"), "baz");

    dict_insert(dict, (void *)"foo1", (void *)"bar");
    dict_discard(dict, (void *)"foo2");
    assert_eq(dict_get(dict, (void *)"foo1"), "bar");
    assert_eq(dict_get(dict, (void *)"foo2"), NULL);

    dict_destroy(dict);
}

void dict_test(void) {
    test_case(dict_test_0);
    test_case(dict_test_1);
    test_case(dict_test_2);
}
