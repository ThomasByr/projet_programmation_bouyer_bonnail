/* types.h
Generic types

*/

#ifndef TYPES_H
#define TYPES_H

typedef void *(for_each_callback_t)(void *, void *);
typedef void(delete_callback_t)(void *);
typedef void(print_callback_t)(void *);

/**
 * @brief Generic compare function type.
 * Should return 0 if both elements evaluate to the same value,
 * 1 or more if the second evaluates as greater,
 * -1 or less if the first one evaluates as greater.
 *
 */
typedef int(compare_fn_t)(const void *, const void *);

/**
 * @brief Generic equal function type.
 * Should return 0 if both elements evaluate to a different value,
 * and non-zero if both elements evaluate as equal.
 *
 */
typedef int(equals_fn_t)(const void *, const void *);

#endif
