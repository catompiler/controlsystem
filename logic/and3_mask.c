#include "and3_mask.h"


METHOD_INIT_IMPL(M_and3_mask, am)
{
}

METHOD_DEINIT_IMPL(M_and3_mask, am)
{
}

METHOD_CALC_IMPL(M_and3_mask, am)
{
    flag_t in0, in1, in2;
    flag_t m0, m1, m2;
    flag_t en;
    flag_t res;

    in0 = am->in_value[0];
    in1 = am->in_value[1];
    in2 = am->in_value[2];

    m0 = am->p_mask[0];
    m1 = am->p_mask[1];
    m2 = am->p_mask[2];

    en = m0 | m1 | m2;

    res = en & (in0 | ~m0) & (in1 | ~m1) & (in2 | ~m2);

    am->out_value = res;
}
