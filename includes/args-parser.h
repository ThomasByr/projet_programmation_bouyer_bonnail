/* args-parser.c
Functions to parse and check the validity of the command line arguments.

*/

#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include "args-options.h"
#include "protocol.h"

extern status_t _status;

/**
 * @brief parse user input in command line
 *
 * @param argc number of arguments
 * @param argv array of arguments
 * @param options_t structure containing all options
 */
void parse_args(int argc, char *argv[], options_t *options);

/**
 * @brief check if the user input is valid once the options are parsed
 *
 * @param options - structure containing all options
 */
void check_args(options_t *options);

#endif
