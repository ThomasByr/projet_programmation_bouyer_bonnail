#include <math.h>
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
    node->mark = 0;
    return node;
}

void _free_node(heap_node_t *node) { free(node); }

void _clear(heap_node_t *node) {
    if (node != NULL) {
        heap_node_t *t1 = node;
        do {
            heap_node_t *t2 = t1;
            t1 = t1->right;
            _clear(t2->child);
            _free_node(t2);
        } while (t1 != node);
    }
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

void _push_node(pqueue_t *pq, heap_node_t *node) {
    pq->min_node = _merge(pq->min_node, node);
    pq->total_nodes++;
}

void _unparent_all(heap_node_t *node) {
    if (node == NULL)
        return;
    heap_node_t *x = node;
    do {
        x->parent = NULL;
        x = x->right;
    } while (x != node);
}

void _remove_from_circular_list(heap_node_t *node) {
    if (node->right == node)
        return;
    heap_node_t *left = node->left;
    heap_node_t *right = node->right;
    left->right = right;
    right->left = left;
}

void _make_child(heap_node_t *child, heap_node_t *parent) {
    _remove_from_circular_list(child);
    child->left = child->right = child;
    child->parent = parent;
    parent->child = _merge(parent->child, child);
    parent->degree++;
    child->mark = 0;
}

void _cut(pqueue_t *pq, heap_node_t *node1, heap_node_t *node2) {
    _remove_from_circular_list(node1);
    if (node1->right == node1)
        node2->child = NULL;
    else
        node2->child = node1->right;

    node2->degree--;
    _merge(pq->min_node, node1);
    node1->parent = NULL;
    node1->mark = 0;
}

void _cascading_cut(pqueue_t *pq, heap_node_t *node) {
    heap_node_t *parent = node->parent;
    if (parent != NULL) {
        if (node->mark == 0)
            node->mark = 1;
        else {
            _cut(pq, node, parent);
            _cascading_cut(pq, parent);
        }
    }
}

void _decrease_key(pqueue_t *pq, heap_node_t *node, int new_key) {
    node->key = new_key;
    heap_node_t *parent = node->parent;
    if (parent != NULL && node->key < parent->key) {
        _cut(pq, node, parent);
        _cascading_cut(pq, parent);
    }
    if (node->key < pq->min_node->key)
        pq->min_node = node;
}

void _consolidate(pqueue_t *pq) {
    int dn = (int)(log2f((float)pq->total_nodes) / log2f(1.618f));
    heap_node_t *a[dn + 1];
    for (int i = 0; i <= dn; i++)
        a[i] = NULL;
    heap_node_t *x = pq->min_node;
    int break_flag = 0;
    while (1) {
        int d = x->degree;
        while (a[d] != NULL) {
            heap_node_t *y = a[d];
            if (x == y) {
                break_flag = 1; // all root nodes have different degree
                break;          // break the loop
            }
            if (x->key > y->key) {
                heap_node_t *tmp = x;
                x = y;
                y = tmp;
            }                  // x is the smaller node
            _make_child(y, x); // make y the child of x
            a[d++] = NULL;     // new node has d+1 child, a[d] = NULL, d = d + 1
        }
        if (break_flag)
            break;
        a[x->degree] = x;
    }
    pq->min_node = x; // update min node
    heap_node_t *iter = x;
    do {
        if (iter->key < pq->min_node->key)
            pq->min_node = iter;
        iter = iter->right;
    } while (iter != x);
}

heap_node_t *_extract_min_node(pqueue_t *pq) {
    heap_node_t *min_node = pq->min_node;
    if (min_node != NULL) {
        _unparent_all(min_node->child);
        _merge(min_node, min_node->child);
        _remove_from_circular_list(min_node);
        // the heap will be empty after the operation
        if (min_node == min_node->right)
            pq->min_node = NULL;
        else {
            pq->min_node = min_node->right;
            _consolidate(pq);
        }
        pq->total_nodes--;
    }
    return min_node;
}

pqueue_t *pqueue_new() {
    pqueue_t *pq = malloc(sizeof(struct pqueue_s));
    pq->min_node = NULL;
    pq->total_nodes = 0;

    pq->map = dict_new();
    return pq;
}

void pqueue_free(pqueue_t *pq) {
    dict_free(pq->map);
    while (pq->min_node != NULL) {
        heap_node_t *node = _extract_min_node(pq);
        free(node);
    }
    free(pq);
}

size_t pqueue_size(pqueue_t *pq) { return pq->total_nodes; }

void *pqueue_find_min(pqueue_t *pq) { return pq->min_node->element; }

void *pqueue_pop_min(pqueue_t *pq) {
    heap_node_t *min_node = _extract_min_node(pq);
    void *ret = min_node->element;
    dict_discard(pq->map, ret);
    _free_node(min_node);
    return ret;
}

void pqueue_merge(pqueue_t *pq1, pqueue_t *pq2) {
    pq1->min_node = _merge(pq1->min_node, pq2->min_node);
    pq1->total_nodes += pq2->total_nodes;
    pq2->min_node = NULL;
    dict_free(pq2->map);
    pq2->map = dict_new();
    pq2->total_nodes = 0;
}

int pqueue_push(pqueue_t *pq, void *element, int key) {
    heap_node_t *node = _create_node(element, key);
    int rv = dict_get(pq->map, element) != NULL ? 0 : 1;

    if (rv) {
        _push_node(pq, node);
        dict_push(pq->map, element, (void *)node);
    }
    return rv;
}

int pqueue_decrease_key(pqueue_t *pq, void *element, int new_key) {
    heap_node_t *node = (heap_node_t *)dict_get(pq->map, element);
    if (node == NULL)
        return -1;
    if (new_key >= node->key)
        return 0;

    _decrease_key(pq, node, new_key);
    return 1;
}