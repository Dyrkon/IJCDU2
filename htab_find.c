// htab_find.c
// Řešení IJC-DU2, příklad b), 19.4.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Pokusí se najít položku v hashmapě a vrátí ji, nebo NULL

#include "htab.h"
#include "htab_priv.h"

htab_pair_t * htab_find(htab_t * t, htab_key_t key)
{
    size_t hash = (htab_hash_function(key) % t->arr_size);
    bool firs_time = true;

    if (t->entries[hash] != NULL)
    {
        for (struct heshEntry *suspect = t->entries[hash]; suspect->next != NULL || firs_time; suspect = t->entries[hash]->next)
        {
            if (!strcmp(suspect->pair.key,key))
            {
                return &suspect->pair;
            }
            firs_time = false;
        }
    }
    return NULL;
}
