#include "node.h"

node_t *create_node(char *name, vec *co_autors)
{

    node_t *node = malloc(sizeof(node_t));
    node->name = name;
    node->co_autors = co_autors;
    node->weight = 0;
    node->parent = NULL;
    return node;
}

void delete_node(node_t *node)
{
    vec_delete_all(node->co_autors, free);
    free(node->co_autors);
    if (node->parent != NULL)
    {
        free(node->parent);
    }
}

void print_node(node_t *node)
{
    if (node != NULL)
    {
        printf("%s\n", node->name);
    }
    else
    {
        printf("erreur: pas de noeud\n");
    }
}