#include "dijkstra.h"
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

    // tant que l'on a pas exploré toute la liste, on prend le noeud de poids min et on recommence

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

                    return (end->weight);
                }

                vec_push(v_open, voisin);
            }
        }
    }
    return (-1);
}
