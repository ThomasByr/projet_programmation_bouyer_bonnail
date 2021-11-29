/*

*/

#ifndef INFO_PARSER_H
#define INFO_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct parser_context_t
{
    int text_count;
    int open_count;
    int close_count;
} parser_context_t;

typedef enum parser_error_t
{
    PARSER_OK,
    ERROR_UNABLE_TO_OPEN_FILE,
    ERROR_UNEXPECTED_END_OF_TAG
} parser_error_t;

typedef struct parser_info_t
{
    void (*handleOpenTag)(char *, void *);
    void (*handleCloseTag)(char *, void *);
    void (*handleText)(char *, void *);
    void *data;
} parser_info_t;

void handleText(char *txt, void *data);
void handleOpenTag(char *tag, void *data);
void handleCloseTag(char *tag, void *data);

parser_info_t *parser_info_new(void);
void parser_info_free(parser_info_t *info);

#endif
