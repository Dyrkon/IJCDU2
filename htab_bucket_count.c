// htab_bucket_count.c
// Řešení IJC-DU2, příklad b), 19.4.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Vrací velikost tabuky

#include "htab.h"
#include "htab_priv.h"

size_t htab_bucket_count(const htab_t * t)
{
    return t->arr_size;
}
