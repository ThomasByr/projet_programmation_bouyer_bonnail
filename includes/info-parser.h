/*

*/

#ifndef INFO_PARSER_H
#define INFO_PARSER_H

struct parser_context_s
{
    int text_count;
    int open_count;
    int close_count;
};
typedef struct parser_context_s parser_context_t;

enum parser_error_type_e
{
    PARSER_OK,
    ERROR_UNABLE_TO_ALLOCATE_MEMORY,
    ERROR_WHILE_READING_FILE,
    ERROR_UNABLE_TO_OPEN_FILE,
    ERROR_UNEXPECTED_END_OF_TAG,
};
typedef enum parser_error_type_e parser_error_type_t;

struct parser_info_s
{
    void (*handleOpenTag)(char *, void *);
    void (*handleCloseTag)(char *, void *);
    void (*handleText)(char *, void *);
    void *data;
};
typedef struct parser_info_s parser_info_t;

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
<<<<<<< HEAD
 * 
=======
 *
 */

/**
 * @brief new parser info structure
<<<<<<< HEAD
 * 
 * @return parser_info_t* 
=======
 *
 * @return parser_info_t*
>>>>>>> 7c92f791ee13737df0c25425f9c58acd01c9783c
 */
parser_info_t *parser_info_new(void);

/**
 * @brief free a parser info underlaying structure
<<<<<<< HEAD
 * 
=======
 *
>>>>>>> 7c92f791ee13737df0c25425f9c58acd01c9783c
 * @param info parser info to free
 */
void parser_info_free(parser_info_t *info);

/**
 * @brief transform an error thrown by the parser into a string
<<<<<<< HEAD
 * 
 * @param error error code
 * @return char* 
=======
 *
 * @param error error code
 * @return char*
>>>>>>> 7c92f791ee13737df0c25425f9c58acd01c9783c
 */
char *parser_error_type_to_string(parser_error_type_t error);

#endif
