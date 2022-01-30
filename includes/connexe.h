#ifndef CONNEXE_H
#define CONNEXE_H

#include "hset.h"
#include "node.h"
#include "pqueue.h"
#include "protocol.h"
#include "types.h"
#include "vec.h"
/**
 * @brief diametre finds diameter of connected component
 *
 * @param component authors of a connected component
 *
 * @return return the diameter
 */
int diametre(hset_t *component);

/**
 * @brief connexe finds number of connected component and their diameter
 *
 * @param nodes all authors
 *
 * @return return list of diameters that you would want to free
 */
vec_t *connexe(hset_t *nodes);

#endif
