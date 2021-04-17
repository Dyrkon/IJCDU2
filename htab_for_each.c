#include "htab.h"
#include "htab_priv.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data))
{
    heshEntry_t *entry = NULL;

    for (size_t i = 0; i < t->arr_size; ++i)
    {
        if ((entry = t->entries[i]) != NULL)
        {
            while(true)
            {
                if (entry->next == NULL)
                {
                    (*f)(&entry->pair);
                    break;
                }
                else
                {
                    (*f)(&entry->pair);
                    entry = entry->next;
                }
            }
        }
    }
}
