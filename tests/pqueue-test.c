#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "foo.h"
#include "macros.h"
#include "pqueue.h"

void pqueue_test_0(void) {
    pqueue_t *pq = pqueue_new();
    pqueue_push(pq, (void *)"bob1", 1); // bob1 with key 1
    pqueue_push(pq, (void *)"bob2", 2); // bob2 with key 2
    pqueue_push(pq, (void *)"bob3", 3); // bob3 with key 3
    assert_eq(pqueue_size(pq), 3);      // we pushed 3 items

    assert_eq(pqueue_find_min(pq), "bob1");     // bob1 is the min
    pqueue_decrease_key(pq, (void *)"bob3", 0); // decrease bob3's key to 0
    assert_eq(pqueue_find_min(pq), "bob3");     // bob3 is the min

    char *min = (char *)pqueue_pop_min(pq); // pop the min
    assert_eq(strcmp(min, "bob3"), 0);      // bob3 was the min
    assert_eq(pqueue_find_min(pq), "bob1"); // bob1 is the min
    assert_eq(pqueue_size(pq), 2);          // we popped 1 item

    pqueue_free(pq);
}

void pqueue_test_1(void) {
    pqueue_t *pq = pqueue_new();
    int n = 1000;
    for (int i = 0; i < n; i++) {
        foo_t *foo = foo_new(i);                // make a random large object
        foo->a = 1;                             // set a to 1
        int priority = n - i;                   // set priority to n - i
        int x = pqueue_push(pq, foo, priority); // push foo with priority
        foo->a = 42;                            // set a to 42
        foo->b = priority;                      // set b to priority
        assert_eq(x, 1);                        // we pushed 1 item
    }
    assert_eq(pqueue_size(pq), n); // we pushed n items in total
    foo_t *foo = NULL;
    int priority = 0;
    while ((foo = (foo_t *)pqueue_pop_min(pq)) != NULL) {
        assert_eq(foo->a, 42);         // a is 42
        assert_eq(foo->b, ++priority); // b is priority
        foo_free(foo);
    } // pop each item in priority order
    assert_eq(pqueue_size(pq), 0);
    pqueue_free(pq);
}

void pqueue_test_2(void) {
    pqueue_t *pq = pqueue_new();
    int n = 1000;
    char str[100];
    void *item;
    for (int i = 0; i < n; i++) {
        sprintf(str, "%d", i);
        item = (void *)strdup(str);
        int x = pqueue_push(pq, item, i);
        assert_eq(x, 1);
        free((char *)pqueue_pop_min(pq));
    }
    assert_eq(pqueue_size(pq), 0);
    pqueue_free(pq);
}

void pqueue_test(void) {
    test_case(pqueue_test_0);
    test_case(pqueue_test_1);
    test_case(pqueue_test_2);
}
