#include <stdio.h>
#include <stdlib.h>

#include "dict-test.c"
#include "dijkstra-test.c"
#include "hset-test.c"
#include "pqueue-test.c"
#include "vec-test.c"
#include "xml-parser-test.c"

unsigned long _no_asserts = 0;

int main(void) {
    xml_parser_test();
    hset_test();
    dict_test();
    pqueue_test();
    vec_test();
    dijkstra_test();
}
