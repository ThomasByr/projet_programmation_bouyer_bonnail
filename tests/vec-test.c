#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "protocol.h"
#include "vec.h"

void vec_test_0(void) {
    vec_t *v = vec_new();
    vec_push(v, (void *)"bob1");
    vec_push(v, (void *)"bob2");

    assert_eq(vec_size(v), 2);
    assert_eq(vec_get_at(v, 0), (void *)"bob1");
    assert_eq(vec_get_at(v, 1), (void *)"bob2");

    char *e = (char *)vec_pop(v);
    assert_eq(e, (void *)"bob2");
    assert_eq(vec_size(v), 1);
    assert_eq(vec_get_at(v, 0), (void *)"bob1");
    assert_eq(vec_get_at(v, 1), NULL);
    vec_free(v);
}

void vec_test_1(void) {
    vec_t *v = vec_new();
    int n = 1000;
    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);
        vec_push(v, (void *)strdup(str));
    }

    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);
        char *e = (char *)vec_get_at(v, (size_t)i);
        assert_eq(strcmp(e, str), 0);
    }
    vec_delete_all(v, free);
    vec_free(v);
}

void vec_test_2(void) {
    vec_t *v = vec_new();
    int n = 1000;

    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);
        vec_push(v, (void *)strdup(str));
    }
    vec_t *v2 = vec_copy(v);
    assert_eq(vec_size(v), vec_size(v2));
    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);
        char *e = (char *)vec_get_at(v, (size_t)i);
        char *e2 = (char *)vec_get_at(v2, (size_t)i);
        assert_eq(strcmp(e, e2), 0);
        assert_eq(strcmp(e, str), 0);
    }
    vec_delete_all(v, free);
    vec_free(v);
    vec_free(v2);
}

void vec_test_3(void) {
    vec_t *v = vec_new();
    int n = 1000;

    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);
        vec_push(v, (void *)strdup(str));
    }
    vec_reverse(v);
    assert_eq(vec_size(v), n);
    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", n - i - 1);
        char *e = (char *)vec_get_at(v, (size_t)i);
        assert_eq(strcmp(e, str), 0);
    }
    vec_delete_all(v, free);
    vec_free(v);
}

void vec_test_4(void) {
    vec_t *v = vec_new();
    int n = 1000;

    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);
        vec_push(v, (void *)strdup(str));
    }

    void **arr = vec_to_array(v);
    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);
        char *e = (char *)arr[i];
        assert_eq(strcmp(e, str), 0);
    }

    vec_t *v2 = vec_from_array(arr, n);
    assert_eq(vec_size(v), vec_size(v2));
    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);
        char *e = (char *)vec_get_at(v, (size_t)i);
        char *e2 = (char *)vec_get_at(v2, (size_t)i);
        assert_eq(strcmp(e, e2), 0);
        assert_eq(strcmp(e, str), 0);
    }
    vec_delete_all(v, free);
    vec_free(v);
    vec_free(v2);
    free(arr);
}

void vec_test_5(void) {
    vec_t *v = vec_new();
    int n = 10;

    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);
        vec_push(v, (void *)strdup(str));
    }

    vec_t *v2 = vec_copy(v);
    assert_eq(vec_size(v), vec_size(v2));
    vec_reverse(v2);
    vec_qsort(v2, compare_strings);
    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);
        char *e = (char *)vec_get_at(v2, (size_t)i);
        assert_eq(strcmp(e, str), 0);
    }

    vec_delete_all(v, free);
    vec_free(v);
    vec_free(v2);
}

void vec_test(void) {
    test_case(vec_test_0);
    test_case(vec_test_1);
    test_case(vec_test_2);
    test_case(vec_test_3);
    test_case(vec_test_4);
    test_case(vec_test_5);
}
