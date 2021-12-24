/* types.h
Generic types

*/

#ifndef TYPES_H
#define TYPES_H

typedef void *(for_each_callback_t)(void *, void *);
typedef void(delete_callback_t)(void *);

typedef int(compare_fn_t)(void *, void *);
typedef int(equals_fn_t)(void *, void *);

#endif
