#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "connexe.h"
#include "dijkstra.h"

int diametre(hset_t *component) {
    // detection of the biggest distance between two nodes of the same connected
    // component
    int max = 0;
    hset_itr_t *itr_beggin = hset_itr_new(component);

    while (hset_itr_has_next(itr_beggin)) {
        hset_itr_t *itr_end = hset_itr_new(component);
        while (hset_itr_has_next(itr_end)) {
            // distance between all nodes n1 and n2 possible with n1
            // corresponding to itr_beggin and n2 to itr_end
            node_t *n1 = (node_t *)hset_itr_next(itr_beggin);
            node_t *n2 = (node_t *)hset_itr_next(itr_end);
            int a = dijkstra(n1, n2);
            max = (a > max) ? a : max;
            hset_itr_next(itr_end);
        }
        hset_itr_next(itr_beggin);
        hset_itr_free(itr_end);
    }
    hset_itr_free(itr_beggin);

    return max;
}

vec_t *connexe(hset_t *nodes) {
    // width first search
    vec_t *list = vec_new();
    hset_itr_t *itr = hset_itr_new(nodes);
    hset_t *all = hset_new();
    int compt = 0;

    while (hset_itr_has_next(itr)) {
        hset_push(all, (void *)hset_itr_value(itr));
        hset_itr_next(itr);
    }

    hset_itr_t *itr_all = hset_itr_new(all);
    // this loop is used to detect the connected components
    while (hset_nitems(all) > 0) {
        compt++;
        hset_t *close = hset_new();
        hset_t *open = hset_new();
        hset_t *component = hset_new();
        hset_itr_t *itr_open = hset_itr_new(open);

        node_t *current = (node_t *)hset_itr_value(itr_all);
        hset_push(open, current);

        // this loop is used to go through the component
        while (hset_nitems(open) != 0) {
            node_t *node = (node_t *)hset_itr_value(itr_open);
            hset_discard(open, node);
            hset_discard(all, node);
            hset_push(close, node);
            hset_push(component, node);

            hset_itr_t *itr_child = node->neighbors;
            // this loop is used to detect the neighbors of the current node
            while (hset_itr_has_next(itr_child)) {
                node_t *node_child = (node_t *)hset_itr_value(itr_child);
                hset_push(open, node_child);
                hset_itr_next(itr_child);
            }
            hset_itr_next(itr_open);
        }

        int *d = malloc(sizeof(int));
        *d = diametre(component);
        vec_push(list, d);

        hset_itr_next(itr_all);
        hset_free(component);
        hset_free(open);
        hset_free(close);
    }
    hset_free(all);
    hset_itr_free(itr);
    hset_itr_free(itr_all);
    return list;
}
