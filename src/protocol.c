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

void print_usage(void) {
    fprintf(stdout, "\"Projet Programmation\" Bouyer Bonnail\n");
    fprintf(stdout, "Version: %s\n", VERSION);
    char s[_width + 1];
    memset(s, '=', _width);
    s[_width] = '\0';
    fprintf(stdout, "%s\n", s);
    fprintf(stdout, "Usage: ./bin/main [OPTIONS]...\n");
    fprintf(stdout, "Options:\n");
    fprintf(stdout, "\t-h, --help\t\t\tDisplay this help\n");
    fprintf(stdout, "\t-v, --version\t\t\tDisplay the version\n");
    fprintf(stdout, "\t-V, --verbose\t\t\tGet extensive messages when running "
                    "the program\n");
    fprintf(stdout, "\t-D, --debug\t\t\tGet debug messages on errors and "
                    "warnings on run time\n");
}

void print_version(void) {
    fprintf(stdout, "\"Projet Programmation\" Bouyer Bonnail\n");
    fprintf(stdout, "Version: %s\n", VERSION);
    fprintf(stdout, "Compilation date: %s\n", __DATE__);
    fprintf(stdout, "Compilation time: %s\n", __TIME__);
    DEBUG_PRINT("Compilation mode : debug\n");
    char s[_width + 1];
    memset(s, '=', _width);
    s[_width] = '\0';
    fprintf(stdout, "%s\n", s);
    fprintf(stdout, "Licence: GPLv3\n");
    fprintf(stdout, "Authors: %s\n", AUTHORS);
}
