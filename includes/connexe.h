#ifndef CONNEXE_H
#define CONNEXE_H

#include "hset.h"
#include "node.h"
#include "pqueue.h"
#include "protocol.h"
#include "types.h"
#include "vec.h"

/**
 * @brief connexe finds number of connected component and their diameter
 *
 * @param nodes all of the autors
 * 
 * @return return number of connected component and their diameters
 */
int connexe(hset_t *nodes);

#endif