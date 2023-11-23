#include "mean2.h"
#include "iqmath/iqutils.h"



METHOD_INIT_IMPL(M_mean2, mean)
{
}

METHOD_DEINIT_IMPL(M_mean2, mean)
{
}

METHOD_CALC_IMPL(M_mean2, mean)
{
    iql_t a = mean->in_value[0];
    iql_t b = mean->in_value[1];

    iql_t res = iql_mean2(a, b);

    mean->out_value = res;
}
