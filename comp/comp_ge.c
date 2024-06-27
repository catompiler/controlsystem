#include "comp_ge.h"


METHOD_INIT_IMPL(M_comp_ge, cmp)
{
}

METHOD_DEINIT_IMPL(M_comp_ge, cmp)
{
}

METHOD_CALC_IMPL(M_comp_ge, cmp)
{
    cmp->out_value = (cmp->in_A >= cmp->in_B) ? FLAG_ACTIVE : FLAG_NONE;
}
