#include "n_coauteurs.h"
#include "vec.h"
vec *n_coauteurs(node_t *begin, int n)
{
    vec *coauteurs = (vec *)malloc(sizeof(vec));
    vec_init(coauteurs);
    vec *v_open = (vec *)malloc(sizeof(vec));
    vec_init(v_open);

    vec_push(coauteurs, begin);

    vec *voisin_begin = begin->co_autors;
    size_t taille_voisin_begin = vec_size(voisin_begin);
    int index = 0;

    while (index <= taille_voisin_begin)
    {
        node_t *voisin = vec_get_at(voisin_begin, index);
        if (voisin != NULL)
        {
            voisin->weight++;
            voisin->parent = begin;
            vec_push(coauteurs, voisin);
            vec_push(v_open, voisin);
        }
        index++;
    }
    int recur = 1;
    while (recur < n)
    {

        size_t taille_a_explorer = vec_size(v_open);
        int index = 0;
        while (index <= taille_a_explorer)
        {
            vec *voisin_a_explorer = ((node_t *)vec_get_at(v_open, index))->co_autors;
            int index_new = 0;
            size_t taille_voisin_explorer = vec_size(voisin_a_explorer);
            while (index_new <= taille_voisin_explorer)
            {
                node_t *voisin = vec_get_at(voisin_a_explorer, index_new);
                if (voisin != NULL)
                {
                    voisin->weight++;
                    voisin->parent = (node_t *)vec_get_at(v_open, index);
                    vec_push(coauteurs, voisin);
                    vec_push(v_open, voisin);
                }
            }
            vec_delete_at(v_open, index);
        }
        recur++;
    }
    return coauteurs;
}