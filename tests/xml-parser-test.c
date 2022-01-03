#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "protocol.h"
#include "types.h"
#include "xml-parser.h"

void xml_test_error_0(void) {
    parser_info_t *info = parser_info_new();

    char filename[] = "../assets/eg.xml";
    parser_error_type_t err = parse(filename, info);
    parser_info_free(info);
    assert_eq(err, PARSER_OK);
}

<<<<<<< HEAD
void test_0(void)
{
    char filename[] = "../assets/eg.xml";
    FILE *fp = fopen(filename, "r");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char *buffer = (char *)malloc(sizeof(char) * (size + 1));
    assert_neq(buffer, NULL);

    size_t result = fread(buffer, 1, size, fp);
    buffer[size] = '\0';
    assert_eq(result, (size_t)size);
    fclose(fp);

    long i1 = find_next_tag(buffer, 0, size);
    long i2 = find_next_tag(buffer, i1, size);
    long i3 = find_next_tag(buffer, i2, size);

    assert_eq(i1, 85l);
    assert_eq(i2, 4l);
    assert_eq(i3, 8l);
}

void test_1(void)
{
    char *ext[] = {"article", "phdthesis", "mastersthesis"};
    int i = -1;
    for each (e, ext, 3)
        assert_eq(strcmp(e, ext[++i]), 0);
}

void xml_parser_test()
{
    test_case(test_error_0);
    // test_case(test_0);
    test_case(test_1);
=======
void xml_test_0(void) {
    char arr[] = "abcdefghijklmnopqrstuvwxyz";
    int count = 0;
    foreach (item of arr) {
        (void)item;
        count++;
    }
    assert_eq(count, 27);
    assert_eq(lerp(5, 0, 10, 0, 100), 50);
    assert_eq(lerp(0.5, 0.0, 1.0, -1.0, 1.0), 0);
}

void xml_test_1(void) {
    int i = 0;
    (void)i;
}

void xml_parser_test() {
    test_case(xml_test_error_0);
    test_case(xml_test_0);
    test_case(xml_test_1);
>>>>>>> 7c92f791ee13737df0c25425f9c58acd01c9783c
}
