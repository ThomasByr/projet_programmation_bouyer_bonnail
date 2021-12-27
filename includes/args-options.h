/*

*/

#ifndef ARGS_OPTIONS_H
#define ARGS_OPTIONS_H

struct options_s {
    int verbose;
    int debug;

    int find_connex_components; // find connex components in the graph
    int find_shortest_path;     // find shortest path between two authors
    int find_authors_words;     // find all authors that have a word in common
    int find_info_author;       // find information about an author
    int find_authors_within; // find all authors that are within a distance of a
                             // given author

    char *author;
    char *author1;
    char *author2;
    char *word;
};

typedef struct options_s options_t;

#endif
