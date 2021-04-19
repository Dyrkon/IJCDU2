// htab_erase.c
// Řešení IJC-DU2, příklad b), 19.4.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Pokusí se vymazat položku z mapy a při úspěchu vrátí true, jinak false

#include "htab.h"
#include "htab_priv.h"

bool htab_erase(htab_t * t, htab_key_t key)
{
    size_t hash = (htab_hash_function(key) % t->arr_size);
    heshEntry_t *suspect = t->entries[hash];
    heshEntry_t *next = NULL;
    if (suspect != NULL)
    {
        while(true)
        {
            if (suspect->next == NULL)
            {
                if (!strcmp(suspect->pair.key,key))
                {
                    t->size--;
                    free((char *)suspect->pair.key);
                    free(suspect);
                    t->entries[hash] = NULL;
                    break;
                }
            }
            else
            {
                if (!strcmp(suspect->pair.key,key))
                {
                    t->size--;
                    next = suspect->next;
                    free((char *)suspect->pair.key);
                    free(suspect);
                    suspect = next;
                }
            }
        }
        return true;
    }
    return false;
}
