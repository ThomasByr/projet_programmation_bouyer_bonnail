#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args-options.h"

options_t *options_new(void) {
    options_t *options = malloc(sizeof(options_t));
    options->verbose = 0;
    options->debug = 0;

    options->find_connex_components = 0;
    options->find_shortest_path = 0;
    options->find_authors_words = 0;
    options->find_info_author = 0;
    options->find_authors_within = 0;

    options->input_file = NULL;
    options->author = NULL;
    options->author1 = NULL;
    options->author2 = NULL;
    options->word = NULL;

    return options;
}

void options_free(options_t *options) { free(options); }
