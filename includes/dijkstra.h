/*

*/

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>

#include "hset.h"
#include "node.h"
#include "pqueue.h"
#include "types.h"
#include "vec.h"

/**
 * @brief dijkstra algorithm using only one search head
 *
 * @param start start node
 * @param end end node
 * @return vec* - path from end to start
 */
vec *dijkstra(node_t *start, node_t *end);

#endif
