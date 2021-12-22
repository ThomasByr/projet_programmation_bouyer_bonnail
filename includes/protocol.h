/* protocol.h

*   `foreach(item in array)` macro only works for static allocated arrays.
This is used to iterate over an unidimensional array. Note that `char arr[] =
...;` will be iterated over properly but `char *arr = ...;` will not.
*   `lerp` macro is used to "move" a value from one range to another.
Given values are casted to the same type before evaluation.

*/

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdio.h>
#include <stdlib.h>

#define FOREACH(type, item, array, size)                                   \
    for (size_t X(keep) = 1, X(i) = 0; X(i) < (size); X(keep) = 1, X(i)++) \
        for (type item = (array)[X(i)]; X(keep); X(keep) = 0)

#define _foreach(item, array) \
    FOREACH(__typeof__(array[0]), item, array, length(array))
#define foreach(item_in_array) _foreach(item_in_array)

#define in ,
#define length(array) (sizeof(array) / sizeof((array)[0]))
#define CAT(a, b) CAT_HELPER(a, b)
#define CAT_HELPER(a, b) a##b
#define X(name) CAT(__##name, __LINE__)

#define lerp(x, x0, x1, y0, y1)   \
    do {                          \
        __typeof__(x) _x = (x);   \
        __typeof__(x) _x0 = (x0); \
        __typeof__(x) _x1 = (x1); \
        __typeof__(x) _y0 = (y0); \
        __typeof__(x) _y1 = (y1); \
    } while (0);                  \
    (((_y0) * ((_x1) - (x)) + (_y1) * ((x) - (_x0))) / ((_x1) - (_x0)))

#endif
