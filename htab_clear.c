#include "htab.h"
#include "htab_priv.h"
/*
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
        free(entry->pair.key);
        free(entry);
    }
}*/

// TODO
void htab_clear(htab_t * t)
{
    heshEntry_t *to_clear = NULL;
    for (size_t i = 0; i < t->arr_size; ++i)
    {
        if ((to_clear = t->entries[i]) != NULL)
        {
            while (t->entries[i] != NULL)
            {
                to_clear = t->entries[i];
                while (true)
                {
                    if (to_clear->next == NULL)
                    {
                        free(to_clear->pair.key);
                        free(to_clear);
                        t->entries[i] = NULL;
                        t->size--;
                        break;
                    }
                    else if (to_clear->next->next == NULL)
                    {
                        free(to_clear->next->pair.key);
                        free(to_clear->next);
                        t->entries[i]->next = NULL;
                        t->size--;
                        break;
                    }
                    else
                        to_clear = to_clear->next;
                }
            }

        }
    }
}
