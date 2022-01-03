/*

*/

#ifndef ARGS_OPTIONS_H
#define ARGS_OPTIONS_H

#define FIELD_LEN 1 << 11

struct options_s {
    int verbose;
    int debug;

    int find_connex_components; // find connex components in the graph
    int find_shortest_path;     // find shortest path between two authors
    int find_authors_words;     // find all authors that have a word in common
    int find_info_author;       // find information about an author
    int find_authors_within; // find all authors that are within a distance of a
                             // given author

    int n_closest; // max distance between two authors to find

    char input_file[FIELD_LEN];
    char author[FIELD_LEN];
    char author1[FIELD_LEN];
    char author2[FIELD_LEN];
    char word[FIELD_LEN];
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
