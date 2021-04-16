#include <stdio.h>
#include "htab.h"
#include "io.h"


void test(htab_t *tab)
{
    printf("bucket size: %zu\n", htab_bucket_count(tab));
    printf("velikost %zu\n", htab_size(tab));
    if (htab_erase(tab, "jedna"))
        printf("jedna odstraneno\n");
    printf("bucket size: %zu\n", htab_bucket_count(tab));
    printf("velikost %zu\n", htab_size(tab));

    htab_t *new = htab_move(3, tab);
    printf("bucket size: %zu\n", htab_bucket_count(new));
    printf("velikost %zu\n", htab_size(new));

    printf("Vymazavam ...\n");
    htab_clear(tab);
    printf("bucket size: %zu\n", htab_bucket_count(tab));
    // Tady nesedi size
    printf("velikost %zu\n", htab_size(tab));

    printf("bucket size: %zu\n", htab_bucket_count(new));
    printf("velikost %zu\n", htab_size(new));
    htab_free(new);
}

void foreach(htab_t *tab)
{
    // TODO
    htab_for_each(tab, NULL);
}

int main(void)
{
    char word[MAX_WORD];
    FILE *f = fopen("tests/test.txt", "r");
    htab_t *tab = htab_init(4);
    htab_pair_t *pair = NULL;
    int i = 0;
    while ((i = read_word(word, 127, f)) != EOF)
    {
        pair = htab_lookup_add(tab, word);
        printf("key: %s, pair: %d\n", pair->key, pair->value);
    }
    printf("Test ...\n");
    test(tab);
    fclose(f);
    htab_free(tab);

	return 0;
}
