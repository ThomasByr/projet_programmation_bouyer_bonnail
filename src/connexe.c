#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "connexe.h"
#include "dijkstra.h"

int diametre(hset_t *component)
{
    int max = 0;
    hset_itr_t *itr_beggin = hset_itr_new(component);
    while (hset_itr_has_next(itr_beggin))
    {
        hset_itr_t *itr_end = hset_itr_new(component);
        while (hset_itr_has_next(itr_end))
        {
            int a = dijkstra(hset_itr_value(itr_beggin), hset_itr_value(itr_end));
            if (a > max)
            {
                max = a;
            }
            hset_itr_next(itr_end);
        }
        hset_itr_next(itr_beggin);
        hset_itr_free(itr_end);
    }
    hset_itr_free(itr_beggin);

    return max;
}

vec_t *connexe(hset_t *nodes)
{
    vec_t *list = vec_new();
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
        hset_t *component = hset_new();
        hset_itr_t *itr_open = hset_itr_new(open);
        node_t *current = (node_t *)hset_itr_value(itr_all);
        hset_push(open, current);
        while (hset_nitems(open) != 0)
        {
            node_t *node = (node_t *)hset_itr_value(itr_open);
            hset_discard(open, node);
            hset_discard(all, node);
            hset_push(close, node);
            hset_push(component, node);

            hset_itr_t *itr_child = node->neighbors;
            while (hset_itr_has_next(itr_child))
            {
                node_t *node_child = (node_t *)hset_itr_value(itr_child);
                hset_push(open, node_child);
                hset_itr_next(itr_child);
            }
            hset_itr_next(itr_open);
        }

        int d = diametre(component);
        char str[BUFSIZ];
        sprintf(str, "%d", d);
        vec_push(list, strdup(str));
        hset_itr_next(itr_all);
    }
    return list;
}
