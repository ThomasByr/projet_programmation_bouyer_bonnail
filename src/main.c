#include <stdio.h>
#include <stdlib.h>

#include "args-parser.h"
#include "protocol.h"
#include "xml-parser.h"

int main(int argc, char *argv[]) {
    options_t *options = options_new();
    parse_args(argc, argv, options);
    options_free(options);
}
