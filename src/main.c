#include <stdio.h>
#include <stdlib.h>

#include "xml-parser.h"
#include "vec.h"

int main(void)
{
    parser_info_t *info = parser_info_new();

    char filename[] = "assets/dblp.xml";
    parser_error_type_t err = parse(filename, info);
    free(info);
    printf("%d\n", err);
}
