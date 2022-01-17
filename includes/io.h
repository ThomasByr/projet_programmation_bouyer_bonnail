/*

*/

#ifndef IO_H
#define IO_H

#include "args-options.h"
#include "args-parser.h"
#include "info-parser.h"
#include "xml-parser.h"

/**
 * @brief execute main program using the options
 *
 * @param options previously parsed options
 * @return int - 0 if success, 1 if error
 */
int exec(options_t *options);

#endif
