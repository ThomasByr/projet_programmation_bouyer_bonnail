#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "protocol.h"
#include "types.h"
#include "xml-parser.h"

void xml_test_0(void) {
    parser_info_t *info = parser_info_new(2);

    char filename[] = "../assets/eg.xml";               // test asset
    parser_error_type_t err = parse(filename, info, 2); // parse file
    hset_free(info->context->nodes);                    // free nodes
    parser_info_free(info);                             // free info
    assert_eq(err, PARSER_OK);                          // check for error
}

void xml_test_1(void) {
    char arr[] = "abcdefghijklmnopqrstuvwxyz"; // test string
    int count = 0;
    // note: char [] will produce the desired result while char * will not
    foreach (item of arr) {
        assert_eq(item, arr[count]); // check for equality
        count++;
    }
    assert_eq(count, 27);                  // check for count
    assert_eq(lerp(5, 0, 10, 0, 100), 50); // check for lerp
    assert_eq(lerp(0.5, 0.0, 1.0, -1.0, 1.0), 0);
}

void xml_test_2(void) {
    int i = 0; // fake test
    (void)i;
}

void xml_parser_test() {
    test_case(xml_test_0);
    test_case(xml_test_1);
    test_case(xml_test_2);
}
