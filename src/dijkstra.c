#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "dijkstra.h"

int dijkstra(node_t *start, node_t *end) {
    hset_t *close = hset_new();
    pqueue_t *open = pqueue_new();

    node_t *current = start;
    current->weight = 0;
    pqueue_push(open, current, current->weight);
    _status = GRAPH_WALKTHROUGH;

    while (pqueue_size(open) > 0ul) {
        current = pqueue_pop_min(open); // pop the node with the lowest weight
        if (current == NULL || current->weight == INT_MAX)
            break;

        hset_push(close, current); // add it to the closed set

        if (current == end)
            break; // if we found the end, we're done

        hset_itr_t *itr = current->neighbors; // iterate over neighbors
        hset_itr_reset(itr);
        while (hset_itr_has_next(itr)) {
            node_t *child = (node_t *)hset_itr_value(itr);
            int c = hset_contains(close, (void *)child);
            if (c == 0) {
                int new_weight = current->weight + 1;
                ASSERT(new_weight > 0 && new_weight < INT_MAX);

                // if child was never visited before, weight is infinity
                // if the new weight is less than the old weight, update
                if (new_weight < child->weight) {
                    child->weight = new_weight;
                    child->parent = current;

                    // add child to open priority queue
                    // if child already in open, update its weight
                    int rv = pqueue_push(open, (void *)child, new_weight);
                    ASSERT(rv != -1 && rv != 2); // bad key or realloc fail
                    if (rv == 0)
                        pqueue_decrease_key(open, (void *)child, new_weight);
                }
            }
            hset_itr_next(itr); // advance to next child
        }
    }
    hset_free(close);
    pqueue_free(open);
    return end->weight == INT_MAX ? -1 : end->weight;
}

vec_t *get_path(node_t *end) {
    vec_t *path = vec_new();
    node_t *current = end;
    while (current != NULL) {
        vec_push(path, current);   // add current to path
        current = current->parent; // move to parent
    }                              // path is in reverse order
    vec_reverse(path);             // reverse path
    return path;
}
