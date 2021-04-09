#include "htab.h"
#include "htab_priv.h"

htab_pair_t * htab_find(htab_t * t, htab_key_t key)
{
    size_t hash = (htab_hash_function(key) % t->arr_size);

    for (struct heshEntry *suspect = t->entries[hash];
        suspect->next != NULL;
        suspect = t->entries[hash]->next)
    {
        if (suspect->pair.key == key)
        {
            return &suspect->pair;
        }
    }
    return NULL;
}
