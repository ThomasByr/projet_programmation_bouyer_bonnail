#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "node.h"

node_t *node_new(char *name, hset_t *neighbors) {
    node_t *node = malloc(sizeof(node_t));
    node->weight = INT_MAX;
    node->name = name;
    node->parent = NULL;
    node->neighbors = hset_itr_new(neighbors);
    return node;
}

void node_free(node_t *node) {
    hset_itr_free(node->neighbors);
    free(node);
}
