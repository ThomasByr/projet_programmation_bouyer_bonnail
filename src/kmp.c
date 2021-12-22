#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kmp.h"

void preMp(char *x, int m, int mpNext[]) {
    int i, j;

    i = 0;
    j = mpNext[0] = -1;
    while (i < m) {
        while (j > -1 && x[i] != x[j])
            j = mpNext[j];
        mpNext[++i] = ++j;
    }
}

void preKmp(char *x, int m, int kmpNext[]) {
    int i, j;

    i = 0;
    j = kmpNext[0] = -1;
    while (i < m) {
        while (j > -1 && x[i] != x[j])
            j = kmpNext[j];
        i++;
        j++;
        if (x[i] == x[j])
            kmpNext[i] = kmpNext[j];
        else
            kmpNext[i] = j;
    }
}

int attempt(char *y, char *x, int m, int start, int wall) {
    int k;

    k = wall - start;
    while (k < m && x[k] == y[k + start])
        ++k;
    return (k);
}

int KMPSKIP(char *x, int m, char *y, int n) {
    int i, j, k, kmpStart, per, start, wall;
    int kmpNext[XSIZE], list[XSIZE], mpNext[XSIZE], z[ASIZE];

    /* Preprocessing */
    preMp(x, m, mpNext);
    preKmp(x, m, kmpNext);
    memset(z, -1, ASIZE * sizeof(int));
    memset(list, -1, m * sizeof(int));
    z[(short)x[0]] = 0;
    for (i = 1; i < m; ++i) {
        list[i] = z[(short)x[i]];
        z[(short)x[i]] = i;
    }

    wall = 0;
    per = m - kmpNext[m];
    i = j = -1;
    do {
        j += m;
    } while (j < n && z[(short)y[j]] < 0);
    if (j >= n)
        return -1;
    i = z[(short)y[j]];
    start = j - i;
    while (start <= n - m) {
        if (start > wall)
            wall = start;
        k = attempt(y, x, m, start, wall);
        wall = start + k;
        if (k == m) {
            OUTPUT(start);
            i -= per;
        } else
            i = list[i];
        if (i < 0) {
            do {
                j += m;
            } while (j < n && z[(short)y[j]] < 0);
            if (j >= n)
                return -1;
            i = z[(short)y[j]];
        }
        kmpStart = start + k - kmpNext[k];
        k = kmpNext[k];
        start = j - i;
        while (start < kmpStart || (kmpStart < start && start < wall)) {
            if (start < kmpStart) {
                i = list[i];
                if (i < 0) {
                    do {
                        j += m;
                    } while (j < n && z[(short)y[j]] < 0);
                    if (j >= n)
                        return -1;
                    i = z[(short)y[j]];
                }
                start = j - i;
            } else {
                kmpStart += (k - mpNext[k]);
                k = mpNext[k];
            }
        }
    }
    return -1;
}
