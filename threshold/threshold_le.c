#include "threshold_le.h"


METHOD_INIT_IMPL(M_threshold_le, th)
{
}

METHOD_DEINIT_IMPL(M_threshold_le, th)
{
}

METHOD_CALC_IMPL(M_threshold_le, th)
{
    th->out_value = (th->in_value <= th->p_threshold) ? FLAG_ACTIVE : FLAG_NONE;
}
