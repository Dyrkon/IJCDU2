// htab_free.c
// Řešení IJC-DU2, příklad b), 19.4.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Vymaže celou tabulku a uvolní ji z paměti

#include "htab.h"
#include "htab_priv.h"

void htab_free(htab_t * t)
{
    htab_clear(t);
    free(t);
}
