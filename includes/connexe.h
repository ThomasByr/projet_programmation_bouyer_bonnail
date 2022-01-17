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
 * @param nodes autors of a connected component
 * 
 * @return return the diameter
 */
int diametre(hset_t *component);

/**
 * @brief connexe finds number of connected component and their diameter
 *
 * @param nodes all of the autors
 * 
 * @return return list of diameters
 */
vec_t *connexe(hset_t *nodes);

#endif