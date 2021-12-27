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

    while (pqueue_size(open) > 0ul) {
        current = pqueue_pop_min(open); // pop the node with the lowest weight
        hset_push(close, current);      // add it to the closed set

        if (current == end)
            break; // if we found the end, we're done

        hset_itr_t *itr = current->neighbors; // iterate over neighbors
        while (hset_itr_has_next(itr)) {
            node_t *child = (node_t *)hset_itr_value(itr);
            int c = hset_contains(close, (void *)child);
            if (c == 0) {
                int new_weight = current->weight + 1;

                // if child was never visited before, weight is infinity
                if (new_weight < child->weight) {
                    child->weight = new_weight;
                    child->parent = current;

                    // if child already in open set, update its weight
                    int rv = pqueue_push(open, child, new_weight);
                    if (rv == 0)
                        pqueue_decrease_key(open, child, new_weight);
                }
            }
            hset_itr_next(itr); // advance to next child
        }
    }
    hset_free(close);
    pqueue_free(open);
    return end->weight == INT_MAX ? -1 : end->weight;
}
