#include <stdio.h>
#include <stdlib.h>

#include "pqueue.h"

heap_node_t *_create_node(void *element, int key) {
    heap_node_t *node = malloc(sizeof(heap_node_t));
    node->element = element;
    node->key = key;

    node->left = node;
    node->right = node;
    node->parent = NULL;
    node->child = NULL;
    node->degree = 0;
    node->marked = 0;
    return node;
}

heap_node_t *_merge(heap_node_t *x, heap_node_t *y) {
    if (x == NULL)
        return y;
    if (y == NULL)
        return x;

    if (x->key > y->key) {
        heap_node_t *tmp = x;
        x = y;
        y = tmp;
    } // swap nodes
    heap_node_t *xr = x->right;
    heap_node_t *yl = y->left;
    x->right = y;
    y->left = x;
    xr->left = yl;
    yl->right = xr;
    return x;
}

void _pqueue_push(pqueue_t *pq, heap_node_t *node) {
    pq->min_node = _merge(pq->min_node, node);
    pq->total_nodes++;
}

pqueue_t *pqueue_new() {
    pqueue_t *pq = malloc(sizeof(struct pqueue_s));
    pq->min_node = NULL;
    pq->total_nodes = 0;

    pq->nodes = hset_new();
    pq->map = hset_itr_new(pq->nodes);
}

void pqueue_free(pqueue_t *pq) {
    hset_itr_free(pq->map);
    hset_free(pq->nodes);
    free(pq);
}

heap_node_t *pqueue_find_min(pqueue_t *pq) { return pq->min_node; }
