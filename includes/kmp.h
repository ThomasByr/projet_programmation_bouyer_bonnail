/**
 * KMP Skip Search algorithm
 * from StackOverflow
 * https://stackoverflow.com/questions/2530751/how-can-i-partial-compare-two-strings-in-c
 */

#ifndef KMP_H
#define KMP_H

#define XSIZE 1 << 16
#define ASIZE 1 << 8
#define OUTPUT(v) printf("%d ", v);

void preMp(char *x, int m, int mpNext[]);

void preKmp(char *x, int m, int kmpNext[]);

int attempt(char *y, char *x, int m, int start, int wall);

int KMPSKIP(char *x, int m, char *y, int n);

#endif
