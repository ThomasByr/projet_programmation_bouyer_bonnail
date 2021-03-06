#include <errno.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "protocol.h"

static const unsigned long _width = 20;

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

void alert(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    fflush(stdout);
    fprintf(stderr, "\033[0;31m");
    vfprintf(stderr, msg, args);
    if (errno) {
        fprintf(stderr, ": %s", strerror(errno));
    }
    fprintf(stderr, "\033[0m\n");
    va_end(args);
}

void warn(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    fflush(stdout);
    fprintf(stderr, "\033[0;33m");
    vfprintf(stderr, msg, args);
    if (errno) {
        fprintf(stderr, ": %s", strerror(errno));
    }
    fprintf(stderr, "\033[0m\n");
    va_end(args);
}

void award(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    fflush(stdout);
    fprintf(stderr, "\033[0;32m");
    vfprintf(stderr, msg, args);
    fprintf(stderr, "\033[0m\n");
    va_end(args);
}

int ask(const char *msd, ...) {
    va_list args;
    va_start(args, msd);
    fflush(stdout);
    fprintf(stderr, "\033[0;34m");
    vfprintf(stderr, msd, args);
    fprintf(stderr, "\033[0m [y/n] ");
    va_end(args);
    char buf[BUFSIZ];
    char *rv = fgets(buf, BUFSIZ, stdin);
    if (rv == NULL) {
        alert("Failed to read from stdin");
        return -1;
    }
    return buf[0] == 'y' || buf[0] == 'Y';
}

void _print_sep(void) {
    char s[_width + 1];
    memset(s, '=', _width);
    s[_width] = '\0';
    fprintf(stdout, "%s\n", s);
}

void print_usage(void) {
    fprintf(stdout, "\"Projet Programmation\" Bouyer Bonnail\n");
    fprintf(stdout, "Version: %s\n", VERSION);

    _print_sep();
    fprintf(stdout, "Usage: ./bin/main [OPTIONS]...\n");
    fprintf(stdout, "Options:\n");
    fprintf(stdout, "\t%-20s%s", "-h, --help", "Display this help\n");
    fprintf(stdout, "\t%-20s%s", "-v, --version", "Display the version\n");
    fprintf(stdout, "\t%-20s%s", "-q, --quiet",
            "Quiet mode (no output, conflicts will be ignored)\n");
    fprintf(stdout, "\t%-20s%s", "-i, --input_file",
            "Specify input file (needed), either xml database or bin\n");
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
}

void print_version(void) {
    fprintf(stdout, "\"Projet Programmation\" Bouyer Bonnail\n");
    fprintf(stdout, "Version: %s\n", VERSION);
    fprintf(stdout, "Compilation date: %s\n", __DATE__);
    fprintf(stdout, "Compilation time: %s\n", __TIME__);
    DEBUG_PRINT("Compilation mode : debug\n");

    _print_sep();
    fprintf(stdout, "Licence: GPLv3\n");
    fprintf(stdout, "Authors: %s\n", AUTHORS);
}

void disp_progress(size_t current, size_t total) {
    static unsigned long counter = 0;
    static unsigned long state = 0;
    if (state != total) {
        counter = 0;
        state = total;
    }

    counter++;
    if (counter < (total / 1000ul))
        return;

    char bar[BAR_WIDTH + 1];
    memset(bar, '.', BAR_WIDTH);
    bar[BAR_WIDTH] = '\0';
    size_t i;
    for (i = 0; i <= BAR_WIDTH * current / total; i++) {
        bar[i] = '#';
    }
    double percent = (double)(current + 1) / total * 100;
    fprintf(stdout, "\rin progress... [%s] %.1f%%", bar, percent);
    fflush(stdout);
    counter = 0;
}

unsigned long hash(char *str) {
    if (str == NULL)
        return 0;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

int compare(int hash_content, size_t item, size_t value) {
    switch (hash_content) {
    case 0:
        return item == value;
    case 1:
    default:
        return strcmp((char *)value, (char *)item) == 0;
    }
}

void see_progress(void) {
    if (ask("See estimated running progress?"))
        fprintf(stdout, "%s\n", status_to_string(_status));
}

void _handle_sigint(sig_atomic_t count) {
    if (count < THRESHOLD) {
        warn("\rInterrupt signal received - resend signal to stop process");
        if (signal(SIGINT, handle_signal) == SIG_ERR) {
            alert("Failed to register signal handler");
            exit(EXIT_FAILURE);
        }
        if (signal(SIGSEGV, handle_signal) == SIG_ERR) {
            alert("Failed to register signal handler");
            exit(EXIT_FAILURE);
        }
    } else {
        alert("\r\nInterrupt signal received - process will be stopped");
        see_progress();
        abort();
    }
}

void _handle_sigsev(void) {
    alert("\r\nSegmentation fault - process will be stopped");
    see_progress();
    abort();
}

void handle_signal(int sig) {
    static volatile sig_atomic_t count = 0;
    static int last_sig = 0;

    if (last_sig != sig) {
        count = 0;
        last_sig = sig;
    }
    count++;

    switch (sig) {
    case SIGINT:
        _handle_sigint(count);
        break;
    case SIGSEGV:
        _handle_sigsev();

    default:
        break;
    }
}

char *status_to_string(status_t status) {
    switch (status) {
    case LAUNCH:
        return "launching program";
    case THREADING:
        return "initial handling of signals";
    case ALLOCATING_MEMORY:
        return "allocating large amount of memory";
    case READING_FILE:
        return "reading file";
    case WRITING_FILE:
        return "writing file";
    case PARSING_XML:
        return "parsing xml database";
    case PARSING_BIN:
        return "parsing binary data";
    case PARSING_ARGS:
        return "parsing command line arguments";
    case CHECKING_ARGS:
        return "checking command line arguments validity";
    case MAKING_GRAPH:
        return "making graph";
    case GRAPH_WALKTHROUGH:
        return "walking through the graph";

    default:
        return "unknown";
    }
}
