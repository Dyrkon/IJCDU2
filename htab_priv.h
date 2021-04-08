#include "htab.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef IJCDU2_HTAB_T_DEF_H
#define IJCDU2_HTAB_T_DEF_H

struct htab
{
    size_t size;       // počet prvků v tabulce
    size_t arr_size;   // počet řádků tabulky
    heshEntry_t *entries[];
};

#endif //IJCDU2_HTAB_T_DEF_H
