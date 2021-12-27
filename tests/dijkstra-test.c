#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dijkstra.h"
#include "macros.h"
#include "node.h"

void dijkstra_test_0(void) {
    // creer deux noeuds voisins et voir si il ressort bien ce qu'il faut
    node_t *n1 = node_new("bob1", hset_new());
    node_t *n2 = node_new("bob2", hset_new());
    hset_push(n2->neighbors->set, n1);
    hset_push(n1->neighbors->set, n2);

    int d = dijkstra(n1, n2);
    assert_eq(d, 1);
    hset_free(n1->neighbors->set);
    hset_free(n2->neighbors->set);
    node_free(n1);
    node_free(n2);
}

void dijkstra_test_1(void) {
    // creer deux noeuds voisins et voir si il ressort bien ce qu'il faut
    node_t *n1 = node_new("bob1", hset_new());
    node_t *n2 = node_new("bob2", hset_new());

    int d = dijkstra(n1, n2);
    assert_eq(d, -1);
    hset_free(n1->neighbors->set);
    hset_free(n2->neighbors->set);
    node_free(n1);
    node_free(n2);
}

void dijkstra_test(void) {
    test_case(dijkstra_test_0);
    test_case(dijkstra_test_1);
}
