#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>
#include "vec.h"

typedef struct node_t
{
    char *name;
    vec *co_autors;
    unsigned long long weight;
    void *parent;
} node_t;

/*creer noeuds*/

node_t *create_node(char *name, vec *co_autors);

/* liberer noeuds*/

void delete_node(node_t *name);

#endif
