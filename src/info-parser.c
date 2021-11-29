#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "info-parser.h"

void handleText(char *txt, void *data)
{
    // parser_context_t *context = data;
    // context->text_count++;
    // printf("TEXT %s\n", txt);
    return;
}

void handleOpenTag(char *tag, void *data)
{
    // parser_context_t *context = data;
    // context->open_count++;
    // printf("OPEN TAG %s\n", tag);
    return;
}

void handleCloseTag(char *tag, void *data)
{
    // parser_context_t *context = data;
    // context->close_count++;
    // printf("CLOSE TAG %s\n", tag);
    return;
}

parser_info_t *parser_info_new(void)
{
    parser_info_t *info = malloc(sizeof(parser_info_t));
    parser_context_t *context = malloc(sizeof(parser_context_t));

    context->text_count = 0;
    context->open_count = 0;
    context->close_count = 0;

    if (info == NULL)
        return NULL;
    if (context == NULL)
    {
        free(info);
        return NULL;
    }

    info->data = context;
    info->handleOpenTag = handleOpenTag;
    info->handleCloseTag = handleCloseTag;
    info->handleText = handleText;

    return info;
}

void parser_info_free(parser_info_t *info)
{
    if (info == NULL)
        return;
    free(info->data);
    free(info);
}
