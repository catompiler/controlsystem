#include "or2_mask.h"


METHOD_INIT_IMPL(M_or2_mask, om)
{
}

METHOD_DEINIT_IMPL(M_or2_mask, om)
{
}

METHOD_CALC_IMPL(M_or2_mask, om)
{
    flag_t in0, in1;
    flag_t m0, m1;
    flag_t res;

    in0 = om->in_value[0];
    in1 = om->in_value[1];

    m0 = om->r_mask[0];
    m1 = om->r_mask[1];

    res = (in0 & m0) | (in1 & m1);

    om->out_value = res;
}
