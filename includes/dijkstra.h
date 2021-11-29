#ifndef DIJKSTRA
#define DIJKSTRA
#include <stdio.h>
#include <stdlib.h>
#include "vec.h"
#include "node.h"
int find_min_weight(vec *v);

int dijkstra(node_t *begin, node_t *end);

#endif