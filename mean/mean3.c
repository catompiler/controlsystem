#include "mean3.h"
#include "iqmath/iqutils.h"



METHOD_INIT_IMPL(M_mean3, mean)
{
}

METHOD_DEINIT_IMPL(M_mean3, mean)
{
}

METHOD_CALC_IMPL(M_mean3, mean)
{
    iql_t a = mean->in_value[0];
    iql_t b = mean->in_value[1];
    iql_t c = mean->in_value[2];

    iql_t res = iql_mean3(a, b, c);

    mean->out_value = res;
}
