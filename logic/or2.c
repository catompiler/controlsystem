#include "or2.h"


METHOD_INIT_IMPL(M_or2, or)
{
}

METHOD_DEINIT_IMPL(M_or2, or)
{
}

METHOD_CALC_IMPL(M_or2, or)
{
    flag_t in0, in1;
    flag_t res;

    in0 = or->in_value[0];
    in1 = or->in_value[1];

    res = (in0 | in1) & FLAG_ACTIVE;

    or->out_value = res;
}
