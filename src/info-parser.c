#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "info-parser.h"

const char *external[] = {
    "article",      "inproceedings", "proceedings",   "book",
    "incollection", "phdthesis",     "mastersthesis", "www",
};

const char *look_for[] = {
    "title", "author", "year", "pages", "url",
};

int contains(const char **str, const char *s) {
    foreach (item of str) {
        if (strcmp(item, s) == 0) {
            return 1;
        }
    }
    return 0;
}

int hndl_txt(char *txt, parser_context_t *context) {
    (void)txt;
    (void)context;
    return 0;
}

int hndl_otg(char *tag, parser_context_t *context) {
    int is_external = contains(external, tag);
    int is_look_for = contains(look_for, tag);

    if (is_external == 0 && is_look_for == 0) {
        return 0;
    } // skip unwanted tags

    if (is_external) {
    }
    if (is_look_for) {
    }

    (void)tag;
    (void)context;

    return 0;
}

int hndl_ctg(char *tag, parser_context_t *context) {

    int is_external = contains(external, tag);
    if (is_external == 0)
        return 0;
    (void)tag;
    (void)context;
    return 0;
}

parser_context_t *parser_context_new(int flag) {
    parser_context_t *ctx = malloc(sizeof(parser_context_t));
    ctx->text_count = 0;
    ctx->open_count = 0;
    ctx->close_count = 0;
    ctx->flag = flag;

    ctx->paper_type = NULL;
    ctx->paper_title = NULL;
    ctx->author = NULL;
    ctx->inner_tag = NULL;

    ctx->current_node = NULL;

    ctx->auth_co_auth = dict_new();
    ctx->auth_papers = dict_new();
    ctx->auth_node = dict_new();
    ctx->nodes = hset_new();
    return ctx;
}

void parser_context_free(parser_context_t *context) {
    if (context == NULL)
        return;
    dict_free(context->auth_co_auth);
    dict_free(context->auth_papers);
    dict_free(context->auth_node);

    if (context->paper_type != NULL) {
        free(context->paper_type);
    }
    if (context->inner_tag != NULL) {
        free(context->inner_tag);
    }
    free(context);
}

parser_info_t *parser_info_new(int flag) {
    parser_info_t *info = malloc(sizeof(parser_info_t));
    parser_context_t *context = parser_context_new(flag);

    if (info == NULL)
        return NULL;
    if (context == NULL) {
        free(info);
        return NULL;
    }

    info->context = context;
    info->hndl_otg = hndl_otg;
    info->hndl_ctg = hndl_ctg;
    info->hndl_txt = hndl_txt;

    return info;
}

void parser_info_free(parser_info_t *info) {
    if (info == NULL)
        return;
    parser_context_free(info->context);
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
