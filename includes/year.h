#ifndef YEAR_H
#define YEAR_H

#include "hset.h"
#include "node.h"
#include "pqueue.h"
#include "protocol.h"
#include "types.h"
#include "vec.h"

/**
 * @brief year lists articles released between two years
 *
 * @param year1 first year
 * @param year2 second year
 * 
 * @return print articles
 */
void year(hset_t *nodes, int year1, int year2);

#endif