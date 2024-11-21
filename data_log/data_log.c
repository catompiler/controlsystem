#include "data_log.h"
#include "reg/regs.h"


static status_t recalc_values(M_data_log* dlog)
{
    status_t res_status = STATUS_READY;

    data_log_ch_param_t* ch_par;
    data_log_ch_data_t* ch_dat;
    reg_t* reg;

    int i;
    for(i = 0; i < DATA_LOG_CH_COUNT; i ++){
        ch_par = &dlog->p_ch[i];
        ch_dat = &dlog->r_ch[i];

        if(ch_par->enabled && (reg = regs_find(ch_par->reg_id))){
            ch_dat->reg = reg;//reg_data(reg);
            ch_dat->base_reg = regs_find(reg->base_id);
        }else{
            ch_dat->reg = NULL;
        }
    }

    return res_status;
}


METHOD_INIT_IMPL(M_data_log, dlog)
{
    dlog->r_count = 0;
    dlog->r_get_index = 0;
    dlog->r_put_index = 0;

    IDLE((*dlog));
}

METHOD_DEINIT_IMPL(M_data_log, dlog)
{
}

METHOD_CALC_IMPL(M_data_log, dlog)
{
    if(!(dlog->control & CONTROL_ENABLE)) return;

    data_log_ch_param_t* ch_par;
    data_log_ch_data_t* ch_dat;
    data_log_value_t val;

    int i;
    for(i = 0; i < DATA_LOG_CH_COUNT; i ++){
        ch_par = &dlog->p_ch[i];
        ch_dat = &dlog->r_ch[i];

        if(ch_par->enabled && ch_dat->reg != NULL && reg_data(ch_dat->reg) != NULL){
            val = (data_log_value_t)reg_valuel(ch_dat->reg);
        }else{
            val = 0;
        }

        ch_dat->data[dlog->r_put_index] = val;
    }

    uint32_t count = dlog->r_count;
    uint32_t put_index = dlog->r_put_index;
    uint32_t get_index = dlog->r_get_index;

    if(count < DATA_LOG_CH_LEN){
        count ++;
    }

    if(count == DATA_LOG_CH_LEN){
        get_index ++;
        if(get_index >= DATA_LOG_CH_LEN){
            get_index = 0;
        }
    }

    put_index ++;
    if(put_index >= DATA_LOG_CH_LEN){
        put_index = 0;
    }

    dlog->r_count = count;
    dlog->r_get_index = get_index;
    dlog->r_put_index = put_index;
}

METHOD_IDLE_IMPL(M_data_log, dlog)
{
    recalc_values(dlog);
}
