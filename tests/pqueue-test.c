#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "pqueue.h"

void pqueue_test_0(void) {
    pqueue_t *pq = pqueue_new();
    pqueue_push(pq, (void *)"bob1", 1);
    pqueue_push(pq, (void *)"bob2", 2);
    pqueue_push(pq, (void *)"bob3", 3);

    assert_eq(pqueue_find_min(pq), (void *)"bob1");
    pqueue_decrease_key(pq, (void *)"bob3", 0);
    assert_eq(pqueue_find_min(pq), (void *)"bob3");

    char *min = (char *)pqueue_pop_min(pq);
    assert_eq(strcmp(min, "bob3"), 0);
    assert_eq(pqueue_find_min(pq), (void *)"bob1");

    pqueue_free(pq);
}

void pqueue_test(void) { test_case(pqueue_test_0); }
