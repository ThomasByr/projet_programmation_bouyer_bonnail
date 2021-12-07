#include "dijkstra.h"
#include "vec.h"
#include "plus_court_chemin.h"

char *plus_court_chemin(node_t *begin, node_t *end)
{
    size_t capacite = 50;
    size_t n_char = 0;
    char *auteurs = malloc(capacite * sizeof(char));
    int taille = dijkstra(begin, end);
    node_t *noeud = end;
    for (int i = 0; i < taille; i++)
    {
        char *nom_noeud = noeud->name;
        int size_name = sizeof(nom_noeud);
        while (capacite - n_char < size_name)
        {
            auteurs = (int *)realloc(auteurs, 2 * capacite * sizeof(int));
            capacite = 2 * capacite;
        }
        auteurs[n_char] = nom_noeud;
        n_char = n_char + size_name;
    }
    return auteurs;
}