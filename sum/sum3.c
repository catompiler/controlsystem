#include "sum3.h"



METHOD_INIT_IMPL(M_sum3, sum)
{
}

METHOD_DEINIT_IMPL(M_sum3, sum)
{
}

METHOD_CALC_IMPL(M_sum3, sum)
{
    iq24_t a = sum->in_value[0];
    iq24_t b = sum->in_value[1];
    iq24_t c = sum->in_value[2];

    iq24_t res = iq24_add_sat(a, b);
            res = iq24_add_sat(res, c);

    sum->out_value = res;
}
