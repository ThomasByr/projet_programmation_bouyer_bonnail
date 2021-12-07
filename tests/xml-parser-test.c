#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xml-parser.h"
#include "macros.h"

void test_error_0(void)
{
    parser_info_t *info = parser_info_new();

    char filename[] = "../assets/eg.xml";
    parser_error_type_t err = parse(filename, info);
    parser_info_free(info);
    assert_eq(err, PARSER_OK);
}

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
}
