#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hset.h"

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

hset_t *hset_create(size_t capacity, char *(*to_string)(void *))
{
    hset_t *hset = malloc(sizeof(hset_t));
    hset->capacity = capacity;

    void ***buckets = malloc(sizeof(void *) * capacity); // `capacity` buckets
    for (size_t i = 0; i < capacity; i++)                // initialize all buckets to NULL
        buckets[i] = malloc(sizeof(void *));             // each bucket is an array of pointers
    memset(buckets, 0, sizeof(void *) * capacity);
    hset->buckets = buckets;

    int *sizes = malloc(sizeof(int) * capacity);
    for (size_t i = 0; i < capacity; i++)
        sizes[i] = 1;
    hset->sizes = sizes;

    int *counts = malloc(sizeof(int) * capacity);
    for (size_t i = 0; i < capacity; i++)
        counts[i] = 0;
    hset->counts = counts;

    hset->to_string = to_string;

    return hset;
}

void hset_destroy(hset_t *hset)
{
    for (size_t i = 0; i < hset->capacity; i++)
        free(hset->buckets[i]);
    free(hset->buckets);
    free(hset->counts);
    free(hset->sizes);
    free(hset);
}

void hset_insert(hset_t *hset, void *data)
{
    char *str = hset->to_string(data);
    unsigned long hash_value = hash(str);

    int index = hash_value % hset->capacity;
    int size = hset->sizes[index];
    int count = hset->counts[index];

    if (count == size)
    {
        hset->sizes[index] *= 2;
        hset->buckets[index] = realloc(hset->buckets[index], sizeof(void *) * hset->sizes[index]);
    }

    for (int i = 0; i < count; i++)
    {
        if (strcmp(str, hset->buckets[index][i]) == 0)
        {
            free(str); // ?is this necessary?
            return;
        }
    }
    hset->buckets[index][count] = data;
    hset->counts[index]++;
}

int hset_contains(hset_t *hset, void *data)
{
    char *str = hset->to_string(data);
    unsigned long hash_value = hash(str);

    int index = hash_value % hset->capacity;
    int count = hset->counts[index];

    for (int i = 0; i < count; i++)
    {
        if (strcmp(str, hset->buckets[index][i]) == 0)
        {
            free(str);
            return 1;
        }
    }
    free(str);
    return 0;
}

void hset_discard(hset_t *hset, void *data)
{
    char *str = hset->to_string(data);
    unsigned long hash_value = hash(str);

    int index = hash_value % hset->capacity;
    int count = hset->counts[index];

    for (int i = 0; i < count; i++)
    {
        if (strcmp(str, hset->buckets[index][i]) == 0)
        {
            free(str);
            for (int j = i; j < count - 1; j++)
                hset->buckets[index][j] = hset->buckets[index][j + 1];
            hset->counts[index]--;
            return;
        }
    }
    free(str);
}
