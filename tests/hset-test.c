#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hset.h"
#include "macros.h"

typedef struct foo_t
{
    int a;
    int b;
    char *id;
} foo_t;

foo_t *foo_new(int id)
{
    foo_t *foo = malloc(sizeof(foo_t));
    foo->a = 0;
    foo->b = 0;
    foo->id = malloc(sizeof(char) * 1000000);
    sprintf(foo->id, "%d", id);

    return foo;
}

void foo_free(foo_t *foo)
{
    free(foo->id);
    free(foo);
}

void hset_test_0(void)
{
    hset_t *hset = hset_create();

    foo_t *foo0 = foo_new(0);
    foo_t *foo1 = foo_new(0);
    foo_t *foo2 = foo_new(0);

    hset_insert(hset, foo0);
    hset_insert(hset, foo1);
    hset_insert(hset, foo2);
    hset_insert(hset, foo0);

    foo0->a = 1;
    sprintf(foo0->id, "%d", 42);
    hset_insert(hset, foo0);

    assert_eq(hset_nitems(hset), 3);

    hset_destroy(hset);
    foo_free(foo0);
    foo_free(foo1);
    foo_free(foo2);
}

void hset_test(void)
{
    test_case(hset_test_0);
}
