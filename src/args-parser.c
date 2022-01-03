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
        {"input_file", required_argument, 0, 'i'},
        {"path", required_argument, 0, 'p'},
        {"list", required_argument, 0, 'l'},
        {"author", required_argument, 0, 'a'},
        {"n_closest", required_argument, 0, 'n'},
        {"verbose", no_argument, 0, 'V'},
        {"debug", no_argument, 0, 'D'},
        {0, 0, 0, 0},
    };

    while (1) {
        c = getopt_long(argc, argv, "hvi:p:l:a:n:VD", long_options,
                        &option_index);
        if (c == -1)
            break;

        switch (c) {

        case 'h':
            print_usage();
            exit(EXIT_SUCCESS);
            break;

        case 'v':
            print_version();
            exit(EXIT_SUCCESS);
            break;

        case 'i':
            strncpy(options->input_file, optarg, FIELD_LEN);
            break;

        case 'p':
            if (options->find_shortest_path == 0) {
                options->find_shortest_path = 1;
                strncpy(options->author1, optarg, FIELD_LEN);
            } else if (options->find_authors_within == 1) {
                options->find_shortest_path = 2;
                strncpy(options->author2, optarg, FIELD_LEN);
            } else {
                fprintf(stderr,
                        "Error: --path can only and must be used twice\n");
                exit(EXIT_FAILURE);
            }
            break;

        case 'l':
            strncpy(options->word, optarg, FIELD_LEN);
            options->find_authors_words = 1;
            break;

        case 'a':
            strncpy(options->author, optarg, FIELD_LEN);
            options->find_info_author = 1;
            break;

        case 'n':
            options->n_closest = atoi(optarg);
            options->find_authors_within = 1;
            break;

        case 'V':
            options->verbose = 1;
            break;

        case 'D':
            options->debug = 1;
            break;

        case '?':
        default:
            fprintf(stderr, "Error: unknown option\n");
            exit(EXIT_FAILURE);
            break;
        }
    }

    if (optind < argc) {
        fprintf(stderr, "Invalid argument: %s\n", argv[optind]);
        print_usage();
        exit(EXIT_FAILURE);
    }
}
