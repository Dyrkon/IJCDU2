#include "htab.h"
#include "htab_priv.h"

// TODO(rework the counts)
bool htab_erase(htab_t * t, htab_key_t key)
{
    size_t hash = (htab_hash_function(key) % t->arr_size);
    heshEntry_t *suspect = t->entries[hash];
    heshEntry_t *next = NULL;
    // TODO(t->size )
    if (suspect != NULL)
    {
        while(true)
        {
            if (suspect->next == NULL)
            {
                if (!strcmp(suspect->pair.key,key))
                {
                    t->size -= suspect->pair.value;
                    free(suspect->pair.key);
                    free(suspect);
                    t->entries[hash] = NULL;
                    break;
                }
                else
                    break;
            }
            else
            {
                if (!strcmp(suspect->pair.key,key))
                {
                    t->size -= suspect->pair.value;
                    next = suspect->next;
                    free(suspect->pair.key);
                    free(suspect);
                    suspect = next;}
                else
                    break;
            }
        }
        return true;
    }
    return false;
}
