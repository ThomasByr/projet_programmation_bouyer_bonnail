#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xml-parser.h"
#include "macros.h"

void test_error_0(void)
{
    parser_info_t *info = parser_info_new();

    char filename[] = "../assets/dblp.xml";
    parser_error_type_t err = parse(filename, info);
    free(info);
    printf("%d\n", err);
}

void xml_parser_test()
{
    test_case(test_error_0);
}
