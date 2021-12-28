/*

*/

#ifndef NODE_H
#define NODE_H

#include "hset.h"
#include "types.h"

struct node_s {
    char *name;
    hset_itr_t *neighbors;
    hset_itr_t *publications;
    int weight;
    struct node_s *parent;
};
typedef struct node_s node_t;

/**
 * @brief new node with an infinite weight
 *
 * @param name name of the author
 * @param neighbors set of neighbors
 * @return node_t*
 */
node_t *node_new(char *name, hset_t *neighbors);

/**
 * @brief free node structure and its iterators
 *
 * @param node node to free
 */
void node_free(node_t *node);

#endif
