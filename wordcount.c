#include <stdio.h>
#include "htab.h"

int main(void)
{
    char *word = NULL;
    FILE *f;
    f = fopen("tests/test.txt","r");
    printf("%d", read_word(word, MAX_WORD, f));
    printf("%s", word);

	return 0;
}
