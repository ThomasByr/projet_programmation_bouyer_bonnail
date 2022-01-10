#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "year.h"

void year(hset_t *nodes, int year1, int year2)
{
    if (year2 < year1)
    {
        int a = year1;
        year1 = year2;
        year2 = a;
    }

    dict_itr_t *itr = dict_itr_new(nodes);
    while (dict_itr_has_next(itr))
    {
        node_t *node = (node_t *)dict_itr_value(itr);
        dict_itr_t *itr_year = node->papers;
        while (dict_itr_has_next(itr_year))
        {
            int *publi_year = (int *)dict_itr_value(itr_year);
            if (year1 <= *publi_year && year2 >= *publi_year)
            {
                char *title = (char *)dict_itr_key(itr_year);
                printf("%s\n", title);
            }
            dict_itr_next(itr_year);
        }
        dict_itr_next(itr);
    }
    return;
}