/*

*/

#ifndef MACROS_H
#define MACROS_H

#include <assert.h>

#define assert_eq(a, b) assert(a == b)

#define assert_neq(a, b) assert(a != b)

#define assert_lt(a, b) assert(a < b)

#define assert_gt(a, b) assert(a > b)

#define assert_leq(a, b) assert(a <= b)

#define assert_geq(a, b) assert(a >= b)

#define test_case(name)                                         \
    printf("\nrunning %s:%d: %s\n", __FILE__, __LINE__, #name); \
    name();                                                     \
    printf("\n");

#endif
