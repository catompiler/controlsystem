#include "ramp.h"
#include "utils/utils.h"



METHOD_INIT_IMPL(M_ramp, ramp)
{
    IDLE((*ramp));
}

METHOD_DEINIT_IMPL(M_ramp, ramp)
{
}

METHOD_CALC_IMPL(M_ramp, ramp)
{
    if(ramp->control & CONTROL_RESET){
        ramp->out_value = 0;
        return;
    }

    iql_t tgt_val;
    iql_t cur_val;
    iq24_t min_val;
    iq24_t max_val;
    iql_t dval;

    tgt_val = ramp->in_value;
    cur_val = ramp->out_value;
    min_val = ramp->p_min;
    max_val = ramp->p_max;

    dval = ramp->m_dv_Ts;

    if(cur_val < tgt_val){
        cur_val = iq24_add_sat(cur_val, dval);
        if(cur_val > tgt_val){
            cur_val = tgt_val;
        }
    }else if(cur_val > tgt_val){
        cur_val = iq24_sub_sat(cur_val, dval);
        if(cur_val < tgt_val){
            cur_val = tgt_val;
        }
    }

    ramp->out_value = CLAMP(cur_val, min_val, max_val);
}

METHOD_IDLE_IMPL(M_ramp, ramp)
{
    if(ramp->p_time == 0){
        ramp->m_dv_Ts = IQ24_MAX;
    }else{
        ramp->m_dv_Ts = iq24_sat(iq15_divl(ramp->r_Ts, ramp->p_time));
    }
}
