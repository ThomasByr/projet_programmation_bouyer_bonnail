#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xml-parser.h"

void get_tag_id(char *tag)
{
    char *p = tag;
    while (*p != '\0' && strchr(delims, *p) == NULL)
        p++;
    *p = '\0';
}

parser_error_type_t parse_buffer(char *buffer, long size, parser_info_t *info)
{
    char *p = buffer;

    char buff[XMLP_BUFFER_SIZE] = "";
    int index = 0;
    int is_opening_tag = 0;
    int is_ending_tag = 0;

    // read the buffer character by character
    while (p < buffer + size)
    {
        if (*p == open_tag)
        {
            if (index > 0)
            {
                buff[index] = '\0';
                info->handleText(buff, info->data);
            }
            check(is_opening_tag, is_ending_tag);
            is_opening_tag = 1;
            reset(index, buff);
            p++;
            continue;
        }
        if (*p == end_tag)
        {
            is_opening_tag = 0;
            is_ending_tag = 1;
            reset(index, buff);
            p++;
            continue;
        }
        if (*p == close_tag)
        {
            buff[index] = '\0';
            get_tag_id(buff);

            if (is_opening_tag == 1)
                info->handleOpenTag(buff, info->data);
            if (is_ending_tag == 1)
                info->handleCloseTag(buff, info->data);

            is_opening_tag = 0;
            is_ending_tag = 0;
            reset(index, buff);
            p++;
            continue;
        }

        buff[index] = *p;
        index++;
        p++;
    }
    check(is_opening_tag, is_ending_tag);
    return PARSER_OK;
}

parser_error_type_t parse(const char *filename, parser_info_t *info)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) // error while opening file
        return ERROR_UNABLE_TO_OPEN_FILE;

    // get size of file
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    // allocate memory to contain the whole file
    char *buffer = (char *)malloc(sizeof(char) * size);
    if (buffer == NULL) // error while allocating memory
        return ERROR_UNABLE_TO_OPEN_FILE;

    // copy the file into the buffer
    size_t result = fread(buffer, 1, size, fp);
    if (result != (size_t)size) // error while reading file
        return ERROR_UNABLE_TO_OPEN_FILE;

    // close file
    fclose(fp);

    // parse the file
    parser_error_type_t error = parse_buffer(buffer, size, info);
    free(buffer);
    return error;
}
