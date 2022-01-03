#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "node.h"

node_t *node_new(char *name, hset_t *neighbors, hset_t *papers)
{
    node_t *node = malloc(sizeof(node_t));
    ASSERT(node);
    node->weight = INT_MAX;
    node->name = name;
    node->parent = NULL;
    node->neighbors = hset_itr_new(neighbors);
    node->papers = hset_itr_new(papers);
    return node;
}

void node_free(node_t *node)
{
    hset_itr_free(node->neighbors);
    hset_itr_free(node->papers);
    free(node);
}
