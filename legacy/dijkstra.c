#include "dijkstra.h"
#include "vec.h"

int find_min_weight(vec *v)
{
    node_t *min_weight = vec_get_at(v, 0);
    int index = 1;
    size_t size = vec_used(v);
    while ((size_t)index <= size)
    {
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

int dijkstra(node_t *begin, node_t *end)
{
    // creation liste exploré et à explorer
    vec *v_open = (vec *)malloc(sizeof(vec));
    vec_init(v_open);
    vec *v_close = (vec *)malloc(sizeof(vec));
    vec_init(v_close);
    // first node is explored, its neighbors are placed in the
    // list of nodes to explore, their size are increased by 1
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
    }

    //while we haven't explored the whole list, we
    // take the minimum weight node and start again

    while (vec_used(v_open) != 0)
    {

        node_t *min = vec_get_at(v_open, index);
        vec_push(v_close, min);
        vec_delete_at(v_open, index);
        vec *voisin_min = min->co_autors;
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

                    return (end->weight);
                }

                vec_push(v_open, voisin);
            }
        }
    }
    return (-1);
}
