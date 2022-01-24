#ifndef WORD_H
#define WORD_H

#include "hset.h"
#include "node.h"
#include "pqueue.h"
#include "protocol.h"
#include "types.h"
#include "vec.h"

/**
 * @brief word lists autors where word is in the title of an article
 *
 * @param word word searched
 *
 * @return print authors
 */
void word(char *word, hset_t *nodes);

#endif
