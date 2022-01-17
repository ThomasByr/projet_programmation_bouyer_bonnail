#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word.h"

void word(char *word, hset_t *nodes)
{
    dict_itr_t *itr = dict_itr_new(nodes);
    while (dict_itr_has_next(itr))
    {
        node_t *node = (node_t *)dict_itr_key(itr);
        dict_itr_t *itr_papers = node->papers;
        while (dict_itr_has_next(itr_papers))
        {
            char *title = (char *)dict_itr_key(itr_papers);
            if (strstr(title, word) != NULL)
            {

                printf("%s\n", node->name);
            }
            dict_itr_next(itr_papers);
        }
        dict_itr_next(itr);
    }
    return;
}