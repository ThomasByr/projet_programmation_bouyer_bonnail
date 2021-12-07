/*

*/

#ifndef MACROS_H
#define MACROS_H

#define assert_eq(a, b)                                                 \
    if (a != b)                                                         \
    {                                                                   \
        printf("failed %s:%d: %s != %s\n", __FILE__, __LINE__, #a, #b); \
        exit(1);                                                        \
    }                                                                   \
    else                                                                \
    {                                                                   \
        printf("ok %s:%d: %s == %s\n", __FILE__, __LINE__, #a, #b);     \
    }

#define assert_neq(a, b)                                                \
    if (a == b)                                                         \
    {                                                                   \
        printf("failed %s:%d: %s == %s\n", __FILE__, __LINE__, #a, #b); \
        exit(1);                                                        \
    }                                                                   \
    else                                                                \
    {                                                                   \
        printf("ok %s:%d: %s != %s\n", __FILE__, __LINE__, #a, #b);     \
    }

#define test_case(name)                                         \
    printf("\nrunning %s:%d: %s\n", __FILE__, __LINE__, #name); \
    name();                                                     \
    printf("\n");

#endif
