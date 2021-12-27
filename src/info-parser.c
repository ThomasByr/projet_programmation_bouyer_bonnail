#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "info-parser.h"

void handleText(char *txt, void *data) {
    (void)txt;
    (void)data;
    return;
}

void handleOpenTag(char *tag, void *data) {
    (void)tag;
    (void)data;
    return;
}

void handleCloseTag(char *tag, void *data) {
    (void)tag;
    (void)data;
    return;
}

parser_info_t *parser_info_new(void) {
    parser_info_t *info = malloc(sizeof(parser_info_t));
    parser_context_t *context = malloc(sizeof(parser_context_t));

    context->text_count = 0;
    context->open_count = 0;
    context->close_count = 0;

    if (info == NULL)
        return NULL;
    if (context == NULL) {
        free(info);
        return NULL;
    }

    info->data = context;
    info->handleOpenTag = handleOpenTag;
    info->handleCloseTag = handleCloseTag;
    info->handleText = handleText;

    return info;
}

void parser_info_free(parser_info_t *info) {
    if (info == NULL)
        return;
    free(info->data);
    free(info);
}

char *parser_error_type_to_string(parser_error_type_t error) {
    switch (error) {
    case ERROR_UNABLE_TO_ALLOCATE_MEMORY:
        return "Unable to allocate memory to hold the file (possibly not "
               "enough memory)";
    case ERROR_WHILE_READING_FILE:
        return "Error while reading the file into memory (possibly pointer out "
               "of memory)";
    case ERROR_UNABLE_TO_OPEN_FILE:
        return "Unable to open the file (possibly wrong path)";
    case ERROR_UNEXPECTED_END_OF_TAG:
        return "Unexpected end of tag (possibly a < was not matched with a >)";

    default:
    case PARSER_OK:
        return "Parsing was successful (possibly luck)";
    }
}
