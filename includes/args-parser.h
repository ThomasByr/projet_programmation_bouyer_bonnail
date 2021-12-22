/*

*/

#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "args-options.h"

/**
 * @brief parse user input in command line
 *
 * @param argc number of arguments
 * @param argv array of arguments
 * @param options_t structure containing all options
 */
void parse_args(int argc, char *argv[], options_t *options);

#endif
