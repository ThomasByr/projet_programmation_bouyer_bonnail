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

parser_error_t parse(const char *filename, parser_info_t *info)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) // error while opening file
        return ERROR_UNABLE_TO_OPEN_FILE;

    char curr;                        // curr is the current character
    char prev = '\0';                 // prev is the previous character
    char buff[XMLP_BUFFER_SIZE] = ""; // this buffer is used to store the current content
    int index = 0;                    // index of the current character in buff

    int is_opening_tag = 0; // is the current character in an opening tag?
    int is_ending_tag = 0;  // is the current character in a ending tag?

    while ((curr = fgetc(fp)) != EOF)
    {
        if (curr == open_tag) // if the current char is an opening tag '<'
        {
            if (index > 0) // if the buffer is not empty
            {
                buff[index] = '\0';                 // add the end of string character
                info->handleText(buff, info->data); // handle the text before the opening tag
            }
            check(is_opening_tag, is_ending_tag); // if the previous tag was not closed
            is_opening_tag = 1;                   // we are in an opening tag
            reset(index, buff);                   // reset the buffer
            prev = curr;                          // save the current character
            continue;                             // move on to the next character
        }
        if (curr == end_tag && prev == open_tag) // if the current char is an ending tag '/'
        {
            is_opening_tag = 0; // we are not in an opening tag anymore
            is_ending_tag = 1;  // we are in an ending tag
            reset(index, buff); // reset the buffer
            prev = curr;        // save the current character
            continue;           // move on to the next character
        }
        if (curr == close_tag) // if the current char is a closing tag '>'
        {
            buff[index] = '\0'; // terminate the string
            get_tag_id(buff);   // get the tag name

            if (is_opening_tag == 1)
                info->handleOpenTag(buff, info->data); // handle the opening tag
            if (is_ending_tag == 1)
                info->handleCloseTag(buff, info->data); // handle the endind tag

            is_opening_tag = 0; // we are not in an opening tag anymore
            is_ending_tag = 0;  // we are not in an ending tag anymore
            reset(index, buff); // reset the buffer
            prev = curr;        // save the current character
            continue;           // move on to the next character
        }

        buff[index] = curr; // add the current character to the buffer
        index++;            // increment the index
        prev = curr;        // save the current character
    }

    check(is_opening_tag, is_ending_tag); // if the tag is not closed by the end of the file
    return PARSER_OK;
}
