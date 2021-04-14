#include "htab.h"
#include "htab_priv.h"

void free_on_key(heshEntry_t *entry)
{
    if (entry->next == NULL)
    {
        free(entry->pair.key);
        free(entry);
        return;
    }
    else
    {
        printf("in loop key: %s, pair: %d\n", entry->pair.key, entry->pair.value);
        free_on_key(entry->next);
        printf("out loop key: %s, pair: %d\n", entry->pair.key, entry->pair.value);
        free(entry->pair.key);
        free(entry);
    }
}

bool htab_erase(htab_t * t, htab_key_t key)
{
    size_t hash = (htab_hash_function(key) % t->arr_size);

    struct heshEntry *suspect = t->entries[hash];

    if (suspect != NULL)
    {
        free_on_key(suspect);
        return true;
    }
    return false;
}
