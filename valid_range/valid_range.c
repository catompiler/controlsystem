#include "valid_range.h"


METHOD_INIT_IMPL(M_valid_range, vr)
{
}

METHOD_DEINIT_IMPL(M_valid_range, vr)
{
}

static int32_t valid_range_check(M_valid_range* vr, iql_t value)
{
    if(value < vr->p_min_value){
        return VALID_RANGE_UNDER;
    }

    if(value > vr->p_max_value){
        return VALID_RANGE_OVER;
    }

    return VALID_RANGE_WITHIN;
}

METHOD_CALC_IMPL(M_valid_range, vr)
{
    vr->out_value = valid_range_check(vr, vr->in_value);
    vr->status = STATUS_VALID;
}
