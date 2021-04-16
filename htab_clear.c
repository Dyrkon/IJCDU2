#include "htab.h"
#include "htab_priv.h"

void htab_clear(htab_t * t)
{
    heshEntry_t *to_clear = NULL;
    heshEntry_t *next = NULL;

    // TODO(revisit the t->size decrementing)
    for (size_t i = 0; i < t->arr_size; ++i)
    {
        if ((to_clear = t->entries[i]) != NULL)
        {
            while(true)
            {
                if (to_clear->next == NULL)
                {
                    free(to_clear->pair.key);
                    free(to_clear);
                    t->entries[i] = NULL;
                    break;
                }
                else
                {
                    next = to_clear->next;
                    free(to_clear->pair.key);
                    free(to_clear);
                    to_clear = next;
                }
            }
        }
    }
    t->size = 0;
}
