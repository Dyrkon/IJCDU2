// htab_move.c
// Řešení IJC-DU2, příklad b), 19.4.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Přesune tabulku do nové se zadanou velikostí

#include "htab.h"
#include "htab_priv.h"

htab_t *htab_move(size_t n, htab_t *from)
{
    htab_t *new_tab;
    new_tab = htab_init(n);
    size_t hash = 0;

    for (size_t i = 0; i < from->arr_size; ++i)
    {
        if (from->entries[i] != NULL)
        {
            hash = (htab_hash_function(from->entries[i]->pair.key) % n);
            new_tab->entries[hash] = from->entries[i];
            from->entries[i] = NULL;
        }
    }
    new_tab->size = from->size;
    from->size = 0;

    return new_tab;
}
