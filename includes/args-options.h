/* args-options.h
Options for the command line arguments.

*/

#ifndef ARGS_OPTIONS_H
#define ARGS_OPTIONS_H

struct options_s {
    int verbose;
    int quiet;

    int find_connex_components; // find connex components in the graph
    int find_shortest_path;     // find shortest path between two authors
    int find_authors_words;     // find all authors that have a word in common
    int find_info_author;       // find information about an author
    int find_authors_within; // find all authors that are within a distance of a
                             // given author

    int need_graph; // need to make the graph
    int n_closest;  // max distance between two authors to find

    char *input_file;
    char *author;
    char *author1;
    char *author2;
    char *word;
};

typedef struct options_s options_t;

/**
 * @brief return a new option with blank values
 *
 * @return options_t*
 */
options_t *options_new(void);

/**
 * @brief free the memory allocated for the options
 *
 * @param options
 */
void options_free(options_t *options);

#endif
