#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "xml-parser.h"

static const char open_tag = '<';   // opening tag
static const char close_tag = '>';  // closing tag
static const char end_tag = '/';    // ending tag
static const char delims[] = " \n"; // delimiters

void get_tag_id(char *tag) {
    char *p = tag;
    while (*p != '\0' && strchr(delims, *p) == NULL)
        p++;
    *p = '\0';
}

parser_error_type_t parse_buffer(char *buffer, long size, parser_info_t *info,
                                 int flag) {
    char *p = buffer;  // current position in buffer
    char *pp = buffer; // previous position in buffer

    char buff[XMLP_BUFFER_SIZE] = "";
    int index = 0;
    int is_opening_tag = 0;
    int is_ending_tag = 0;

    // read the buffer character by character
    while (p < buffer + size) {

        if (flag == 1) {
            // current character number
            size_t curr = p - buffer;
            size_t tot = (size_t)size;
            disp_progress(curr, tot);
        }

        if (*p == open_tag) {
            if (index > 0) {
                buff[index] = '\0';
                info->hndl_txt(buff, info->context);
            }
            check(is_opening_tag, is_ending_tag);
            is_opening_tag = 1;
            reset(index, buff);
            pp = p;
            p++;
            continue;
        }
        if (*p == end_tag && *pp == open_tag) {
            is_opening_tag = 0;
            is_ending_tag = 1;
            reset(index, buff);
            pp = p;
            p++;
            continue;
        }
        if (*p == close_tag) {
            buff[index] = '\0';
            get_tag_id(buff);

            if (is_opening_tag == 1)
                info->hndl_otg(buff, info->context);
            if (is_ending_tag == 1)
                info->hndl_ctg(buff, info->context);

            is_opening_tag = 0;
            is_ending_tag = 0;
            reset(index, buff);
            pp = p;
            p++;
            continue;
        }

        buff[index] = *p;
        index++;
        pp = p;
        p++;
    }
    check(is_opening_tag, is_ending_tag);
    return PARSER_OK;
}

parser_error_type_t parse(const char *filename, parser_info_t *info, int flag) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) // error while opening file
        return ERROR_UNABLE_TO_OPEN_FILE;

    // get size of file
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    // allocate memory to contain the whole file
    if (flag == 1)
        fprintf(stdout, "allocating %ld bytes of memory\n", size);
    char *buffer = (char *)malloc(sizeof(char) * (size + 1));
    if (buffer == NULL) // error while allocating memory
        return ERROR_UNABLE_TO_ALLOCATE_MEMORY;
    memset(buffer, 0, size);

    // copy the file into the buffer
    size_t result = fread(buffer, 1, size, fp);
    buffer[size] = '\0';
    if (result != (size_t)size) // error while reading file
        return ERROR_WHILE_READING_FILE;

    // close file
    fclose(fp);

    // parse the file
    if (flag == 1)
        fprintf(stdout, "parsing file %s\n", filename);
    parser_error_type_t err = parse_buffer(buffer, size, info, flag);
    if (flag == 1)
        fprintf(stdout, "\n");

    free(buffer);
    return err;
}
