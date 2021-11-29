/*

*/

#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "info-parser.h"

#define EOL '\n'
#define XMLP_BUFFER_SIZE 1 << 12
#define reset(idx, b) \
    idx = 0;          \
    b[0] = '\0';
#define check(is1, is2)                                           \
    if (is1 == 1 || is2 == 1)                                     \
    {                                                             \
        fprintf(stderr, "Unexpected end of tag (missing '>')\n"); \
        return ERROR_UNEXPECTED_END_OF_TAG;                       \
    }

static const char open_tag = '<';         // opening tag
static const char close_tag = '>';        // closing tag
static const char end_tag = '/';          // ending tag
static const char delims[] = {' ', '\n'}; // delimiters

// list of tags to look for while parsing
static const char *look_for[] = {
    "article",
    "phdthesis",
    "title",
    "author",
    "date",
    "school",
    "year",
    "pages",
    "isbn",
};

/**
 * @brief only keep the first characters of a string until any of `delims` is reached
 * 
 * @param tag tag with attributes and all...
 */
void get_tag_id(char *tag);

/**
 * @brief open and parse the file pointed by `filename`
 * 
 * @param filename the name of the file to parse
 * @param info the info containing the handler functions
 * 
 * @return PARSER_OK if everything went fine, an error otherwise
 */
parser_error_t parse(const char *filename, parser_info_t *info);

#endif
