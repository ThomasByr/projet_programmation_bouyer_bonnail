#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "vec.h"

void vec_test_0(void) {
    vec_t *v = vec_new();
    vec_push(v, (void *)"bob1");
    vec_push(v, (void *)"bob2");

    assert_eq(vec_size(v), 2);
    assert_eq(vec_get_at(v, 0), (void *)"bob1");
    assert_eq(vec_get_at(v, 1), (void *)"bob2");
    vec_free(v);
}

void vec_test_1(void) {
    vec_t *v = vec_new();
    char str[100];
    int n = 1000;
    for (int i = 0; i < n; i++) {
        sprintf(str, "bob%d", i);
        vec_push(v, (void *)str);
    }

    for (int i = 0; i < n; i++) {
        sprintf(str, "bob%d", i);
        assert_eq(vec_get_at(v, (size_t)i), (void *)str);
    }
    vec_free(v);
}

void vec_test(void) {
    test_case(vec_test_0);
    test_case(vec_test_1);
}
