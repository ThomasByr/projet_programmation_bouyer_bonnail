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
    if (signal(SIGINT, handle_signal) == SIG_ERR) {
        alert("Cannot catch SIGINT");
        return EXIT_FAILURE;
    }
    if (signal(SIGSEGV, handle_signal) == SIG_ERR) {
        alert("Cannot catch SIGSEGV");
        return EXIT_FAILURE;
    }

    options_t *options = options_new();

    parse_args(argc, argv, options);
    check_args(options);

    int rv = exec(options);

    options_free(options);
    return rv;
}
