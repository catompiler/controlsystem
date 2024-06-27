#include "comp_le.h"


METHOD_INIT_IMPL(M_comp_le, cmp)
{
}

METHOD_DEINIT_IMPL(M_comp_le, cmp)
{
}

METHOD_CALC_IMPL(M_comp_le, cmp)
{
    cmp->out_value = (cmp->in_A <= cmp->in_B) ? FLAG_ACTIVE : FLAG_NONE;
}
