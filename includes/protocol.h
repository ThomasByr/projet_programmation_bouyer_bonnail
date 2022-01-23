/* protocol.h
Some general-purpose macros and functions.

*   `foreach(item in array)` macro only works for static allocated arrays.
This is used to iterate over an unidimensional array. Note that `char arr[] =
...;` will be iterated over properly but `char *arr = ...;` will not.
*   `lerp` macro is used to "move" a value from one range to another.
It is the caller's responsability to cast the values to the same type.

*/

#ifndef PROTOCOL_H
#define PROTOCOL_H

#ifdef DEBUG
#include <assert.h>
#endif

#ifdef DEBUG
#define DEBUG_PRINT(...) fprintf(stdout, __VA_ARGS__)
#define ASSERT(x) assert(x)
#else
#define DEBUG_PRINT(...)
#define ASSERT(x) (void)(x)
#endif

#define FOREACH(type, item, array, size)                                   \
    for (size_t X(keep) = 1, X(i) = 0; X(i) < (size); X(keep) = 1, X(i)++) \
        for (type item = (array)[X(i)]; X(keep); X(keep) = 0)

#define _foreach(item, array) \
    FOREACH(__typeof__(array[0]), item, array, length(array))
#define foreach(item_of_array) _foreach(item_of_array)

#define of ,
#define length(array) (sizeof(array) / sizeof((array)[0]))
#define CAT(a, b) CAT_HELPER(a, b)
#define CAT_HELPER(a, b) a##b
#define X(name) CAT(__##name, __LINE__)

#define VERSION "0.0.4"
#define AUTHORS "Julie BONNAIL & Thomas BOUYER"

#define BAR_WIDTH 20ul
#define THRESHOLD 2

#define lerp(x, x0, x1, y0, y1) \
    (((y0) * ((x1) - (x)) + (y1) * ((x) - (x0))) / ((x1) - (x0)))

enum status_e {
    LAUNCH,
    THREADING,
    ALLOCATING_MEMORY,
    READING_FILE,
    WRITING_FILE,
    PARSING_XML,
    PARSING_BIN,
    PARSING_ARGS,
    CHECKING_ARGS,
    MAKING_GRAPH,
    GRAPH_WALKTHROUGH,
};
/**
 * @brief The status_t struct is used to store the status of the program
 *
 */
typedef enum status_e status_t;

extern status_t _status;

/**
 * @brief duplicate a string.
 * Since -std=c18, `strdup` is not available because it is not part of the
 * standard C library.
 *
 * @return char* - pointer to the duplicated string
 */
extern char *strdup(const char *);

/**
 * @brief send a error to the client.
 * Does not exit the process.
 *
 * @param msg message to send
 */
void alert(const char *msg, ...);

/**
 * @brief send a warning to the client.
 * Does not exit the process.
 *
 * @param msg message to send
 */
void warn(const char *msg, ...);

/**
 * @brief send a message to the client.
 * Does not exit the process.
 *
 * @param msg message to send
 */
void award(const char *msg, ...);

/**
 * @brief ask the user to confirm an action.
 *
 * @param msg message to send
 * @return int - 1 if the user confirms, 0 otherwise, -1 if error
 */
int ask(const char *msg, ...);

/**
 * @brief display the main usage of the program.
 *
 */
void print_usage(void);

/**
 * @brief display the version and additional infos of the program.
 *
 */
void print_version(void);

/**
 * @brief diaplay the progress of some operation.
 *
 * @param current current tick
 * @param total total number of ticks
 */
void disp_progress(size_t current, size_t total);

/**
 * @brief compare two strings.
 *
 * @param a first string
 * @param b second string
 * @return int
 */
int compare_strings(const void *a, const void *b);

/**
 * @brief compare two integers.
 *
 * @param a first integer
 * @param b second integer
 * @return int - -1 if a < b, 0 if a == b, 1 if a > b
 */
int compare_ints(const void *a, const void *b);

/**
 * @brief compare two floats.
 *
 * @param a first float
 * @param b second float
 * @return int - -1 if a < b, 0 if a == b, 1 if a > b
 */
int compare_floats(const void *a, const void *b);

/**
 * @brief djb2 hash function by Dan Bernstein
 *
 * @param str string to hash
 * @return unsigned long
 */
unsigned long hash(char *str);

/**
 * @brief compare two size_t, interpreted as either pointers or strings
 *
 * @param hash_content 0 for pointer, non-zero for string
 * @param item first item
 * @param value second item
 * @return int - result of the comparison
 */
int compare(int hash_content, size_t item, size_t value);

/**
 * @brief handle signals
 *
 * @param sig signal to handle
 */
void handle_signal(int sig);

/**
 * @brief get string representation of a status_t
 *
 * @param status status to get the string representation of
 * @return char* - string representation of the status
 */
char *status_to_string(status_t status);

#endif
