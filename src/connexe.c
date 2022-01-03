#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "connexe.h"

int connexe(hset_t *nodes)
{
    hset_itr_t *itr = hset_itr_new(nodes);
    hset_t *all = hset_new();
    int compt = 0;
    while (hset_itr_has_next(itr))
    {
        hset_push(all, (void *)hset_itr_value(itr));
        hset_itr_next(itr);
    }
    hset_itr_t *itr_all = hset_itr_new(all);
    while (hset_nitems(all) > 0)
    {
        compt++;
        hset_t *close = hset_new();
        hset_t *open = hset_new();
        hset_itr_t *itr_open = hset_itr_new(open);
        node_t *current = hset_itr_value(itr_all);
        hset_push(open, current);
        while (hset_nitems(open) != 0)
        {
            node_t *node = hset_itr_value(itr_open);
            hset_discard(open, node);
            hset_discard(all, node);
            hset_push(close, node);

            hset_itr_t *itr_child = node->neighbors;
            while (hset_itr_has_next(itr_child))
            {
                node_t *node_child = hset_itr_value(itr_child);
                hset_push(open, node_child);
                hset_itr_next(itr_child);
            }
            hset_itr_next(itr_open);
        }
        hset_itr_next(itr_all);
    }
    return compt;
}