#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <getopt.h>
#include <limits.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

#include "io.h"

int exec(options_t *options) {
    parser_info_t *info = parser_info_new();
    parse(options->input_file, info);

    hset_t *nodes = info->context->nodes;
    (void)nodes;
    parser_info_free(info); // does not free nodes info->context->nodes

    hset_free(nodes); // at the end
    return 0;
}
