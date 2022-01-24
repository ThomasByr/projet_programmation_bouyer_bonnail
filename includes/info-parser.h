/* info-parser.h
XML parser context and info retrieval.

*/

#ifndef INFO_PARSER_H
#define INFO_PARSER_H

#include "dict.h"
#include "hset.h"
#include "node.h"

extern status_t _status;

struct parser_context_s {
    int text_count;  // number of fields
    int open_count;  // number of open tags
    int close_count; // number of close tags
    int flag;        // flag for the client

    char *paper_type;  // paper type (external)
    char *paper_title; // last paper title
    char *author;      // main author of the paper
    char *inner_tag;   // inner tag (look_for)

    node_t *current_node; // current node

    dict_t *auth_co_auth; // author -> set of co-author names
    dict_t *auth_papers;  // author name -> paper titles
    dict_t *auth_node;    // author name -> node object
    hset_t *auth_set;     // set of author names
    hset_t *nodes;        // set of node objects

    FILE *out; // binary output file
};
typedef struct parser_context_s parser_context_t;

enum parser_error_type_e {
    PARSER_OK,
    ERROR_UNABLE_TO_ALLOCATE_MEMORY,
    ERROR_WHILE_READING_FILE,
    ERROR_UNABLE_TO_OPEN_FILE,
    ERROR_UNEXPECTED_END_OF_TAG,
};
typedef enum parser_error_type_e parser_error_type_t;

struct parser_info_s {
    int (*hndl_otg)(char *, struct parser_context_s *);
    int (*hndl_ctg)(char *, struct parser_context_s *);
    int (*hndl_txt)(char *, struct parser_context_s *);
    struct parser_context_s *context;
};
typedef struct parser_info_s parser_info_t;

/**
 * @brief tell the parser to handle some text between tags
 *
 * @param txt some text
 * @param context the context to pass to the callback functions
 * @return int - 0 if everything went well, -1 otherwise
 */
int hndl_txt(char *txt, struct parser_context_s *context);

/**
 * @brief tell the parser to open a tag
 *
 * @param tag tag name (without the <> brackets and any attributes)
 * @param context the context to pass to the callback functions
 * @return int - 0 if everything went well, -1 otherwise
 */
int hndl_otg(char *tag, struct parser_context_s *context);

/**
 * @brief tell the parser to close a tag
 *
 * @param tag tag name (without the <> brackets and any attributes)
 * @param context the context to pass to the callback functions
 * @return int - 0 if everything went well, -1 otherwise
 */
int hndl_ctg(char *tag, struct parser_context_s *context);

/**
 * @brief new parser context structure
 *
 * @param flag flag for the client
 * @return parser_context_t*
 */
parser_context_t *parser_context_new(int flag);

/**
 * @brief free a parser context underlaying structure
 *
 * @param context parser context to free
 */
void parser_context_free(parser_context_t *context);

/**
 * @brief new parser info structure
 *
 * @param flag flag for the client
 * @return parser_info_t*
 */
parser_info_t *parser_info_new(int flag);

/**
 * @brief free a parser info underlaying structure
 *
 * @param info parser info to free
 */
void parser_info_free(parser_info_t *info);

/**
 * @brief transform an error thrown by the parser into a string
 *
 * @param error error code
 * @return char*
 */
char *parser_error_type_to_string(parser_error_type_t error);

#endif
