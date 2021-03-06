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
    int flag = options->quiet == 1 ? 2 : options->verbose == 1 ? 1 : 0;
    parser_info_t *info = parser_info_new(flag);

    char *filename = options->input_file;
    char *ext = strrchr(filename, '.');
    if (ext == NULL) {
        ext = "";
    } else {
        ext++;
    }

    int rv = 0;

    if (strcmp(ext, "xml") == 0) {
        // parse xml file into .bin file
        parser_error_type_t err = parse(filename, info, flag);

        switch (err) {
        case PARSER_OK:
            if (options->verbose == 1) {
                char *msg = parser_error_type_to_string(err);
                award(msg);
            }
            break;
        default:
            rv = 1;
            if (options->quiet == 0) {
                char *msg = parser_error_type_to_string(err);
                alert(msg);
            }
            break;
        }

    } else if (strcmp(ext, "bin") == 0 || options->need_graph == 1) {
        // read .bin file to make graph
    }

    hset_t *nodes = info->context->nodes;
    parser_info_free(info); // does not free nodes info->context->nodes

    hset_free(nodes); // at the end
    return rv;
}
