#include "htab.h"
#include "htab_priv.h"

void for_row(heshEntry_t *entry, void (*f)(htab_pair_t *data))
{
    if (entry->next == NULL)
    {
        f(&entry->pair);
        return;
    }
    else
    {
        for_row(entry->next, f);
        f(&entry->pair);
    }
}

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data))
{
    for (size_t i = 0; i < t->arr_size; i++)
    {
        for_row(t->entries[i], f);
    }
}
