#include <stdio.h>
#include <stdlib.h>

#include "dijkstra.h"

void _set_path(vec *path, node_t *end) {
    node_t *node = end;
    while (node != NULL) {
        vec_push(path, node);
        node = node->parent;
    }
}

vec *dijkstra(node_t *start, node_t *end) {
    vec *path = vec_new();
    hset_t *close = hset_new();
    pqueue_t *open = pqueue_new();

    node_t *current = start;
    current->weight = 0;
    pqueue_push(open, current, current->weight);

    while (pqueue_size(open) > 0ul) {
        current = pqueue_pop_min(open); // pop the node with the lowest weight
        hset_push(close, current);      // add it to the closed set

        if (current == end) {
            _set_path(path, current);
            break;
        }
        hset_itr_t *itr = hset_itr_new(current->neighbors);
        while (hset_itr_has_next(itr)) {
            node_t *child = (node_t *)hset_itr_val(itr);
            if (!hset_contains(close, child)) {
                int new_weight = current->weight + 1;

                // if child was never visited before, weight is infinity
                if (new_weight < child->weight) {
                    child->weight = new_weight;
                    child->parent = current;

                    // if child already in open set, update its weight
                    int rv =
                        pqueue_decrease_key(open, (void *)child, new_weight);
                    switch (rv) {
                    case -1: // node not in the open set
                        pqueue_push(open, child, new_weight);
                        break;
                    case 0: // node in the open set, but with a higher weight
                    case 1: // node in the open set, but with the same weight
                    default:
                        break;
                    }
                }
            }
            hset_itr_next(itr); // advance to next child
        }
        hset_itr_free(itr);
    }
    hset_free(close);
    pqueue_free(open);
    return path;
}
