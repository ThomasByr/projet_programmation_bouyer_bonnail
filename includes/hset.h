/*

*/

#ifndef HSET_H
#define HSET_H

typedef struct hset_s
{
};

/**
 * @brief djb2 hash function by Dan Bernstein
 * 
 * @param str string to hash
 * @return unsigned long 
 */
unsigned long hash(unsigned char *str);

#endif
