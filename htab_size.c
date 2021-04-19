// htab_size.c
// Řešení IJC-DU2, příklad b), 19.4.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Vrací počet záznamů v tabulce

#include "htab.h"
#include "htab_priv.h"

size_t htab_size(const htab_t * t)
{
    return t->size;
}
