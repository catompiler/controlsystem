#include "threshold.h"


METHOD_INIT_IMPL(M_threshold, th)
{
}

METHOD_DEINIT_IMPL(M_threshold, th)
{
}

METHOD_CALC_IMPL(M_threshold, th)
{
    if(th->in_value < th->p_lower){

        th->out_value = THRESHOLD_UNDER;

    }else if(th->in_value > th->p_upper){

        th->out_value = THRESHOLD_OVER;

    }else{

        th->out_value = THRESHOLD_WITHIN;

    }
}
