#include "and1_mask.h"


METHOD_INIT_IMPL(M_and1_mask, am)
{
}

METHOD_DEINIT_IMPL(M_and1_mask, am)
{
}

METHOD_CALC_IMPL(M_and1_mask, am)
{
    flag_t in0;
    flag_t m0;
    flag_t res;

    in0 = am->in_value[0];

    m0 = am->p_mask[0];

    res = in0 & m0;

    am->out_value = res;
}
