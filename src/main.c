#include <stdio.h>
#include <stdlib.h>

#include "xml-parser.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    parser_info_t *info = parser_info_new();

    char filename[] = "assets/dblp.xml";
    parser_error_type_t err = parse(filename, info);
    parser_info_free(info);
    printf("%s\n", parser_error_type_to_string(err));
}
