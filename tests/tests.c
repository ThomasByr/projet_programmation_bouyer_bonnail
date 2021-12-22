#include <stdio.h>
#include <stdlib.h>

#include "hset-test.c"
#include "macros.h"
#include "xml-parser-test.c"

int main(void) {
    xml_parser_test();
    hset_test();
}
