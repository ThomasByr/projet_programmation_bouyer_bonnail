/*

*/

#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include "args-options.h"

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
