#include "conf/conf.h"



static status_t recalc_values(M_conf* conf)
{
    status_t status = STATUS_READY;

    iq24_t res;
    liq24_t resl;

    // 1/Unom.
    if(conf->p_U_nom != 0){
        // IQ(33) = IQ(24+24) - IQ(15).
        resl = iq24_divl(IQ24(1), conf->p_U_nom);
        res = IQ_N_TO_M(resl, 33, 24);
        if(res != 0){
            conf->r_inv_U_nom = res;
        }else{
            status = STATUS_ERROR;
        }
    }else{
        status = STATUS_ERROR;
    }

    // 1/Inom.
    if(conf->p_I_nom != 0){
        // IQ(33) = IQ(24+24) - IQ(15).
        resl = iq24_divl(IQ24(1), conf->p_I_nom);
        res = IQ_N_TO_M(resl, 33, 24);
        if(res != 0){
            conf->r_inv_I_nom = res;
        }else{
            status = STATUS_ERROR;
        }
    }else{
        status = STATUS_ERROR;
    }

    return status;
}


METHOD_INIT_IMPL(M_conf, conf)
{
    conf->status = STATUS_READY;

    status_t status = recalc_values(conf);

    if(status & STATUS_READY){
        conf->status |= STATUS_VALID;
    }
}

METHOD_DEINIT_IMPL(M_conf, conf)
{
    conf->status = STATUS_NONE;
}

METHOD_IDLE_IMPL(M_conf, conf)
{
    status_t status = recalc_values(conf);

    if(status & STATUS_READY){
        conf->status |= STATUS_VALID;
    }else if(status & STATUS_ERROR){
        conf->status &= ~STATUS_VALID;
    }
}
