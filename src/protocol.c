#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "protocol.h"

static const unsigned long _width = 80;

int compare_strings(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int compare_ints(const void *a, const void *b) {
    if (*(int *)a < *(int *)b) {
        return -1;
    } else if (*(int *)a > *(int *)b) {
        return 1;
    } else {
        return 0;
    }
}

int compare_floats(const void *a, const void *b) {
    if (*(float *)a < *(float *)b) {
        return -1;
    } else if (*(float *)a > *(float *)b) {
        return 1;
    } else {
        return 0;
    }
}

void complain(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    fprintf(stderr, "\033[0;31m");
    vfprintf(stderr, msg, args);
    if (errno) {
        fprintf(stderr, ": %s\n", strerror(errno));
    } else {
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "\033[0m");
    va_end(args);
}

void print_sep(void) {
    char s[_width + 1];
    memset(s, '=', _width);
    s[_width] = '\0';
    fprintf(stdout, "%s\n", s);
}

void print_usage(void) {
    fprintf(stdout, "\"Projet Programmation\" Bouyer Bonnail\n");
    fprintf(stdout, "Version: %s\n", VERSION);

    print_sep();
    fprintf(stdout, "Usage: ./bin/main [OPTIONS]...\n");
    fprintf(stdout, "Options:\n");
    fprintf(stdout, "\t%-20s%s", "-h, --help", "Display this help\n");
    fprintf(stdout, "\t%-20s%s", "-v, --version", "Display the version\n");
    fprintf(stdout, "\t%-20s%s", "-i, --input_file",
            "Specify input file (needed)\n");
    fprintf(stdout, "\t%-20s%s", "-p, --path",
            "Use it twice to find the closest path between authors\n");
    fprintf(stdout, "\t%-20s%s", "-l, --list",
            "List authors whom at least one paper contains a specified word\n");
    fprintf(stdout, "\t%-20s%s", "-a, --author", "List papers of an author\n");
    fprintf(stdout, "\t%-20s%s", "-n, --n_closest",
            "List co-authors of an author (specified with -a) lying withing a "
            "specified distance\n");
    fprintf(stdout, "\t%-20s%s", "-V, --verbose",
            "Get extensive messages when running the program\n");
    fprintf(stdout, "\t%-20s%s", "-D, --debug",
            "Get debug messages on errors and warnings on run time\n");
}

void print_version(void) {
    fprintf(stdout, "\"Projet Programmation\" Bouyer Bonnail\n");
    fprintf(stdout, "Version: %s\n", VERSION);
    fprintf(stdout, "Compilation date: %s\n", __DATE__);
    fprintf(stdout, "Compilation time: %s\n", __TIME__);
    DEBUG_PRINT("Compilation mode : debug\n");

    print_sep();
    fprintf(stdout, "Licence: GPLv3\n");
    fprintf(stdout, "Authors: %s\n", AUTHORS);
}
