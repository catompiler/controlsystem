#include "valid_range3.h"


METHOD_INIT_IMPL(M_valid_range3, vr)
{
}

METHOD_DEINIT_IMPL(M_valid_range3, vr)
{
}

static int32_t valid_range3_check(M_valid_range3* vr, iql_t value)
{
    if(value < vr->p_min_value){
        return VALID_RANGE3_UNDER;
    }

    if(value > vr->p_max_value){
        return VALID_RANGE3_OVER;
    }

    return VALID_RANGE3_WITHIN;
}

METHOD_CALC_IMPL(M_valid_range3, vr)
{
    int32_t check_all_res = 0;
    int32_t check_res = 0;

    int i;
    for(i = 0; i < VALID_RANGE3_VALUES_COUNT; i ++){
        check_res = valid_range3_check(vr, vr->in_value[i]);
        vr->out_value[i] = check_res;

        if(check_res != VALID_RANGE3_WITHIN){
            check_all_res |= (1 << i);
        }
    }

    vr->out_value_all = check_all_res;
}
