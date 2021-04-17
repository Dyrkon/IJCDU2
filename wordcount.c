#include <stdio.h>
#include "htab.h"
#include "io.h"

void print_pair(htab_pair_t *pair)
{
    printf("%-7s %d\n", pair->key, pair->value);
}

int main(void)
{
    char word[MAX_WORD];
    FILE *f = fopen("tests/test.txt", "r");
    // TODO(velikost tabulky)
    htab_t *tab = htab_init(4);
    htab_pair_t *pair = NULL;
    int i = 0;
    while ((i = read_word(word, 127, f)) != EOF)
    {
        pair = htab_lookup_add(tab, word);
        pair->value++;
    }

    void (*F)(htab_pair_t*) = print_pair;

    htab_for_each(tab,(F));

    fclose(f);
    htab_free(tab);

	return 0;
}
