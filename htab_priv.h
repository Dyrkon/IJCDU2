// htab_priv.c
// Řešení IJC-DU2, příklad b), 19.4.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Privátní hlavička se strukturamy hlaviček

#include "htab.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef IJCDU2_HTAB_T_DEF_H
#define IJCDU2_HTAB_T_DEF_H

// Položka tabulky
typedef struct heshEntry
{
    struct htab_pair pair;
    struct heshEntry *next;
}heshEntry_t;

struct htab
{
    size_t size;       // počet prvků v tabulce
    size_t arr_size;   // počet řádků tabulky
    heshEntry_t *entries[];
};

#endif //IJCDU2_HTAB_T_DEF_H
