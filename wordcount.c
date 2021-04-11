#include <stdio.h>
#include "htab.h"
#include "htab_priv.h"


int main(void)
{
    word_t word;
    FILE *f = fopen("tests/test.txt", "r");
    htab_t *tab;
    tab = htab_init(4);
    int i = 0;
    while ((i = read_word(&word, 127, f)) != EOF)
    {
        htab_lookup_add(tab, word.s);
    }

    // htab_for_each(tab, printf);
    printf("%s", tab->entries[0]->pair.key);
    printf("%s", tab->entries[1]->pair.key);
    printf("%s", tab->entries[2]->pair.key);
    printf("%s", tab->entries[3]->pair.key);

	return 0;
}
