/*

*/

#ifndef PQUEUE_H
#define PQUEUE_H

typedef struct pqueue_node
{
    void *data;                      // pointer to data
    int *(*compare)(void *, void *); // pointer to compare function
} pqueue_node;

#endif
