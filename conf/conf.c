#include "conf/conf.h"
#include "utils/utils.h"


// Минимумы и максимумы.
// U.
#define U_MIN IQ15(1)
#define U_MAX_INT 1000
#define U_MAX IQ15(U_MAX_INT)
// I.
#define I_MIN IQ15(1)
#define I_MAX_INT 10000
#define I_MAX IQ15(I_MAX_INT)
// P.
#define P_MIN IQ7(1)
#define P_MAX IQ7(U_MAX_INT * I_MAX_INT)
// f.
#define f_MIN_INT 1
#define f_MIN IQ15(f_MIN_INT)
#define f_MAX_INT 400
#define f_MAX IQ15(f_MAX_INT)


static status_t recalc_values(M_conf* conf)
{
    status_t res_status = STATUS_READY;

    int32_t tmp;

    // U.
    if(!iqn_in_range(conf->p_U_nom, U_MIN, U_MAX)){
        res_status = STATUS_ERROR;
        conf->r_U_base = CLAMP(conf->p_U_nom, U_MIN, U_MAX);
    }else{
        conf->r_U_base = conf->p_U_nom;
    }
    conf->r_U_base_inv = iq15_inv24(conf->r_U_base);

    // I.
    if(!iqn_in_range(conf->p_I_nom, I_MIN, I_MAX)){
        res_status = STATUS_ERROR;
        conf->r_I_base = CLAMP(conf->p_I_nom, I_MIN, I_MAX);
    }else{
        conf->r_I_base = conf->p_I_nom;
    }
    conf->r_I_base_inv = iq15_inv24(conf->r_I_base);

    // f.
    if(!iqn_in_range(conf->p_f_nom, f_MIN, f_MAX)){
        res_status = STATUS_ERROR;
        conf->r_f_base = CLAMP(conf->p_f_nom, f_MIN, f_MAX);
    }else{
        conf->r_f_base = conf->p_f_nom;
    }
    conf->r_f_base_inv = iq15_inv24(conf->r_f_base);

    // P.
    // P_base = U_base * I_base.
    iq7_t P_base = liqn_to_m(iq15_mull(conf->r_U_base, conf->r_I_base), 15, 7);
    if(!iqn_in_range(P_base, P_MIN, P_MAX)){
        res_status = STATUS_ERROR;
        conf->r_P_base = CLAMP(P_base, P_MIN, P_MAX);
    }else{
        conf->r_P_base = P_base;
    }
    conf->r_P_base_inv = iq7_inv24(conf->r_P_base);

    // w.
    // w_base = f_base * 2*pi.
    conf->r_w_base = iq15_mul(conf->p_f_nom, IQ15_2PI);
    conf->r_w_base_inv = iq15_inv24(conf->r_w_base);

    // t.
    // t_base = 1 / w_base.
    conf->r_t_base = conf->r_w_base_inv;//iq15_inv24(conf->r_w_base);
    conf->r_t_base_inv = conf->r_w_base;//iq24_inv15(conf->r_t_base);

    // M.
    // M_base = P_base / w_base = P_base * t_base.
    // IQ(15) = IQ(7 + 24 - 7) => IQ(15)
    conf->r_M_base = liqn_to_m(iq7_mull(conf->r_P_base, conf->r_t_base), 24, 15);
    conf->r_M_base_inv = iq15_inv24(conf->r_M_base);

    // J.
    // J_base = M_base / (w_base^2) = M_base * (t_base ^ 2).
    // IQ24 = IQ(15 + 24 - 15).
    tmp = iq15_mul(conf->r_M_base, conf->r_t_base);
    tmp = iq24_mul(tmp, conf->r_t_base);
    conf->r_J_base = tmp;
    conf->r_J_base_inv = iq24_inv7(conf->r_J_base);

    // Psi.
    // Psi_base = U_base / w_base == U_base * t_base.
    // IQ24 = IQ(15 + 24 - 15).
    conf->r_Psi_base = iq15_mul(conf->r_U_base, conf->r_t_base);
    conf->r_Psi_base_inv = iq24_inv(conf->r_Psi_base);

    // R.
    // R_base = U_base / I_base.
    // IQ24 = IQ(15 + 24 - 15).
    conf->r_R_base = iq24_div(conf->r_U_base, conf->r_I_base);
    conf->r_R_base_inv = iq24_inv(conf->r_R_base);

    // L.
    // L_base = R_base / w_base == R_base * t_base.
    conf->r_L_base = iq24_mul(conf->r_R_base, conf->r_t_base);
    conf->r_L_base_inv = iq24_inv15(conf->r_L_base);

    // C.
    // C_base = 1/(R_base * w_base) == t_base / R_base.
    conf->r_C_base = iq24_div(conf->r_t_base, conf->r_R_base);
    conf->r_C_base_inv = iq24_inv15(conf->r_C_base);

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
