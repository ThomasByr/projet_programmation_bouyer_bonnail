/* info-parser.h
XML parser context and info retrieval.

*/

#ifndef INFO_PARSER_H
#define INFO_PARSER_H

struct parser_context_s {
    int text_count;
    int open_count;
    int close_count;

    char *paper_type;
    char *inner_tag;
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
    void (*handleOpenTag)(char *, struct parser_context_s *);
    void (*handleCloseTag)(char *, struct parser_context_s *);
    void (*handleText)(char *, struct parser_context_s *);
    struct parser_context_s *context;
};
typedef struct parser_info_s parser_info_t;

/**
 * @brief tell the parser to handle some text between tags
 *
 * @param txt some text
 * @param context the context to pass to the callback functions
 */
void handleText(char *txt, struct parser_context_s *context);

/**
 * @brief tell the parser to open a tag
 *
 * @param tag tag name (without the <> brackets and any attributes)
 * @param context the context to pass to the callback functions
 */
void handleOpenTag(char *tag, struct parser_context_s *context);

/**
 * @brief tell the parser to close a tag
 *
 * @param tag tag name (without the <> brackets and any attributes)
 * @param context the context to pass to the callback functions
 */
void handleCloseTag(char *tag, struct parser_context_s *context);

/**
 * @brief new parser context structure
 *
 * @return parser_context_t*
 */
parser_context_t *parser_context_new(void);

/**
 * @brief free a parser context underlaying structure
 *
 * @param context parser context to free
 */
void parser_context_free(parser_context_t *context);

/**
 * @brief new parser info structure
 *
 * @return parser_info_t*
 */
parser_info_t *parser_info_new(void);

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
