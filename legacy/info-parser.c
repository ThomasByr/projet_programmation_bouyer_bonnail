#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "info-parser.h"

char *external[] = {
    "article",      "inproceedings", "proceedings",   "book",
    "incollection", "phdthesis",     "mastersthesis", "www",
};

char *look_for[] = {
    "title", "author", "year", "pages", "url",
};

int contains(char **str, const char *s, size_t n) {
    for (size_t i = 0; i < n; i++) {
        char *item = str[i];
        if (strcmp(item, s) == 0) {
            return 1;
        }
    }
    return 0;
}

int hndl_txt(char *txt, parser_context_t *context) {
    _status = WRITING_FILE;

    if (context->inner_tag == NULL)
        return 0;

    // +case author
    if (strcmp(context->inner_tag, "author") == 0) {
        char *current = strdup(txt);
        hset_push(context->auth_set, current);

        if (context->author == NULL) {
            // this is the main author of the article
            context->author = current;
        }

        dict_t *auth_co_auth = context->auth_co_auth;
        char *author = context->author;

        // does the current author have an entry ?
        size_t rv0 = dict_get(auth_co_auth, current);
        if (rv0 == 0)
            dict_push(auth_co_auth, current, hset_new(1));
        rv0 = dict_get(auth_co_auth, current);
        ASSERT(rv0 > 0);

        // if the current author is the main author
        // it should already have an entry so do nothing

        // if the current author is not the main author
        // add it the the main author's co-author
        // and for each name of the main author's co-author
        // add current -> name and name -> current

        if (strcmp(author, txt) != 0) {
            hset_t *main_co_auth = (hset_t *)dict_get(auth_co_auth, author);
            ASSERT(main_co_auth); // the main author should always be defined
            hset_push(main_co_auth, current);

            hset_itr_t *itr = hset_itr_new(main_co_auth);
            hset_t *co0 = (hset_t *)rv0; // current author's co-author
            while (hset_itr_has_next(itr)) {
                char *name = (char *)hset_itr_value(itr);
                ASSERT(name);
                hset_t *co1 = (hset_t *)dict_get(auth_co_auth, name);
                ASSERT(co1);

                hset_push(co1, current);
                hset_push(co0, name);

                hset_itr_next(itr);
            }
            hset_itr_free(itr); // free tmp iterator
        }
    }
    return 0;
}

int hndl_otg(char *tag, parser_context_t *context) {
    _status = WRITING_FILE;
    int is_external = contains(external, tag, 8);
    int is_look_for = contains(look_for, tag, 5);

    if (is_external == 0 && is_look_for == 0) {
        return 0;
    } // skip unwanted tags

    if (is_external) {
        context->paper_type = strdup(tag); // set paper type
        context->author = NULL;            // reset main author
    }
    if (is_look_for) {
        if (context->inner_tag)
            free(context->inner_tag);
        context->inner_tag = strdup(tag);
    }
    return 0;
}

int hndl_ctg(char *tag, parser_context_t *context) {
    _status = WRITING_FILE;
    int is_external = contains(external, tag, 8);
    if (is_external == 0)
        return 0;

    if (context->paper_type)
        free(context->paper_type);
    if (context->inner_tag)
        free(context->inner_tag);
    context->paper_type = NULL;
    context->inner_tag = NULL;
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

    ctx->auth_co_auth = dict_new(1);
    ctx->auth_papers = dict_new(1);
    ctx->auth_node = dict_new(1);
    ctx->auth_set = hset_new();
    ctx->nodes = hset_new();

    ctx->out = NULL;
    return ctx;
}

void parser_context_free(parser_context_t *context) {
    if (context == NULL)
        return;

    dict_itr_t *itr0 = dict_itr_new(context->auth_co_auth);
    while (dict_itr_has_next(itr0)) {
        hset_t *value = (hset_t *)dict_itr_value(itr0);
        hset_free(value);
        dict_itr_next(itr0);
    }
    dict_itr_free(itr0);
    dict_free(context->auth_co_auth);

    hset_itr_t *itr1 = hset_itr_new(context->auth_set);
    hset_itr_discard_all(itr1, free);
    hset_itr_free(itr1);
    hset_free(context->auth_set);

    dict_free(context->auth_papers);
    dict_free(context->auth_node);

    if (context->paper_type != NULL)
        free(context->paper_type);
    if (context->inner_tag != NULL)
        free(context->inner_tag);
    if (context->out)
        fclose(context->out);
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
        return "Error while reading the file into memory (possibly pointer "
               "out "
               "of memory)";
    case ERROR_UNABLE_TO_OPEN_FILE:
        return "Unable to open the file (possibly wrong path)";
    case ERROR_UNEXPECTED_END_OF_TAG:
        return "Unexpected end of tag (possibly a < was not matched with a "
               ">)";

    default:
    case PARSER_OK:
        return "Parsing was successful (possibly luck)";
    }
}
