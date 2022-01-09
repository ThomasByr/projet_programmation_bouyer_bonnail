/* pqueue.h
Priority queue implementation using a Fibonacci heap.

User should not use `heap_node_t` directly.

*/

#ifndef PQUEUE_H
#define PQUEUE_H

#include "dict.h"
#include "types.h"

struct heap_node_s {
    void *element;              // pointer to the element
    int key;                    // priority of the element
    struct heap_node_s *parent; // parent node
    struct heap_node_s *left;   // node "to the left"
    struct heap_node_s *right;  // node "to the right"
    struct heap_node_s *child;  // child node
    int degree;                 // number of children
    int mark;                   // is this node mark for deletion?
};
/**
 * @brief user should not use this structure directly
 *
 */
typedef struct heap_node_s heap_node_t;

struct pqueue_s {
    dict_t *map;           // correspondence between elements and nodes
    heap_node_t *min_node; // minimum node
    size_t total_nodes;    // total number of nodes
};
/**
 * @brief priority queue data structure using Fibonacci heap
 *
 */
typedef struct pqueue_s pqueue_t;

/**
 * @brief create a new priority queue
 *
 * @return pqueue_t*
 */
pqueue_t *pqueue_new();

/**
 * @brief get total node in the priority queue
 *
 * @param pq priority queue
 * @return size_t
 */
size_t pqueue_size(pqueue_t *pq);

/**
 * @brief get the minimum element of the priority queue
 *
 * @param pq priority queue
 * @return void*
 */
void *pqueue_find_min(pqueue_t *pq);

/**
 * @brief get the minimum element of the priority queue and remove it.
 * The node is freed but the element is still accessible
 *
 * @param pq priority queue
 * @return void*
 */
void *pqueue_pop_min(pqueue_t *pq);

/**
 * @brief insert an element into the priority queue.
 * Does nothing if the element is already present
 *
 * @param pq priority queue
 * @param element element to insert
 * @param key priority of the element
 * @return int - `-1` if error (bad key value),
 * `0` if already present (no change),
 * `1` if added (new entry),
 * `2` if rehash did not work (priority queue integrity compromised)
 */
int pqueue_push(pqueue_t *pq, void *element, int key);

/**
 * @brief decrease the priority of an element
 *
 * @param pq priority queue
 * @param element element to decrease the priority
 * @param new_key new priority
 * @return int - 1 if success, 0 if element does have a lower priority,
 * -1 if element does not exist
 */
int pqueue_decrease_key(pqueue_t *pq, void *element, int new_key);

/**
 * @brief merge second priority queue into the first one.
 * The second priority queue is reset.
 * Due to limitations, user should be aware that duplicated nodes
 * may cause the first priority queue to become corrupted.
 *
 * @note Do not use this function please.
 *
 * @param pq1 first priority queue
 * @param pq2 second priority queue
 */
void pqueue_merge(pqueue_t *pq1, pqueue_t *pq2);

/**
 * @brief free the priority queue and all its nodes (might be expensive)
 *
 * @param pq priority queue
 */
void pqueue_free(pqueue_t *pq);

#endif
