#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "protocol.h"
#include "types.h"
#include "xml-parser.h"

void xml_test_0(void) {
    parser_info_t *info = parser_info_new();

    char filename[] = "../assets/eg.xml";
    parser_error_type_t err = parse(filename, info);
    hset_free(info->context->nodes);
    parser_info_free(info);
    assert_eq(err, PARSER_OK);
}

void xml_test_1(void) {
    char arr[] = "abcdefghijklmnopqrstuvwxyz";
    int count = 0;
    foreach (item of arr) {
        assert_eq(item, arr[count]);
        count++;
    }
    assert_eq(count, 27);
    assert_eq(lerp(5, 0, 10, 0, 100), 50);
    assert_eq(lerp(0.5, 0.0, 1.0, -1.0, 1.0), 0);
}

void xml_test_2(void) {
    int i = 0;
    (void)i;
}

void xml_parser_test() {
    test_case(xml_test_0);
    test_case(xml_test_1);
    test_case(xml_test_2);
}
