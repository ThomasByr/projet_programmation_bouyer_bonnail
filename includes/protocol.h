/* protocol.h
Some general-purpose macros and functions.

*   `foreach(item in array)` macro only works for static allocated arrays.
This is used to iterate over an unidimensional array. Note that `char arr[] =
...;` will be iterated over properly but `char *arr = ...;` will not.
*   `lerp` macro is used to "move" a value from one range to another.
It is the caller's responsability to cast the values to the same type.

*/

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define lerp(x, x0, x1, y0, y1) \
    (((y0) * ((x1) - (x)) + (y1) * ((x) - (x0))) / ((x1) - (x0)))

/**
 * @brief duplicate a string.
 * Since -std=c18, `strdup` is not available because it is not part of the
 * standard C library.
 *
 * @return char* - pointer to the duplicated string
 */
extern char *strdup(const char *);

#endif
