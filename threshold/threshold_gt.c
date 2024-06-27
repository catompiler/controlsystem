#include "threshold_gt.h"


METHOD_INIT_IMPL(M_threshold_gt, th)
{
}

METHOD_DEINIT_IMPL(M_threshold_gt, th)
{
}

METHOD_CALC_IMPL(M_threshold_gt, th)
{
    th->out_value = (th->in_value > th->p_threshold) ? FLAG_ACTIVE : FLAG_NONE;
}
