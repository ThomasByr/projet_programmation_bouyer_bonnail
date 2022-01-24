#include <stdio.h>
#include <stdlib.h>

#include "dict-test.c"
#include "dijkstra-test.c"
#include "hset-test.c"
#include "pqueue-test.c"
#include "vec-test.c"
#include "xml-parser-test.c"
// todo: do not include .c files

unsigned long _no_asserts = 0;
status_t _status = LAUNCH;

int main(void) {
    xml_parser_test(); // generic tests and parsing examples
    hset_test();       // hash set tests
    dict_test();       // dictionary tests
    pqueue_test();     // Fibonacci heap tests
    vec_test();        // vector tests
    dijkstra_test();   // Dijkstra's algorithm tests
}
