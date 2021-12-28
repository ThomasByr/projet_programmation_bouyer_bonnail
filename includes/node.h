/*

*/

#ifndef NODE_H
#define NODE_H

#include "hset.h"
#include "types.h"

struct node_s {
    char *name;
    hset_itr_t *neighbors;
    hset_itr_t *papers;
    int weight;
    struct node_s *parent;
};
typedef struct node_s node_t;

/**
 * @brief new node with an infinite weight
 *
 * @param name name of the author
 * @param neighbors set of neighbors
 * @param papers set of scientific papers
 * @return node_t*
 */
node_t *node_new(char *name, hset_t *neighbors, hset_t *papers);

/**
 * @brief free node structure and its iterators (not the sets)
 *
 * @param node node to free
 */
void node_free(node_t *node);

#endif
