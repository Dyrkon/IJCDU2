// wordcount.c
// Řešení IJC-DU2, příklad b), 19.4.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// C implementace C++ programu  s hashmapou

#include <stdio.h>
#include "htab.h"
#include "io.h"

/*
 *  Toto číslo jsem zvolil hlavně kvůli testovacím datům.
 *  V případech s malým vstupem je C++ program rychlejší o desítky procent, což je ale ve výsledku velice krátký časový úsek.
 *  S daty velikosti knihy z www.gutenberg.org nebo výstupu příkazu "seq 1000000 2000000|shuf" je má C implementace rychlejší
 *  v jak statické, tak dynamické verzi o téměr polovinu. Testováno na "Manjaro 21.0.2 Ornara" s Intel Core i9-9900K
 *  Implementace v C++ je hospodárnější s pamětí, ale u hashmap je místo lepší plýtvat, než ho šetřit a tím program spomalovat.
 */
#define START 100069

void print_pair(htab_pair_t *pair)
{
    printf("%s\t%d\n", pair->key, pair->value);
}

int main(void)
{
    char word[MAX_WORD+1];
    htab_t *tab = NULL;
    if ((tab = htab_init(START)) == NULL)
    {
        fprintf(stderr, "Alokace tabulky selhala\n");
        return 1;
    }
    htab_pair_t *pair = NULL;
    bool warned = false;
    int i = 0;
    while ((i = read_word(word, 127, stdin)) != EOF)
    {
        if (word[MAX_WORD] == EOF)
        {
            if (!warned)
                fprintf(stderr, "Slovo bylo načteno jen z části\n");
            warned = true;
            word[MAX_WORD] = '\0';
        }
        if ((pair = htab_lookup_add(tab, word)) != NULL)
            pair->value++;
        else
        {
            fprintf(stderr, "Slovo se nepodarilo pridat\n");
        }
    }

    void (*F)(htab_pair_t*) = print_pair;

    htab_for_each(tab,(F));

    htab_free(tab);

	return 0;
}
