#include "htab.h"
#include "htab_priv.h"

void free_entry(heshEntry_t *entry)
{
    if (entry->next == NULL)
    {
        free(entry);
        return;
    }
    else
    {
        free_entry(entry->next);
        free(entry);
    }
}

void htab_clear(htab_t * t)
{
    for (size_t i = 0; i < t->arr_size; ++i)
    {
        if (t->entries[i] != NULL)
            free_entry(t->entries[i]);
    }
}
