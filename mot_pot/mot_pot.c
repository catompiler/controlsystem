#include "mot_pot.h"
#include "utils/utils.h"



METHOD_INIT_IMPL(M_mot_pot, pot)
{
}

METHOD_DEINIT_IMPL(M_mot_pot, pot)
{
}

METHOD_CALC_IMPL(M_mot_pot, pot)
{
    if(pot->control & CONTROL_RESET){
        pot->r_value = 0;
        return;
    }

    flag_t dec, inc;
    iq24_t cur_val;
    iq24_t min_val;
    iq24_t max_val;
    iq24_t dval;

    dec = pot->in_dec;
    inc = pot->in_inc;

    cur_val = pot->r_value;
    min_val = pot->p_min;
    max_val = pot->p_max;
    dval = pot->m_dv_Ts;

    if(inc == FLAG_ACTIVE){
        cur_val = iq24_add_sat(cur_val, dval);
    }else if(dec == FLAG_ACTIVE){
        cur_val = iq24_sub_sat(cur_val, dval);
    }

    pot->r_value = CLAMP(cur_val, min_val, max_val);
}

METHOD_IDLE_IMPL(M_mot_pot, pot)
{
    if(pot->p_time == 0){
        pot->m_dv_Ts = IQ24_MAX;
    }else{
        pot->m_dv_Ts = iq24_sat(iq15_divl(pot->r_Ts, pot->p_time));
    }
}
