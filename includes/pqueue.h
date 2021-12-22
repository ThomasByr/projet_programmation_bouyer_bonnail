/*

*/

#ifndef PQUEUE_H
#define PQUEUE_H

#include "hset.h"
#include "types.h"

struct heap_node_s {
    void *element;              // pointer to the element
    int priority;               // ?
    struct heap_node_s *parent; // parent node
    struct heap_node_s *left;   // node "to the left"
    struct heap_node_s *right;  // node "to the right"
    struct heap_node_s *child;  // child node
    size_t degree;              // number of children
    int marked;                 // is this node marked for deletion?
};
typedef struct heap_node_s heap_node_t;

struct pqueue_s {
    hset_t *nodes;         // collection of nodes
    hset_itr_t *map;       // unordered map of nodes
    heap_node_t *min_node; // minimum node
    size_t total_nodes;    // total number of nodes

    compare_fn_t *cmp; // pointer to compare function
    equals_fn_t *eq;   // pointer to equals function
};
/**
 * @brief priority queue data structure using Fibonacci heap
 *
 */
typedef struct pqueue_s pqueue_t;

heap_node_t *heap_node_new(void *element, int priority);

void heap_node_free(heap_node_t *node);

pqueue_t *pqueue_new(compare_fn_t *cmp, equals_fn_t *eq);

heap_node_t *pqueue_find_min(pqueue_t *pq);

heap_node_t *pqueue_pop_min(pqueue_t *pq);

int pqueue_push(pqueue_t *pq, void *element, int priority);

int pqueue_decrease_key(pqueue_t *pq, heap_node_t *node, int priority);

int pqueue_consolidate(pqueue_t *pq);

pqueue_t *pqueue_merge(pqueue_t *pq1, pqueue_t *pq2);

void pqueue_free(pqueue_t *pq);

#endif
