/* dijkstra.h
Dijkstra's algorithm for finding the shortest path between two nodes.

Assuming Dijkstra's algorithm was run on the graph, you can get the shortest
path between two nodes by using the `get_path` function.
By using a set and a priority queue, the algorithm runs in O(E + V log V) time
where E is the number of edges and V is the number of vertices.

*/

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "hset.h"
#include "node.h"
#include "pqueue.h"
#include "protocol.h"
#include "types.h"
#include "vec.h"

extern status_t _status;

/**
 * @brief dijkstra algorithm using only one search head
 *
 * @param start start node
 * @param end end node
 * @return int - distance or -1 if no path
 */
int dijkstra(node_t *start, node_t *end);

/**
 * @brief get the path from start to end assuming dijkstra was run
 *
 * @param end end node
 * @return vec_t* - path from start to end
 */
vec_t *get_path(node_t *end);

#endif
