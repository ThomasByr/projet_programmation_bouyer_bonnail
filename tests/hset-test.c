#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "foo.h"
#include "hset.h"
#include "macros.h"

void hset_test_0(void) {
    hset_t *hset = hset_new();

    foo_t *foo0 = foo_new(0); // make a random large object
    foo_t *foo1 = foo_new(0);
    foo_t *foo2 = foo_new(0);

    hset_push(hset, foo0); // add to the set
    hset_push(hset, foo1);
    hset_push(hset, foo2);
    hset_push(hset, foo0); // add the same object again

    foo0->a = 1; // modify the object
    sprintf(foo0->id, "%d", 42);
    hset_push(hset, foo0); // add the same object again

    assert_eq(hset_nitems(hset), 3); // we added 3 items

    hset_free(hset);
    foo_free(foo0);
    foo_free(foo1);
    foo_free(foo2);
}

void hset_test_1(void) {
    hset_t *hset = hset_new();
    hset_itr_t *itr = hset_itr_new(hset);
    size_t n = 1000;

    for (size_t i = 0; i < n; i++) {
        foo_t *foo = foo_new(i);      // make a random large object
        foo->a = 42;                  // set a to 42
        int x = hset_push(hset, foo); // push foo
        assert_eq(x, 1);              // we pushed 1 item
    }

    assert_eq(hset_nitems(hset), n); // we pushed n items in total
    size_t count = 0;                // count the number of items
    while (hset_itr_has_next(itr)) {
        count++;
        foo_t *foo = (foo_t *)hset_itr_value(itr); // get the value
        assert_eq(foo->a, 42);                     // a is 42
        foo->a = 1;                                // modify the value
        int x = hset_push(hset, foo);              // add the same object again
        assert_eq(x, 0);                           // we didn't push anything
        hset_itr_next(itr);                        // move to the next item
    }
    assert_eq(count, n);             // we iterated over n items
    assert_eq(hset_nitems(hset), n); // we added n items in total
    hset_itr_reset(itr);             // reset the iterator

    while (hset_itr_has_next(itr)) {
        foo_t *foo = (foo_t *)hset_itr_value(itr); // get the value
        foo_free(foo);                             // free the value
        hset_itr_next(itr);                        // move to the next item
    }
    hset_itr_free(itr);
    hset_free(hset);
}

void hset_test_2(void) {
    hset_t *hset = hset_new();
    hset_itr_t *itr = hset_itr_new(hset);
    size_t n = 1000;

    for (size_t i = 0; i < n; i++) {
        foo_t *foo = foo_new(i); // make a random large object
        foo->a = 1;              // set a to 1
        hset_push(hset, foo);    // push foo
        foo->a = 42;             // set a to 42
    }

    assert_eq(hset_nitems(hset), n);              // we pushed n items in total
    int a = 42;                                   // a is 42
    void *data = &a;                              // data is a pointer to a
    hset_itr_for_each(itr, foo_cmp_a_void, data); // iterate over the set

    hset_itr_discard_all(itr, foo_free_void); // free all the items
    hset_itr_free(itr);
    hset_free(hset);
}

void hset_test_3(void) {
    hset_t *hset = hset_new();
    hset_push(hset, (void *)"foo"); // push a string
    hset_push(hset, (void *)"bar");
    hset_push(hset, (void *)"foo");
    assert_eq(hset_nitems(hset), 2); // we added 2 items

    hset_free(hset);
}

void hset_test_4(void) {
    hset_t *hset = hset_new();
    hset_itr_t *itr = hset_itr_new(hset);
    size_t n = 1000;

    for (size_t i = 0; i < n; i++) {
        foo_t *foo = foo_new((int)i); // make a random large object
        foo->a = 42;                  // set a to 42
        hset_push(hset, foo);         // push foo
    }
    hset_t *cpy = hset_copy(hset);   // make a copy of the set
    hset_itr_discard_all(itr, NULL); // discard all the items
    hset_itr_free(itr);              // free the iterator

    assert_eq(hset_nitems(hset), 0); // we discarded all the items
    assert_eq(hset_nitems(cpy), n);  // we copied n items

    itr = hset_itr_new(cpy);                      // make a new iterator
    int a = 42;                                   // a is 42
    void *data = &a;                              // data is a pointer to a
    hset_itr_for_each(itr, foo_cmp_a_void, data); // iterate over the set
    hset_itr_discard_all(itr, foo_free_void);     // free all the items

    hset_itr_free(itr);
    hset_free(cpy);
    hset_free(hset);
}

void hset_test_5(void) {
    hset_t *hset = hset_new();
    size_t n = 1000;

    for (size_t i = 0; i < n; i++) {
        foo_t *foo = foo_new((int)i); // make a random large object
        foo->a = 42;                  // set a to 42
        foo->b = 24;                  // set b to 24
        hset_push(hset, foo);         // push foo
    }

    for (size_t i = 0; i < n; i++) {
        size_t item = hset_pop(hset);            // pop a random item
        assert_gt(item, 0);                      // we popped an item
        foo_t *foo = (foo_t *)(item);            // get the value
        assert_eq(foo->a, 42);                   // a is 42
        assert_eq(foo->b, 24);                   // b is 24
        assert_geq(atoi(foo->id), 0);            // id is a positive integer
        assert_eq(hset_nitems(hset), n - i - 1); // we popped 1 item
        foo_free(foo);                           // free the value
    }
    hset_free(hset);
}

void hset_test_6(void) {
    hset_t *hset = hset_new();
    size_t n = 1000;

    for (size_t i = 0; i < n; i++) {
        char id[100];                         // temporary buffer
        sprintf(id, "%s", "test string");     // write a string to the buffer
        int rv = hset_push(hset, strdup(id)); // push a copy of the string
        assert_eq(rv, 1);                     // we pushed a new item
    }
    for (size_t i = 0; i < n; i++) {
        char *id = (char *)hset_pop(hset);       // pop a random item
        assert_eq(strcmp(id, "test string"), 0); // compare contents
        free(id);                                // free the value
    }
    hset_free(hset);
}

void hset_test_7(void) {
    hset_t *hset0 = hset_new();
    hset_t *hset1 = hset_new(1); // set that hashes content instead of pointers

    char *str = "foo";        // a string that will be used as a key
    char *str1 = strdup(str); // a copy of the string
    char *str2 = strdup(str); // a copy of the string

    hset_push(hset0, str1); // push a copy of the string
    hset_push(hset0, str2);
    hset_push(hset1, str1);
    hset_push(hset1, str2);

    assert_eq(hset_nitems(hset0), 2); // we pushed 2 items
    assert_eq(hset_nitems(hset1), 1); // we pushed 1 item

    free(str1);
    free(str2);
    hset_free(hset0);
    hset_free(hset1);
}

void hset_test_8(void) {
    hset_t *hset0 = hset_new();
    hset_t *hset1 = hset_new(1); // set that hashes content instead of pointers
    int n = 1000;

    char *str = "foo";        // a string that will be used as a key
    char *str1 = strdup(str); // a copy of the string
    hset_push(hset0, str1);   // push a copy of the string
    hset_push(hset1, str1);

    for (int i = 0; i < n; i++) {
        str1 = strdup(str);                       // make a copy of the string
        assert_eq(hset_contains(hset0, str1), 0); // hset0 does not contain str1
        assert_eq(hset_contains(hset1, str1), 1); // hset1 does contain str1
        int rv0 = hset_push(hset0, str1);         // push a copy of the string
        int rv1 = hset_push(hset1, str1);         // push a copy of the string
        assert_eq(rv0, 1);                        // we pushed a new item
        assert_eq(rv1, 0);                        // we did not push a new item
        assert_eq(hset_contains(hset0, str1), 1); // hset0 does contain str1
        assert_eq(hset_contains(hset1, str1), 1); // hset1 does contain str1
    }
    assert_eq(hset_nitems(hset0), n + 1); // we pushed n + 1 items
    assert_eq(hset_nitems(hset1), 1);     // we pushed 1 item

    for (int i = 0; i < n + 1; i++) {
        char *str1 = (char *)hset_pop(hset0); // pop a random item
        assert_eq(strcmp(str1, str), 0);      // compare contents
        free(str1);                           // free the value
    }
    hset_free(hset0);
    hset_free(hset1);
}

void hset_test_9(void) {
    hset_t *hset = hset_new();
    int n = 1000;

    char *str = "foo"; // a string that will be used as a key
    for (int i = 0; i < n; i++) {
        char *item = strdup(str);            // make a copy of str
        int rv0 = hset_contains(hset, item); // check item in hset
        assert_eq(rv0, 0);                   // item not in hset
        int rv1 = hset_push(hset, item);     // push a copy of str
        assert_eq(rv1, 1);                   // we pushed a new item
        int rv2 = hset_contains(hset, item); // check item in hset
        assert_eq(rv2, 1);                   // item in hset
        int rv3 = hset_discard(hset, item);  // discard the item
        assert_eq(rv3, 1);                   // we discarded the item
        int rv4 = hset_contains(hset, item); // check item in hset
        assert_eq(rv4, 0);                   // item not in hset
        int rv5 = hset_discard(hset, item);  // discard the item
        assert_eq(rv5, 0);                   // we did not discard the item
        free(item);                          // free the copy of the str
    }
    assert_eq(hset_nitems(hset), 0); // hset is empty
    hset_free(hset);
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
    test_case(hset_test_9);
}
