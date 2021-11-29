#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xml-parser.h"
#include "macros.h"

void test_count()
{
    char *line = "abcdefghijklmnopqrstuvwxyz";
    char *w0 = "abc";
    char *w1 = "def";
    char *w2 = "ghi";
    char *w3 = "aaa";
    assert_equal(count(line, w0), 1);
    assert_equal(count(line, w1), 1);
    assert_equal(count(line, w2), 1);
    assert_equal(count(line, w3), 0);
}

int main(void)
{
    test_case(test_count);
    return 0;
}
