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
        {"quiet", no_argument, 0, 'q'},
        {"input_file", required_argument, 0, 'i'},
        {"path", required_argument, 0, 'p'},
        {"list", required_argument, 0, 'l'},
        {"author", required_argument, 0, 'a'},
        {"n_closest", required_argument, 0, 'n'},
        {"verbose", no_argument, 0, 'V'},
        {0, 0, 0, 0},
    };

    while (1) {
        c = getopt_long(argc, argv, "hvqi:p:l:a:n:V", long_options,
                        &option_index);
        if (c == -1)
            break;

        switch (c) {

        case 'h':
            print_usage();
            options_free(options);
            exit(EXIT_SUCCESS);

        case 'v':
            print_version();
            options_free(options);
            exit(EXIT_SUCCESS);

        case 'q':
            options->quiet = 1;
            break;

        case 'i':
            options->input_file = optarg;
            break;

        case 'p':
            if (options->find_shortest_path == 0) {
                options->find_shortest_path = 1;
                options->author1 = optarg;
            } else if (options->find_authors_within == 1) {
                options->find_shortest_path = 2;
                options->author2 = optarg;
            } else {
                alert("Error: --path can only and must be used twice\n");
                options_free(options);
                exit(EXIT_FAILURE);
            }
            break;

        case 'l':
            options->word = optarg;
            options->find_authors_words = 1;
            break;

        case 'a':
            options->author = optarg;
            options->find_info_author = 1;
            break;

        case 'n':
            options->n_closest = atoi(optarg);
            options->find_authors_within = 1;
            break;

        case 'V':
            options->verbose = 1;
            break;

        case '?':
        default:
            alert("Error: unknown option\n");
            options_free(options);
            exit(EXIT_FAILURE);
            break;
        }
    }

    if (optind < argc) {
        alert("Invalid argument: %s\n", argv[optind]);
        print_usage();
        options_free(options);
        exit(EXIT_FAILURE);
    }
}

void check_args(options_t *options) {
    int has_error = 0;

    // if --author is used but not set
    if (options->find_info_author == 1 && options->author == NULL) {
        alert("Error: --author requires an argument\n");
        has_error = 1;
    }
    // if --list is used but not set
    if (options->find_authors_words == 1 && options->word == NULL) {
        alert("Error: --list requires an argument\n");
        has_error = 1;
    }
    // if --n_closest is used but not set
    if (options->find_authors_within == 1 && options->n_closest == 0) {
        alert("Error: --n_closest requires an non trivial argument\n");
        has_error = 1;
    }
    // if --path is used but not set
    if (options->find_shortest_path != 0 &&
        (options->author1 == NULL || options->author2 == NULL)) {
        alert("Error: --path requires an argument\n");
        has_error = 1;
    }
    // if --path is used but not exactly twice
    if (options->find_shortest_path != 0 && options->find_shortest_path != 2) {
        alert("Error: --path should and must be used twice\n");
        has_error = 1;
    }

    // if --n_closest is used but not author is specified
    if (options->find_authors_within == 1 && options->author == NULL) {
        alert("Error: --n_closest requires an author\n");
        has_error = 1;
    }

    // if --input_file not set
    if (options->input_file == NULL) {
        alert("Error: --input_file must be set\n");
        has_error = 1;
    }

    // if both verbose and quiet flags are used
    if (options->verbose == 1 && options->quiet == 1) {
        alert("Error: --quiet and --verbose cannot be used together\n");
        has_error = 1;
    }

    if (has_error) {
        print_usage();
        options_free(options);
        exit(EXIT_FAILURE);
    } // go on if no error, exec should be called
}
