#include "htab.h"
#include "htab_priv.h"

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key)
{
    size_t hash = (htab_hash_function(key) % t->arr_size);
    if (hash != 0)
        printf("%zu", hash);
    int val = 0;
    heshEntry_t *suspect = t->entries[hash];
    printf("%d", t->size);
    printf("%d", t->arr_size);

    if (suspect != NULL)
    {
        for (;suspect->next != NULL; suspect = t->entries[hash]->next)
        {
            if (!strcmp(suspect->pair.key,key))
                return &suspect->pair;
            val++;
        }
    }
    else
    {
        if ((suspect = malloc(sizeof(heshEntry_t))) != NULL)
        {
            if ((suspect->pair.key = malloc(strlen(key))) != NULL)
                strcpy(suspect->pair.key, key);
            suspect->pair.value = val;
            return &suspect->pair;
        }
        else
            return NULL;
    }


    if ((suspect->next = malloc(sizeof(heshEntry_t))) != NULL)
    {
        suspect->next->next = NULL;
        if ((suspect->next->pair.key = malloc(strlen(key))) != NULL)
            strcpy(suspect->next->pair.key, key);
        suspect->pair.value = val;
        return &suspect->pair;
    }
    return NULL;
}
