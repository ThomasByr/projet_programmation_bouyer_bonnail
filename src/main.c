#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "args-parser.h"
#include "io.h"
#include "protocol.h"
#include "xml-parser.h"

status_t _status = LAUNCH;

int main(int argc, char *argv[]) {
    _status = THREADING;
    signal(SIGINT, handle_signal);

    options_t *options = options_new();

    parse_args(argc, argv, options);
    check_args(options);

    int rv = exec(options);

    options_free(options);
    return rv;
}
