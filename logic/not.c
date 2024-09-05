#include "not.h"


METHOD_INIT_IMPL(M_not, not)
{
}

METHOD_DEINIT_IMPL(M_not, not)
{
}

METHOD_CALC_IMPL(M_not, not)
{
    flag_t in;
    flag_t res;

    in = not->in_value;

    res = (~in) & FLAG_ACTIVE;

    not->out_value = res;
}
