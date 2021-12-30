#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "protocol.h"

int compare_strings(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int compare_ints(const void *a, const void *b) {
    if (*(int *)a < *(int *)b) {
        return -1;
    } else if (*(int *)a > *(int *)b) {
        return 1;
    } else {
        return 0;
    }
}

int compare_floats(const void *a, const void *b) {
    if (*(float *)a < *(float *)b) {
        return -1;
    } else if (*(float *)a > *(float *)b) {
        return 1;
    } else {
        return 0;
    }
}

void print_usage(void) { printf("\n"); }
