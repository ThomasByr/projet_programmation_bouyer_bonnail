/* node.h
Main node struct for the data base.

*/

#ifndef NODE_H
#define NODE_H

#include "hset.h"
#include "protocol.h"
#include "types.h"

struct node_s {
    char *name;            // name of the author
    hset_itr_t *neighbors; // set of neighbor nodes
    hset_itr_t *papers;    // set of paper titles
    int weight;            // weight of the node (distance from start)
    struct node_s *parent; // parent node
};
typedef struct node_s node_t;

/**
 * @brief new node with an infinite weight
 *
 * @param name name of the author
 * @param neighbors set of neighbor nodes
 * @param papers set of scientific paper titles
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
