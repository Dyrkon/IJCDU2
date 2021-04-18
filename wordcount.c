#include <stdio.h>
#include "htab.h"
#include "io.h"

void print_pair(htab_pair_t *pair)
{
    printf("%s\t%d\n", pair->key, pair->value);
}

int main(void)
{
    char word[MAX_WORD+1];
    // TODO(velikost tabulky)
    htab_t *tab = htab_init(1000000);
    htab_pair_t *pair = NULL;
    bool varned = false;
    int i = 0;
    while ((i = read_word(word, 127, stdin)) != EOF)
    {
        if (word[MAX_WORD] == EOF)
        {
            if (!varned)
                fprintf(stderr, "Slovo bylo načteno jen z části\n");
            varned = true;
            word[MAX_WORD] = '\0';
        }

        pair = htab_lookup_add(tab, word);
        pair->value++;
    }

    void (*F)(htab_pair_t*) = print_pair;

    htab_for_each(tab,(F));

    htab_free(tab);

	return 0;
}
