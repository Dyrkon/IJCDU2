#include "htab.h"
#include "htab_priv.h"

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key)
{
    size_t hash = htab_hash_function(key);
    struct heshEntry *suspect = t->entries[hash];
    for (;suspect->next != NULL; suspect = t->entries[hash]->next)
    {
        if (suspect->pair.key == key)
        {
            return &suspect->pair;
        }
    }

    // TODO
    if ((suspect->next = malloc(sizeof(heshEntry_t))) != NULL)
    {
        suspect->next->next = NULL;
        if ((suspect->next->pair.key = malloc(strlen(key))) != NULL)
            strcpy(suspect->next->pair.key, key);
        // suspect->pair.value = hash;
    }
    return NULL;
}
