#include "htab.h"
#include "htab_priv.h"

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key)
{
    size_t hash = (htab_hash_function(key) % t->arr_size);
    heshEntry_t *suspect = t->entries[hash];
    bool first_time = true;

    if (suspect != NULL)
    {
        for (;suspect != NULL || first_time; suspect = suspect->next)
        {
            if (!strcmp(suspect->pair.key,key))
            {
                return &suspect->pair;
            }
            else if (suspect->next == NULL)
            {
                if ((suspect->next = malloc(sizeof(heshEntry_t))) != NULL)
                {
                    suspect->next->next = NULL;
                    if ((suspect->next->pair.key = malloc(strlen(key)+1)) != NULL)
                        strcpy(suspect->next->pair.key, key);
                    else {
                        free(suspect);
                        return NULL;
                    }
                    suspect->next->pair.value = 0;
                    t->size++;
                    return &suspect->next->pair;
                }
                break;
            }
            first_time = false;
        }
    }
    else
    {
        if ((suspect = (heshEntry_t *)malloc(sizeof(heshEntry_t))) != NULL)
        {
            if ((suspect->pair.key = malloc(strlen(key)+1)) != NULL)
                strcpy(suspect->pair.key, key);
            else {
                free(suspect);
                return NULL;
            }
            suspect->pair.value = 0;
            suspect->next = NULL;
            t->size++;
            t->entries[hash] = suspect;
            return &suspect->pair;
        }
    }
    return NULL;
}
