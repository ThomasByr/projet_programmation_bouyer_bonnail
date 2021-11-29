#include "n_coauteurs.h"
#include "vec.h"
vec n_coauteurs(node_t *begin, int n)
{
    vec *coauteurs = (vec *)malloc(sizeof(vec));
    vec_init(coauteurs);
    vec *v_open = (vec *)malloc(sizeof(vec));
    vec_init(v_open);

    vec_push(coauteurs, begin);

    vec *voisin_begin = begin->co_autors;
    size_t taille_voisin_begin = vec_used(voisin_begin);
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
    }
    // a finir
}