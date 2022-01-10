#ifndef INFO_H
#define INFO_H

#include "hset.h"
#include "node.h"
#include "pqueue.h"
#include "protocol.h"
#include "types.h"
#include "vec.h"

/**
 * @brief info lists articles of an autor
 *
 * @param autor autor name
 * 
 * @return print articles
 */
void info(node_t *autor);

#endif
