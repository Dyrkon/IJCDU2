#include <stdio.h>
#include "htab.h"
#include "io.h"


int main(void)
{
    char *word = malloc(MAX_WORD * sizeof(char));
    FILE *f = fopen("tests/test.txt", "r");
    htab_t *tab = htab_init(4);
    htab_pair_t *pair = NULL;
    int i = 0;
    while ((i = read_word(word, 127, f)) != EOF)
    {
        pair = htab_lookup_add(tab, word);
        printf("key: %s, pair: %d\n", pair->key, pair->value);
    }
    free(word);
    fclose(f);
    htab_free(tab);

	return 0;
}
