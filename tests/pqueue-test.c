#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "foo.h"
#include "macros.h"
#include "pqueue.h"

void pqueue_test_0(void) {
    pqueue_t *pq = pqueue_new();
    pqueue_push(pq, (void *)"bob1", 1);
    pqueue_push(pq, (void *)"bob2", 2);
    pqueue_push(pq, (void *)"bob3", 3);
    assert_eq(pqueue_size(pq), 3);

    assert_eq(pqueue_find_min(pq), "bob1");
    pqueue_decrease_key(pq, (void *)"bob3", 0);
    assert_eq(pqueue_find_min(pq), "bob3");

    char *min = (char *)pqueue_pop_min(pq);
    assert_eq(strcmp(min, "bob3"), 0);
    assert_eq(pqueue_find_min(pq), "bob1");
    assert_eq(pqueue_size(pq), 2);

    pqueue_free(pq);
}

void pqueue_test_1(void) {
    pqueue_t *pq = pqueue_new();
    int n = 1000;
    for (int i = 0; i < n; i++) {
        foo_t *foo = foo_new(i);
        foo->a = 1;
        int priority = n - i;
        int x = pqueue_push(pq, foo, priority);
        foo->a = 42;
        foo->b = priority;
        assert_eq(x, 1);
    }
    assert_eq(pqueue_size(pq), n);
    foo_t *foo = NULL;
    int priority = 0;
    while ((foo = (foo_t *)pqueue_pop_min(pq)) != NULL) {
        assert_eq(foo->a, 42);
        assert_eq(foo->b, ++priority);
        foo_free(foo);
    }
    assert_eq(pqueue_size(pq), 0);
    pqueue_free(pq);
}

void pqueue_test(void) {
    test_case(pqueue_test_0);
    test_case(pqueue_test_1);
}
