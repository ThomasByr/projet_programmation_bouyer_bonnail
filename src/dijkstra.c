#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "dijkstra.h"
<<<<<<< HEAD
#include "vec.h"
#include "node.h"

int find_min_weight(vec *v)
{
    node_t *min_weight = vec_get_at(v, 0);
    int index = 0;
    size_t size = vec_used(v);

    while (index <= (int)size)
    {

        printf("%d\n", index);
        node_t *test = vec_get_at(v, index);
        if (test != NULL)
        {
            if (min_weight->weight > test->weight)
            {
                min_weight = test;
            }
        }
        index++;
    }
    return index;
}

void print_elt(void *elt)
{
    node_t *e = (node_t *)elt;
    print_node(e);
}

int dijkstra(node_t *begin, node_t *end)
{

    //creation liste exploré et à explorer
    vec *v_open = (vec *)malloc(sizeof(vec));
    vec_init(v_open);
    vec *v_close = (vec *)malloc(sizeof(vec));
    vec_init(v_close);
    //le noeud de depart est exploré, on place ses voisins dans la liste à explorer, on augmente leur taille de 1
    vec_push(v_close, begin);
    vec *voisin_begin = begin->co_autors;
    size_t taille_voisin_begin = vec_used(voisin_begin);
    int index = 0;

    while ((size_t)index <= taille_voisin_begin)
    {

        node_t *voisin = vec_get_at(voisin_begin, index);
        if (voisin != NULL)
        {
            voisin->weight++;
            voisin->parent = begin;

            vec_push(v_open, voisin);
        }
        index++;
    }
=======

int dijkstra(node_t *start, node_t *end) {
    hset_t *close = hset_new();
    pqueue_t *open = pqueue_new();

    node_t *current = start;
    current->weight = 0;
    pqueue_push(open, current, current->weight);

    while (pqueue_size(open) > 0ul) {
        current = pqueue_pop_min(open); // pop the node with the lowest weight
        hset_push(close, current);      // add it to the closed set
>>>>>>> 7c92f791ee13737df0c25425f9c58acd01c9783c

        if (current == end)
            break; // if we found the end, we're done

<<<<<<< HEAD
    while (vec_used(v_open) != 0)
    {

        int index_min = find_min_weight(v_open);
        vec_print(v_open, print_elt);

        vec_print_elts(v_open);

        node_t *min = vec_get_at(v_open, index_min);

        vec_push(v_close, min);

        vec_delete_at(v_open, index_min);
        vec *voisin_min;

        voisin_min = min->co_autors;
        printf("ok\n");
        size_t taille_voisin_min = vec_used(voisin_min);
        int index = 0;

        while ((size_t)index <= taille_voisin_min)
        {
            node_t *voisin = vec_get_at(voisin_min, index);
            if (voisin != NULL)
            {
                voisin->weight++;
                voisin->parent = min;
                if (voisin == end)
                {
=======
        hset_itr_t *itr = current->neighbors; // iterate over neighbors
        while (hset_itr_has_next(itr)) {
            node_t *child = (node_t *)hset_itr_value(itr);
            int c = hset_contains(close, (void *)child);
            if (c == 0) {
                int new_weight = current->weight + 1;
                ASSERT(new_weight > 0 && new_weight < INT_MAX);
>>>>>>> 7c92f791ee13737df0c25425f9c58acd01c9783c

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
<<<<<<< HEAD
    return (-1);
=======
    hset_free(close);
    pqueue_free(open);
    return end->weight == INT_MAX ? -1 : end->weight;
}

vec_t *get_path(node_t *end) {
    vec_t *path = vec_new();
    node_t *current = end;
    while (current != NULL) {
        vec_push(path, current);
        current = current->parent;
    }
    vec_reverse(path);
    return path;
>>>>>>> 7c92f791ee13737df0c25425f9c58acd01c9783c
}
