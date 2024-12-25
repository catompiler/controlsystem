#include "conf.h"
#include "utils/utils.h"



static status_t recalc_values(M_conf* conf)
{
    status_t res_status = STATUS_READY;

    // U.
    if(!iqn_in_range(conf->p_U_nom, CONF_U_NOM_MIN, CONF_U_NOM_MAX)){
        res_status = STATUS_ERROR;
        conf->r_U_base = CLAMP(conf->p_U_nom, CONF_U_NOM_MIN, CONF_U_NOM_MAX);
    }else{
        conf->r_U_base = conf->p_U_nom;
    }
    conf->r_U_base_inv = iq15_inv24(conf->r_U_base);

    // I.
    if(!iqn_in_range(conf->p_I_nom, CONF_I_NOM_MIN, CONF_I_NOM_MAX)){
        res_status = STATUS_ERROR;
        conf->r_I_base = CLAMP(conf->p_I_nom, CONF_I_NOM_MIN, CONF_I_NOM_MAX);
    }else{
        conf->r_I_base = conf->p_I_nom;
    }
    conf->r_I_base_inv = iq15_inv24(conf->r_I_base);

    // f.
    if(!iqn_in_range(conf->p_f_nom, CONF_f_NOM_MIN, CONF_f_NOM_MAX)){
        res_status = STATUS_ERROR;
        conf->r_f_base = CLAMP(conf->p_f_nom, CONF_f_NOM_MIN, CONF_f_NOM_MAX);
    }else{
        conf->r_f_base = conf->p_f_nom;
    }
    conf->r_f_base_inv = iq15_inv24(conf->r_f_base);

    // P.
    // P_base = U_base * I_base.
    conf->r_P_base = iq7_sat(liqn_to_m(iq15_mull(conf->r_U_base, conf->r_I_base), 15, 7));
    conf->r_P_base_inv = iq7_inv24(conf->r_P_base);

    return res_status;
}


METHOD_INIT_IMPL(M_conf, conf)
{
    IDLE((*conf));
}

METHOD_DEINIT_IMPL(M_conf, conf)
{
}

METHOD_IDLE_IMPL(M_conf, conf)
{
    status_t status = recalc_values(conf);

    if(status == STATUS_READY){
        conf->warnings = CONF_WARNING_NONE;
        conf->status = STATUS_NONE;
    }else{
        conf->warnings = CONF_WARNING_INVALID_PARAMS;
        conf->status = STATUS_WARNING;
    }
}
