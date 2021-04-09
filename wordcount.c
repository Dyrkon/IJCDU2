#include <stdio.h>
#include "htab.h"

int main(void)
{
    char *s = NULL;
    FILE *f = fopen("tests/test.txt", "r");
    int i = read_word(s, 127, f);
    printf("%d", i);
    printf("%s", s);
	return 0;
}
