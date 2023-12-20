#include "motor.h"
#include "utils/utils.h"
#include "modules/modules.h"



static status_t recalc_values_rotor(M_motor* mot)
{
    status_t res_status = STATUS_READY;

    int32_t tmp;

    // U.
    if(!iqn_in_range(mot->p_U_nom, MOTOR_U_NOM_MIN, MOTOR_U_NOM_MAX)){
        res_status = STATUS_ERROR;
        mot->r_U_base = CLAMP(mot->p_U_nom, MOTOR_U_NOM_MIN, MOTOR_U_NOM_MAX);
    }else{
        mot->r_U_base = mot->p_U_nom;
    }
    mot->r_U_base_inv = iq15_inv24(mot->r_U_base);

    // I.
    if(!iqn_in_range(mot->p_I_nom, MOTOR_I_NOM_MIN, MOTOR_I_NOM_MAX)){
        res_status = STATUS_ERROR;
        mot->r_I_base = CLAMP(mot->p_I_nom, MOTOR_I_NOM_MIN, MOTOR_I_NOM_MAX);
    }else{
        mot->r_I_base = mot->p_I_nom;
    }
    mot->r_I_base_inv = iq15_inv24(mot->r_I_base);

    // f.
    if(!iqn_in_range(mot->p_f_nom, MOTOR_f_NOM_MIN, MOTOR_f_NOM_MAX)){
        res_status = STATUS_ERROR;
        mot->r_f_base = CLAMP(mot->p_f_nom, MOTOR_f_NOM_MIN, MOTOR_f_NOM_MAX);
    }else{
        mot->r_f_base = mot->p_f_nom;
    }
    mot->r_f_base_inv = iq15_inv24(mot->r_f_base);

    // P.
    // P_base = U_base * I_base.
    mot->r_P_base = iq7_sat(liqn_to_m(iq15_mull(mot->r_U_base, mot->r_I_base), 15, 7));
    mot->r_P_base_inv = iq7_inv24(mot->r_P_base);

    // w.
    // w_base = f_base * 2*pi.
    mot->r_w_base = iq15_mul(mot->p_f_nom, IQ15_2PI);
    mot->r_w_base_inv = iq15_inv24(mot->r_w_base);

    // t.
    // t_base = 1 / w_base.
    mot->r_t_base = mot->r_w_base_inv;//iq15_inv24(conf->r_w_base);
    mot->r_t_base_inv = mot->r_w_base;//iq24_inv15(conf->r_t_base);

    // M.
    // M_base = P_base / w_base = P_base * t_base.
    // IQ(15) = IQ(7 + 24 - 7) => IQ(15)
    mot->r_M_base = liqn_to_m(iq7_mull(mot->r_P_base, mot->r_t_base), 24, 15);
    mot->r_M_base_inv = iq15_inv24(mot->r_M_base);

    // J.
    // J_base = M_base / (w_base^2) = M_base * (t_base ^ 2).
    // IQ24 = IQ(15 + 24 - 15).
    tmp = iq15_mul(mot->r_M_base, mot->r_t_base);
    tmp = iq24_mul(tmp, mot->r_t_base);
    mot->r_J_base = tmp;
    mot->r_J_base_inv = iq24_inv7(mot->r_J_base);

    // Psi.
    // Psi_base = U_base / w_base == U_base * t_base.
    // IQ24 = IQ(15 + 24 - 15).
    mot->r_Psi_base = iq15_mul(mot->r_U_base, mot->r_t_base);
    mot->r_Psi_base_inv = iq24_inv(mot->r_Psi_base);

    // R.
    // R_base = U_base / I_base.
    // IQ24 = IQ(15 + 24 - 15).
    mot->r_R_base = iq24_div(mot->r_U_base, mot->r_I_base);
    mot->r_R_base_inv = iq24_inv(mot->r_R_base);

    // L.
    // L_base = R_base / w_base == R_base * t_base.
    mot->r_L_base = iq24_mul(mot->r_R_base, mot->r_t_base);
    mot->r_L_base_inv = iq24_inv15(mot->r_L_base);

    // C.
    // C_base = 1/(R_base * w_base) == t_base / R_base.
    mot->r_C_base = iq24_div(mot->r_t_base, mot->r_R_base);
    mot->r_C_base_inv = iq24_inv15(mot->r_C_base);

    // k U(Mains) -> U(Mot).
    mot->r_k_U_mains_to_mot = iq15_mul(conf.r_U_base, mot->r_U_base_inv);
    // k I(Mains) -> I(Mot).
    mot->r_k_I_mains_to_mot = iq15_mul(conf.r_I_base, mot->r_I_base_inv);
    // k I(Mot) -> I(Mains).
    mot->r_k_I_mot_to_mains = iq15_mul(mot->r_I_base, conf.r_I_base_inv);

    return res_status;
}

static status_t recalc_values_stator(M_motor* mot)
{
    status_t res_status = STATUS_READY;

    // U.
    if(!iqn_in_range(mot->p_s_U_nom, MOTOR_S_U_NOM_MIN, MOTOR_S_U_NOM_MAX)){
        res_status = STATUS_ERROR;
        mot->r_s_U_base = CLAMP(mot->p_s_U_nom, MOTOR_S_U_NOM_MIN, MOTOR_S_U_NOM_MAX);
    }else{
        mot->r_s_U_base = mot->p_s_U_nom;
    }
    mot->r_s_U_base_inv = iq15_inv24(mot->r_s_U_base);

    // I.
    if(!iqn_in_range(mot->p_s_I_nom, MOTOR_S_I_NOM_MIN, MOTOR_S_I_NOM_MAX)){
        res_status = STATUS_ERROR;
        mot->r_s_I_base = CLAMP(mot->p_s_I_nom, MOTOR_S_I_NOM_MIN, MOTOR_S_I_NOM_MAX);
    }else{
        mot->r_s_I_base = mot->p_s_I_nom;
    }
    mot->r_s_I_base_inv = iq15_inv24(mot->r_s_I_base);

    // P.
    // P_base = U_base * I_base.
    mot->r_s_P_base = iq7_sat(liqn_to_m(iq15_mull(mot->r_s_U_base, mot->r_s_I_base), 15, 7));
    mot->r_s_P_base_inv = iq7_inv24(mot->r_s_P_base);

    return res_status;
}


static status_t recalc_values(M_motor* mot)
{
    status_t res_status = STATUS_READY;

    res_status |= recalc_values_rotor(mot);
    res_status |= recalc_values_stator(mot);

    return res_status;
}


METHOD_INIT_IMPL(M_motor, mot)
{
    IDLE((*mot));
}

METHOD_DEINIT_IMPL(M_motor, mot)
{
}

METHOD_CALC_IMPL(M_motor, mot)
{
}

METHOD_IDLE_IMPL(M_motor, mot)
{
    status_t status = recalc_values(mot);

    if(status == STATUS_READY){
        mot->warnings = MOTOR_WARNING_NONE;
        mot->status = STATUS_NONE;
    }else{
        mot->warnings = MOTOR_WARNING_INVALID_PARAMS;
        mot->status = STATUS_WARNING;
    }
}
