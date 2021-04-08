#include "htab.h"
#include "htab_priv.h"

size_t htab_bucket_count(const htab_t * t)
{
    return t->arr_size;
}
