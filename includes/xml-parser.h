/*

*/

#ifndef XML_PARSER_H
#define XML_PARSER_H

#include "info-parser.h"

#define NTHREADS 8
#define XMLP_BUFFER_SIZE 1 << 12
#define XMLP_MAX_TAG_SIZE 1 << 6

#define reset(idx, b) \
    idx = 0;          \
    b[0] = '\0';
#define check(is1, is2)       \
    if (is1 == 1 || is2 == 1) \
        return ERROR_UNEXPECTED_END_OF_TAG;

struct pthread_arg {
    char *buffer;
    long size;
    parser_info_t *info;
};
typedef struct pthread_arg pthread_arg_t;

/**
 * @brief only keep the first characters of a string until any of `delims` is
 * reached
 *
 * @param tag tag with attributes and all...
 */
void get_tag_id(char *tag);

/**
 * @brief find the first occurence of any of `external` in `buffer`
 *
 * @param buffer buffer to parse
 * @param start starting position
 * @param size size of buffer
 * @return long - position of <
 */
long find_next_tag(char *buffer, long start, long size);

/**
 * @brief parse the buffer of size `size`
 *
 * @param buffer buffer to parse
 * @param size size of the buffer
 * @param info the info constaining the handler functions
 * @return parser_error_type_t
 */
parser_error_type_t parse_buffer(char *buffer, long size, parser_info_t *info);

/**
 * @brief open and parse the file pointed by `filename`
 *
 * @param filename the name of the file to parse
 * @param info the info containing the handler functions
 *
 * @return PARSER_OK if everything went fine, an error otherwise
 */
parser_error_type_t parse(const char *filename, parser_info_t *info);

#endif
