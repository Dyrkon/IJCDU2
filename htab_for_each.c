// htab_for_each.c
// Řešení IJC-DU2, příklad b), 19.4.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Aplikuje zadanou funkci na všechy položky v hashmapě

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
