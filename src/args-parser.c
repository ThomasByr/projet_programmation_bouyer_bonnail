#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "args-options.h"
#include "args-parser.h"
#include "protocol.h"

void parse_args(int argc, char *argv[], options_t *options) {
    int c;
    int option_index = 0;
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {"verbose", no_argument, 0, 'V'},
        {"debug", no_argument, 0, 'D'},
        {0, 0, 0, 0},
    };

    while (1) {
        c = getopt_long(argc, argv, "hvVD", long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
        case 'h':
            print_usage();
            exit(EXIT_SUCCESS);
        case 'v':
            print_version();
            exit(EXIT_SUCCESS);
            break;
        case 'V':
            options->verbose = 1;
            break;
        case 'D':
            options->debug = 1;
            break;

        default:
            print_usage();
            exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        fprintf(stderr, "Invalid argument: %s\n", argv[optind]);
        print_usage();
        exit(EXIT_FAILURE);
    }
}
