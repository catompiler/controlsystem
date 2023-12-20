#include "limit.h"
#include "utils/utils.h"



METHOD_INIT_IMPL(M_limit, lim)
{
}

METHOD_DEINIT_IMPL(M_limit, lim)
{
}

METHOD_CALC_IMPL(M_limit, lim)
{
    iql_t val = lim->in_value;

    iql_t min_val = lim->p_min_value;
    iql_t max_val = lim->p_max_value;

    iql_t res = CLAMP(val, min_val, max_val);

    lim->out_value = res;
}
