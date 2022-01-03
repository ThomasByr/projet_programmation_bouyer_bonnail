#include <stdio.h>
#include <stdlib.h>

#include "protocol.h"
#include "xml-parser.h"

<<<<<<< HEAD
int main(int argc, char *argv[])
{
=======
int main(int argc, char *argv[]) {
>>>>>>> 7c92f791ee13737df0c25425f9c58acd01c9783c
    (void)argc;
    (void)argv;

    parser_info_t *info = parser_info_new();

    print_version();

    char filename[] = "assets/dblp.xml";
    parser_error_type_t err = parse(filename, info);
<<<<<<< HEAD
    free(info);
=======
    parser_info_free(info);
>>>>>>> 7c92f791ee13737df0c25425f9c58acd01c9783c
    printf("%s\n", parser_error_type_to_string(err));
}
