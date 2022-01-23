#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "protocol.h"
#include "vec.h"

void vec_test_0(void) {
    vec_t *v = vec_new();
    vec_push(v, (void *)"bob1"); // push 2 elements
    vec_push(v, (void *)"bob2");

    assert_eq(vec_size(v), 2);                   // size is 2
    assert_eq(vec_get_at(v, 0), (void *)"bob1"); // order is preserved
    assert_eq(vec_get_at(v, 1), (void *)"bob2");

    char *e = (char *)vec_pop(v); // pop the last element
    assert_eq(e, (void *)"bob2");
    assert_eq(vec_size(v), 1);                   // size is now 1
    assert_eq(vec_get_at(v, 0), (void *)"bob1"); // first element is unchanged
    assert_eq(vec_get_at(v, 1), NULL);           // second element is NULL
    vec_free(v);
}

void vec_test_1(void) {
    vec_t *v = vec_new();
    int n = 1000;
    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);         // push bob0, bob1, ...
        vec_push(v, (void *)strdup(str)); // duplicate the string
    }

    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);                   // for the order
        char *e = (char *)vec_get_at(v, (size_t)i); // get the element
        assert_eq(strcmp(e, str), 0);               // compare the strings
    }
    vec_delete_all(v, free); // free all strings
    vec_free(v);
}

void vec_test_2(void) {
    vec_t *v = vec_new();
    int n = 1000;

    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);         // push bob0, bob1, ...
        vec_push(v, (void *)strdup(str)); // duplicate the string
    }
    vec_t *v2 = vec_copy(v);              // copy the vector (shallow copy)
    assert_eq(vec_size(v), vec_size(v2)); // same size
    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);                     // for the order
        char *e = (char *)vec_get_at(v, (size_t)i);   // get the element
        char *e2 = (char *)vec_get_at(v2, (size_t)i); // get the element
        assert_eq(strcmp(e, e2), 0);                  // compare the strings
        assert_eq(strcmp(e, str), 0);                 // compare the strings
    }
    vec_delete_all(v, free); // free all strings only once
    vec_free(v);
    vec_free(v2);
}

void vec_test_3(void) {
    vec_t *v = vec_new();
    int n = 1000;

    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);         // push bob0, bob1, ...
        vec_push(v, (void *)strdup(str)); // duplicate the string
    }
    vec_reverse(v);            // reverse the vector
    assert_eq(vec_size(v), n); // same size
    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", n - i - 1);           // for the order
        char *e = (char *)vec_get_at(v, (size_t)i); // get the element
        assert_eq(strcmp(e, str), 0);               // compare the strings
    }
    vec_delete_all(v, free);
    vec_free(v);
}

void vec_test_4(void) {
    vec_t *v = vec_new();
    int n = 1000;

    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);         // push bob0, bob1, ...
        vec_push(v, (void *)strdup(str)); // duplicate the string
    }

    void **arr = vec_to_array(v); // convert to array
    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);     // for the order
        char *e = (char *)arr[i];     // get the element from the array
        assert_eq(strcmp(e, str), 0); // compare the strings
    }

    vec_t *v2 = vec_from_array(arr, n);   // convert from array
    assert_eq(vec_size(v), vec_size(v2)); // same size
    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);                     // for the order
        char *e = (char *)vec_get_at(v, (size_t)i);   // get the element
        char *e2 = (char *)vec_get_at(v2, (size_t)i); // get the element
        assert_eq(strcmp(e, e2), 0);                  // compare the strings
        assert_eq(strcmp(e, str), 0);                 // compare the strings
    }
    vec_delete_all(v, free);
    vec_free(v);
    vec_free(v2);
    free(arr);
}

void vec_test_5(void) {
    vec_t *v = vec_new();
    int n = 10; // only 10 elements for alphabetic order

    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);         // push bob0, bob1, ...
        vec_push(v, (void *)strdup(str)); // duplicate the string
    }

    vec_t *v2 = vec_copy(v);              // copy the vector (shallow copy)
    assert_eq(vec_size(v), vec_size(v2)); // same size
    vec_reverse(v2);                      // reverse the vector
    vec_qsort(v2, compare_strings);       // sort the vector
    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "bob%d", i);                    // for the order
        char *e = (char *)vec_get_at(v2, (size_t)i); // get the element
        assert_eq(strcmp(e, str), 0);                // compare the strings
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
