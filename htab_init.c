#include "htab.h"
#include "htab_priv.h"

htab_t *htab_init(size_t n)
{
    size_t size_to_alloc = 0;
    htab_t *tab;

    size_to_alloc += sizeof(htab_t);
    size_to_alloc += sizeof(heshEntry_t*) * n;

    if ((tab = malloc(size_to_alloc)) == NULL)
        return NULL;

    tab->arr_size = n;
    tab->size = 0;

    for (size_t i = 0; i < n; ++i)
        tab->entries[i] = NULL;

    return tab;
}
