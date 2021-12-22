/* macro.h
A simple assertion macro.

*   `assert` macro is used to check the truth evaluation of an expression.
If the expression evaluates to false, the program will be terminated with an
error
*   `assert_eq` macro is used to check the equality of two values.
This macro, unlike `assert`, tries to cast the values to the same type before
evaluation. The type of the first argument is arbitrarily chosen.
*/

#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <stdlib.h>

#define assert(expr)                                          \
    do {                                                      \
        if (!(expr)) {                                        \
            fprintf(stderr, "\033[0;31m");                    \
            fprintf(stderr, "Assertion failed: %s\n", #expr); \
            abort();                                          \
        }                                                     \
    } while (0);

#define assert_eq(a, b)         \
    do {                        \
        __typeof__(a) _a = (a); \
        __typeof__(a) _b = (b); \
        assert(_a == _b);       \
    } while (0);
#define assert_neq(a, b)        \
    do {                        \
        __typeof__(a) _a = (a); \
        __typeof__(a) _b = (b); \
        assert(_a != _b);       \
    } while (0);
#define assert_lt(a, b)         \
    do {                        \
        __typeof__(a) _a = (a); \
        __typeof__(a) _b = (b); \
        assert(_a < _b);        \
    } while (0);
#define assert_gt(a, b)         \
    do {                        \
        __typeof__(a) _a = (a); \
        __typeof__(a) _b = (b); \
        assert(_a > _b);        \
    } while (0);
#define assert_leq(a, b)        \
    do {                        \
        __typeof__(a) _a = (a); \
        __typeof__(a) _b = (b); \
        assert(_a <= _b);       \
    } while (0);
#define assert_geq(a, b)        \
    do {                        \
        __typeof__(a) _a = (a); \
        __typeof__(a) _b = (b); \
        assert(_a >= _b);       \
    } while (0);

#define test_case(name)                                         \
    do {                                                        \
        printf("\033[0m");                                      \
        printf("running %s:%d: %s", __FILE__, __LINE__, #name); \
        name();                                                 \
        printf("\033[0;32m");                                   \
        printf(" ok\n");                                        \
        printf("\033[0m");                                      \
    } while (0)

#endif
