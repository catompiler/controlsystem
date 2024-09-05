#include "and2.h"


METHOD_INIT_IMPL(M_and2, and)
{
}

METHOD_DEINIT_IMPL(M_and2, and)
{
}

METHOD_CALC_IMPL(M_and2, and)
{
    flag_t in0, in1;
    flag_t res;

    in0 = and->in_value[0];
    in1 = and->in_value[1];

    res = (in0 & in1) & FLAG_ACTIVE;

    and->out_value = res;
}
