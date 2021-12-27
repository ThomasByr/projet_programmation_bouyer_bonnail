/*

*/

#ifndef INFO_PARSER_H
#define INFO_PARSER_H

typedef struct parser_context_t {
    int text_count;
    int open_count;
    int close_count;
} parser_context_t;

typedef enum parser_error_type_t {
    PARSER_OK,
    ERROR_UNABLE_TO_ALLOCATE_MEMORY,
    ERROR_WHILE_READING_FILE,
    ERROR_UNABLE_TO_OPEN_FILE,
    ERROR_UNEXPECTED_END_OF_TAG,
} parser_error_type_t;

typedef struct parser_info_t {
    void (*handleOpenTag)(char *, void *);
    void (*handleCloseTag)(char *, void *);
    void (*handleText)(char *, void *);
    void *data;
} parser_info_t;

/**
 * @brief tell the parser to handle some text between tags
 *
 * @param txt some text
 * @param data the data to pass to the callback functions
 */
void handleText(char *txt, void *data);

/**
 * @brief tell the parser to open a tag
 *
 * @param tag tag name (without the <> brackets and any attributes)
 * @param data the data to pass to the callback functions
 */
void handleOpenTag(char *tag, void *data);

/**
 * @brief tell the parser to close a tag
 *
 * @param tag tag name (without the <> brackets and any attributes)
 * @param data the data to pass to the callback functions
 */
void handleCloseTag(char *tag, void *data);

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
