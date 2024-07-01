#include "smotor_larionov.h"
#include "modules/modules.h"
#include "iqmath/iqmath.h"


//
// Модели.
//

//
// Модель СД.
//


static void smotor_model_recalc_stator_off_field_off(M_smotor_larionov* lrm)
{
    iq24_t Lrd = lrm->m_Lrd;
    iq24_t Lrq = lrm->m_Lrq;


    iq24_t id_denom_inv = iq24_div(IQ24(1.0), Lrd);
    iq24_t iq_denom_inv = iq24_div(IQ24(1.0), Lrq);


    lrm->m_id_denom_inv_sf_off = id_denom_inv;
    lrm->m_iq_denom_inv_sf_off = iq_denom_inv;
}


static void smotor_model_recalc_stator_off_field_on(M_smotor_larionov* lrm)
{
    iq24_t Lrd = lrm->m_Lrd;
    iq24_t Lrq = lrm->m_Lrq;
    iq24_t Lfd = lrm->m_Lfd;

    iq24_t Lmrfd = lrm->m_Lmrfd;


    iql_t val, tmp;

    // id_denom_inv = 1.0 / (Lmrfd^2-Lfd*Lrd);
    // Lmrfd^2
    val  = iq24_mul(Lmrfd, Lmrfd);
    // Lfd*Lrd
    tmp = iq24_mul(Lfd, Lrd);
    // Lmrfd^2-Lfd*Lrd
    val  = iq24_sub(val, tmp);
    // 1.0 / (Lmrfd^2-Lfd*Lrd)
    iq24_t id_denom_inv = iq24_div(IQ24(1.0), val);
    iq24_t iq_denom_inv = iq24_div(IQ24(1.0), Lrq);

    iq24_t k_ird_Psi_rd = -Lfd;
    iq24_t k_ird_Psi_fd = Lmrfd;

    iq24_t k_ifd_Psi_rd = Lmrfd;
    iq24_t k_ifd_Psi_fd = -Lrd;


    lrm->m_id_denom_inv_s_off = id_denom_inv;
    lrm->m_iq_denom_inv_s_off = iq_denom_inv;

    lrm->m_k_ird_Psi_rd_s_off = k_ird_Psi_rd;
    lrm->m_k_ird_Psi_fd_s_off = k_ird_Psi_fd;

    lrm->m_k_ifd_Psi_rd_s_off = k_ifd_Psi_rd;
    lrm->m_k_ifd_Psi_fd_s_off = k_ifd_Psi_fd;
}


static void smotor_model_recalc_stator_on_field_off(M_smotor_larionov* lrm){

    iq24_t Lsd = lrm->m_Lsd;
    iq24_t Lsq = lrm->m_Lsq;
    iq24_t Lrd = lrm->m_Lrd;
    iq24_t Lrq = lrm->m_Lrq;

    iq24_t Lmsrd = lrm->m_Lmsrd;
    iq24_t Lmsrq = lrm->m_Lmsrq;


    iql_t val, tmp;

    // id_denom_inv = 1.0 / (Lmsrd^2-Lrd*Lsd)
    // Lmsrd^2
    val = iq24_mul(Lmsrd, Lmsrd);
    // Lrd*Lsd
    tmp = iq24_mul(Lrd, Lsd);
    // Lmsrd^2-Lrd*Lsd
    val = iq24_sub(val, tmp);
    // 1.0 / (Lmsrd^2-Lrd*Lsd)
    iq24_t id_denom_inv = iq24_div(IQ24(1.0), val);

    // iq_denom_inv = 1.0 / (Lmsrq^2-Lrq*Lsq)
    // Lmsrq^2
    val = iq24_mul(Lmsrq, Lmsrq);
    // Lrq*Lsq
    tmp = iq24_mul(Lrq, Lsq);
    // Lmsrq^2-Lrq*Lsq
    val = iq24_sub(val, tmp);
    // 1.0 / (Lmsrq^2-Lrq*Lsq)
    iq24_t iq_denom_inv = iq24_div(IQ24(1.0), val);

    iq24_t k_isd_Psi_sd = -Lrd;
    iq24_t k_isd_Psi_rd = iq24_mul(Lmsrd, lrm->m_rfpu_k_Psi_rf2s);

    iq24_t k_isq_Psi_sq = -Lrq;
    iq24_t k_isq_Psi_rq = iq24_mul(Lmsrq, lrm->m_rfpu_k_Psi_rf2s);

    iq24_t k_ird_Psi_sd = iq24_mul(Lmsrd, lrm->m_rfpu_k_Psi_s2rf);
    iq24_t k_ird_Psi_rd = -Lsd;

    iq24_t k_irq_Psi_sq = iq24_mul(Lmsrq, lrm->m_rfpu_k_Psi_s2rf);
    iq24_t k_irq_Psi_rq = -Lsq;


    lrm->m_id_denom_inv_f_off = id_denom_inv;
    lrm->m_iq_denom_inv_f_off = iq_denom_inv;

    lrm->m_k_isd_Psi_sd_f_off = k_isd_Psi_sd;
    lrm->m_k_isd_Psi_rd_f_off = k_isd_Psi_rd;

    lrm->m_k_isq_Psi_sq_f_off = k_isq_Psi_sq;
    lrm->m_k_isq_Psi_rq_f_off = k_isq_Psi_rq;

    lrm->m_k_ird_Psi_sd_f_off = k_ird_Psi_sd;
    lrm->m_k_ird_Psi_rd_f_off = k_ird_Psi_rd;

    lrm->m_k_irq_Psi_sq_f_off = k_irq_Psi_sq;
    lrm->m_k_irq_Psi_rq_f_off = k_irq_Psi_rq;
}


static void smotor_model_recalc_stator_on_field_on(M_smotor_larionov* lrm){

    iq24_t Lsd = lrm->m_Lsd;
    iq24_t Lsq = lrm->m_Lsq;
    iq24_t Lrd = lrm->m_Lrd;
    iq24_t Lrq = lrm->m_Lrq;
    iq24_t Lfd = lrm->m_Lfd;

    iq24_t Lmsrd = lrm->m_Lmsrd;
    iq24_t Lmsrq = lrm->m_Lmsrq;
    iq24_t Lmsfd = lrm->m_Lmsfd;
    iq24_t Lmrfd = lrm->m_Lmrfd;


    iql_t val, tmp;

    // id_denom_inv = 1.0 / (Lfd*Lmsrd^2 - 2*Lmrfd*Lmsfd*Lmsrd + Lrd*Lmsfd^2 + Lsd*Lmrfd^2 - Lfd*Lrd*Lsd)
    // Lfd*Lmsrd^2
    val = iq24_mul(Lfd, Lmsrd);
    val = iq24_mul(val, Lmsrd);
    // 2*Lmrfd*Lmsfd*Lmsrd
    tmp = iq24_imul(Lmrfd, 2);
    tmp = iq24_mul(tmp, Lmsfd);
    tmp = iq24_mul(tmp, Lmsrd);
    // Lfd*Lmsrd^2 - 2*Lmrfd*Lmsfd*Lmsrd
    val = iq24_sub(val, tmp);
    // Lrd*Lmsfd^2
    tmp = iq24_mul(Lrd, Lmsfd);
    tmp = iq24_mul(tmp, Lmsfd);
    // Lfd*Lmsrd^2 - 2*Lmrfd*Lmsfd*Lmsrd + Lrd*Lmsfd^2
    val = iq24_add(val, tmp);
    // Lsd*Lmrfd^2
    tmp = iq24_mul(Lsd, Lmrfd);
    tmp = iq24_mul(tmp, Lmrfd);
    // Lfd*Lmsrd^2 - 2*Lmrfd*Lmsfd*Lmsrd + Lrd*Lmsfd^2 + Lsd*Lmrfd^2
    val = iq24_add(val, tmp);
    // Lfd*Lrd*Lsd
    tmp = iq24_mul(Lfd, Lrd);
    tmp = iq24_mul(tmp, Lsd);
    // Lfd*Lmsrd^2 - 2*Lmrfd*Lmsfd*Lmsrd + Lrd*Lmsfd^2 + Lsd*Lmrfd^2 - Lfd*Lrd*Lsd
    val = iq24_sub(val, tmp);
    // 1.0 / (Lfd*Lmsrd^2 - 2*Lmrfd*Lmsfd*Lmsrd + Lrd*Lmsfd^2 + Lsd*Lmrfd^2 - Lfd*Lrd*Lsd)
    iq24_t id_denom_inv = iq24_div(IQ24(1.0), val);

    // iq_denom_inv = 1.0 / (Lmsrq^2-Lrq*Lsq)
    // Lmsrq^2
    val = iq24_mul(Lmsrq, Lmsrq);
    // Lrq*Lsq
    tmp = iq24_mul(Lrq, Lsq);
    // Lmsrq^2-Lrq*Lsq
    val = iq24_sub(val, tmp);
    // 1.0 / (Lmsrq^2-Lrq*Lsq)
    iq24_t iq_denom_inv = iq24_div(IQ24(1.0), val);

    // k_isd_Psi_sd = Lmrfd^2-Lfd*Lrd
    // Lmrfd^2
    val = iq24_mul(Lmrfd, Lmrfd);
    // Lfd*Lrd
    tmp = iq24_mul(Lfd, Lrd);
    // Lmrfd^2-Lfd*Lrd
    val = iq24_sub(val, tmp);
    iq24_t k_isd_Psi_sd = val;

    // k_isd_Psi_rd = Lfd*Lmsrd-Lmrfd*Lmsfd
    // Lfd*Lmsrd
    val = iq24_mul(Lfd, Lmsrd);
    // Lmrfd*Lmsfd
    tmp = iq24_mul(Lmrfd, Lmsfd);
    // Lfd*Lmsrd-Lmrfd*Lmsfd
    val = iq24_sub(val, tmp);
    // Psi r -> s
    val = iq24_mul(val, lrm->m_rfpu_k_Psi_rf2s);
    iq24_t k_isd_Psi_rd = val;

    // k_isd_Psi_fd = Lrd*Lmsfd-Lmrfd*Lmsrd
    // Lrd*Lmsfd
    val = iq24_mul(Lrd, Lmsfd);
    // Lmrfd*Lmsrd
    tmp = iq24_mul(Lmrfd, Lmsrd);
    // Lrd*Lmsfd-Lmrfd*Lmsrd
    val = iq24_sub(val, tmp);
    // Psi f -> s
    val = iq24_mul(val, lrm->m_rfpu_k_Psi_rf2s);
    iq24_t k_isd_Psi_fd = val;

    iq24_t k_isq_Psi_sq = -Lrq;
    iq24_t k_isq_Psi_rq = iq24_mul(Lmsrq, lrm->m_rfpu_k_Psi_rf2s);

    // k_ird_Psi_sd = Lfd*Lmsrd-Lmrfd*Lmsfd
    // Lfd*Lmsrd
    val = iq24_mul(Lfd, Lmsrd);
    // Lmrfd*Lmsfd
    tmp = iq24_mul(Lmrfd, Lmsfd);
    // Lfd*Lmsrd-Lmrfd*Lmsfd
    val = iq24_sub(val, tmp);
    // Psi s -> r
    val = iq24_mul(val, lrm->m_rfpu_k_Psi_s2rf);
    iq24_t k_ird_Psi_sd = val;

    // k_ird_Psi_rd = Lmsfd^2-Lfd*Lsd
    // Lmsfd^2
    val = iq24_mul(Lmsfd, Lmsfd);
    // Lfd*Lsd
    tmp = iq24_mul(Lfd, Lsd);
    // Lmsfd^2-Lfd*Lsd
    val = iq24_sub(val, tmp);
    iq24_t k_ird_Psi_rd = val;

    // k_ird_Psi_fd = Lsd*Lmrfd-Lmsfd*Lmsrd
    // Lsd*Lmrfd
    val = iq24_mul(Lsd, Lmrfd);
    // Lmsfd*Lmsrd
    tmp = iq24_mul(Lmsfd, Lmsrd);
    // Lsd*Lmrfd-Lmsfd*Lmsrd
    val = iq24_sub(val, tmp);
    iq24_t k_ird_Psi_fd = val;

    iq24_t k_irq_Psi_sq = iq24_mul(Lmsrq, lrm->m_rfpu_k_Psi_s2rf);
    iq24_t k_irq_Psi_rq = -Lsq;

    // k_ifd_Psi_sd = Lrd*Lmsfd-Lmrfd*Lmsrd
    // Lrd*Lmsfd
    val = iq24_mul(Lrd, Lmsfd);
    // Lmrfd*Lmsrd
    tmp = iq24_mul(Lmrfd, Lmsrd);
    // Lrd*Lmsfd-Lmrfd*Lmsrd
    val = iq24_sub(val, tmp);
    // Psi s -> r
    val = iq24_mul(val, lrm->m_rfpu_k_Psi_s2rf);
    iq24_t k_ifd_Psi_sd = val;

    // k_ifd_Psi_rd = Lsd*Lmrfd-Lmsfd*Lmsrd
    // Lsd*Lmrfd
    val = iq24_mul(Lsd, Lmrfd);
    // Lmsfd*Lmsrd
    tmp = iq24_mul(Lmsfd, Lmsrd);
    // Lsd*Lmrfd-Lmsfd*Lmsrd
    val = iq24_sub(val, tmp);
    iq24_t k_ifd_Psi_rd = val;

    // k_ifd_Psi_fd = Lmsrd^2-Lrd*Lsd
    // Lmsrd^2
    val = iq24_mul(Lmsrd, Lmsrd);
    // Lrd*Lsd
    tmp = iq24_mul(Lrd, Lsd);
    // Lmsrd^2-Lrd*Lsd
    val = iq24_sub(val, tmp);
    iq24_t k_ifd_Psi_fd = val;


    lrm->m_id_denom_inv = id_denom_inv;
    lrm->m_iq_denom_inv = iq_denom_inv;

    lrm->m_k_isd_Psi_sd = k_isd_Psi_sd;
    lrm->m_k_isd_Psi_rd = k_isd_Psi_rd;
    lrm->m_k_isd_Psi_fd = k_isd_Psi_fd;

    lrm->m_k_isq_Psi_sq = k_isq_Psi_sq;
    lrm->m_k_isq_Psi_rq = k_isq_Psi_rq;

    lrm->m_k_ird_Psi_sd = k_ird_Psi_sd;
    lrm->m_k_ird_Psi_rd = k_ird_Psi_rd;
    lrm->m_k_ird_Psi_fd = k_ird_Psi_fd;

    lrm->m_k_irq_Psi_sq = k_irq_Psi_sq;
    lrm->m_k_irq_Psi_rq = k_irq_Psi_rq;

    lrm->m_k_ifd_Psi_sd = k_ifd_Psi_sd;
    lrm->m_k_ifd_Psi_rd = k_ifd_Psi_rd;
    lrm->m_k_ifd_Psi_fd = k_ifd_Psi_fd;
}

/*
 * Обновляет приведённую к статору систему единиц ротора.
 */
static void smotor_model_upodate_rotor_pu(M_smotor_larionov* lrm)
{
    // Базовый ток ротора - это такой ток,
    // который при синхронной скорости
    // индуцирует в обмотках отключенного статора
    // номинальное напряжение.

    iq15_t U_s_base = motor.r_s_U_base;
    iq15_t w_s_base = motor.r_w_base;
    iq15_t Lm = lrm->p_Lmsfd;

    iq15_t tmp = iq15_mul(w_s_base, Lm);
    iq15_t I_base = iq15_div(U_s_base, tmp);

    // Базовое напряжение - такое, что обеспечивает равенство
    // базовых индуктивностей (сопротивлений).
    iq15_t I_s_base = motor.r_s_I_base;
    tmp = iq15_div(U_s_base, I_s_base);
    iq15_t U_base = iq15_mul(tmp, I_base);

    // Коэффициенты преобразования в систему относительных единиц
    // ротора, приведённого к статору.
    lrm->m_rfpu_k_U_r = iq15_inv24(U_base);
    lrm->m_rfpu_k_I_r = iq15_inv24(I_base);
    lrm->m_rfpu_k_L_rs = motor.r_s_L_base_inv;
    lrm->m_rfpu_k_R_rs = motor.r_s_R_base_inv;

    // Коэффициенты преобразования из одной
    // системы относительных единиц в другую.
    lrm->m_rfpu_k_Psi_s2rf = iq15_div24(U_s_base, U_base);
    lrm->m_rfpu_k_Psi_rf2s = iq15_div24(U_base, U_s_base);
    lrm->m_rfpu_k_I_s2rf = iq15_div24(I_s_base, I_base);
    lrm->m_rfpu_k_I_rf2s = iq15_div24(I_base, I_s_base);
    lrm->m_rfpu_k_U_rf2mt = iq15_div24(U_base, motor.r_r_U_base);
    lrm->m_rfpu_k_I_rf2mt = iq15_div24(I_base, motor.r_r_I_base);
    lrm->m_rfpu_k_U_ms2rf = iq15_div24(conf.r_U_base, U_base);
    lrm->m_rfpu_k_I_rf2ms = iq15_div24(I_base, conf.r_I_base);
}

static status_t smotor_model_update(M_smotor_larionov* lrm)
{
    iql_t tmp;

    smotor_model_upodate_rotor_pu(lrm);


    lrm->m_Rs = iq15_mul(lrm->p_Rs, lrm->m_rfpu_k_R_rs);
    lrm->m_Rr = iq15_mul(lrm->p_Rr, lrm->m_rfpu_k_R_rs);
    lrm->m_Rf = iq15_mul(lrm->p_Rf, lrm->m_rfpu_k_R_rs);

    lrm->m_p  = (int32_t)lrm->p_p;
    lrm->m_p_inv = IQ24(1.0) / lrm->m_p;

    lrm->m_Mc = iq15_mul(lrm->p_Mc / lrm->m_p, motor.r_s_M_base_inv); //
    lrm->m_Kf = IQ_N_TO_M(lrm->p_Kf, 15, 24);


    // http://simenergy.ru/energy-system/primary-equipment/equation-rotor
    // Tj = J * w^2 / S.
    // S = Unom * Inom.
    // -----------------
    iq15_t Wnom = motor.r_w_base / lrm->m_p; //
    // J / Unom.
    tmp = iq15_div(lrm->p_J, motor.r_s_U_base);
    // (J / Unom) * w.
    tmp = iq15_mul(tmp, Wnom);
    // (J * w / Unom) * w.
    tmp = iq15_mul(tmp, Wnom);
    // (J * w^2 / Unom) / Inom.
    // IQ(15) = IQ(15 + 15 - 15). // IQ(24) = IQ(15 + 24 - 15).
    tmp = iq15_div(tmp, motor.r_s_I_base);
    // Tj* = Tj / t_base = Tj * t_base_inv = Tj * w_base.
    tmp = iq15_mul(tmp, motor.r_t_base_inv);
    // Tj.
    lrm->m_Tj_inv = iq15_inv24(tmp);


    lrm->m_Lsd = iq15_mul24(lrm->p_Lsd, lrm->m_rfpu_k_L_rs);
    lrm->m_Lsq = iq15_mul24(lrm->p_Lsq, lrm->m_rfpu_k_L_rs);
    lrm->m_Lrd = iq15_mul24(lrm->p_Lrd, lrm->m_rfpu_k_L_rs);
    lrm->m_Lrq = iq15_mul24(lrm->p_Lrq, lrm->m_rfpu_k_L_rs);
    lrm->m_Lfd = iq15_mul24(lrm->p_Lfd, lrm->m_rfpu_k_L_rs);

    lrm->m_Lmsrd = iq15_mul24(lrm->p_Lmsrd, lrm->m_rfpu_k_L_rs);
    lrm->m_Lmsrq = iq15_mul24(lrm->p_Lmsrq, lrm->m_rfpu_k_L_rs);
    lrm->m_Lmsfd = iq15_mul24(lrm->p_Lmsfd, lrm->m_rfpu_k_L_rs);
    lrm->m_Lmrfd = iq15_mul24(lrm->p_Lmrfd, lrm->m_rfpu_k_L_rs);

    lrm->m_k_Psi_sd_ird = iq24_mul(lrm->m_Lmsrd, lrm->m_rfpu_k_I_rf2s);
    lrm->m_k_Psi_sd_ifd = iq24_mul(lrm->m_Lmsfd, lrm->m_rfpu_k_I_rf2s);
    lrm->m_k_Psi_sq_irq = iq24_mul(lrm->m_Lmsrq, lrm->m_rfpu_k_I_rf2s);
    lrm->m_k_Psi_fd_isd = iq24_mul(lrm->m_Lmsfd, lrm->m_rfpu_k_I_s2rf);
    lrm->m_k_Psi_fd_ird = /*iq24_mul(*/ lrm->m_Lmrfd /*, IQ24(1.0))*/;


    smotor_model_recalc_stator_off_field_off(lrm);
    smotor_model_recalc_stator_off_field_on(lrm);
    smotor_model_recalc_stator_on_field_off(lrm);
    smotor_model_recalc_stator_on_field_on(lrm);


    lrm->m_I_hold = iq15_mul(lrm->p_I_hold, lrm->m_rfpu_k_I_r);

    lrm->m_Rstart = iq15_mul(lrm->p_Rstart, lrm->m_rfpu_k_R_rs);
    lrm->m_start_r_u_thr = iq15_mul(lrm->p_start_r_u_thr, lrm->m_rfpu_k_U_r);

    IDLE(lrm->m_ef_filter);

    return STATUS_READY;
}


static void smotor_model_r_start_scr_update_state(M_smotor_larionov* lrm){

    iq24_t Uf = lrm->m_Ufd;

    lrm->m_start_r_scrs_gates[0] = 0;
    lrm->m_start_r_scrs_gates[1] = 0;

    if(lrm->in_start_r_on == 1){
        lrm->m_start_r_scrs_gates[0] = 1;
        lrm->m_start_r_scrs_gates[1] = 1;
    }

    if(Uf >= lrm->m_start_r_u_thr){
        lrm->m_start_r_scrs_gates[0] = 1;
    }

    if(-Uf >= lrm->m_start_r_u_thr){
        lrm->m_start_r_scrs_gates[1] = 1;
    }

    lrm->m_start_r_scrs_state[0] = lrm->m_start_r_scrs_state[0] || lrm->m_start_r_scrs_gates[0];
    lrm->m_start_r_scrs_state[1] = lrm->m_start_r_scrs_state[1] || lrm->m_start_r_scrs_gates[1];

}

static void smotor_model_update_psis(M_smotor_larionov* lrm, flag_t stator_on, flag_t rect_on, flag_t r_start_on)
{
    flag_t field_on = rect_on || r_start_on;

    lrm->m_Psi_sd = lrm->m_Psi_sd_z1;
    lrm->m_Psi_sq = lrm->m_Psi_sq_z1;
    lrm->m_Psi_rd = lrm->m_Psi_rd_z1;
    lrm->m_Psi_rq = lrm->m_Psi_rq_z1;
    lrm->m_Psi_fd = lrm->m_Psi_fd_z1;

    iq24_t val, tmp;

    // Stator.
    if(stator_on){
        // dPsi_sd = (lrm->m_Usd + lrm->m_Psi_sq * lrm->m_w - lrm->m_Rs * lrm->m_Isd) * lrm->m_cur_dt;
        // lrm->m_Usd
        val = lrm->m_Usd;
        // lrm->m_Psi_sq * lrm->m_w;
        tmp = iq24_mul(lrm->m_Psi_sq, lrm->m_w);
        // lrm->m_Usd + lrm->m_Psi_sq * lrm->m_w
        val = iq24_add(val, tmp);
        // lrm->m_Rs * lrm->m_Isd
        tmp = iq24_mul(lrm->m_Rs, lrm->m_Isd);
        // lrm->m_Usd + lrm->m_Psi_sq * lrm->m_w - lrm->m_Rs * lrm->m_Isd
        val = iq24_sub(val, tmp);
        // (lrm->m_Usd + lrm->m_Psi_sq * lrm->m_w - lrm->m_Rs * lrm->m_Isd) * lrm->m_cur_dt
        val = iq24_mul(val, lrm->m_cur_dt);
        // dPsi_sd
        iq24_t dPsi_sd = val;

        // dPsi_sq = (lrm->m_Usq - lrm->m_Psi_sd * lrm->m_w - lrm->m_Rs * lrm->m_Isq) * lrm->m_cur_dt;
        // lrm->m_Usq
        val = lrm->m_Usq;
        // lrm->m_Psi_sd * lrm->m_w
        tmp = iq24_mul(lrm->m_Psi_sd, lrm->m_w);
        // lrm->m_Usq - lrm->m_Psi_sd * lrm->m_w
        val = iq24_sub(val, tmp);
        // lrm->m_Rs * lrm->m_Isq
        tmp = iq24_mul(lrm->m_Rs, lrm->m_Isq);
        // lrm->m_Usq - lrm->m_Psi_sd * lrm->m_w - lrm->m_Rs * lrm->m_Isq
        val = iq24_sub(val, tmp);
        // (lrm->m_Usq - lrm->m_Psi_sd * lrm->m_w - lrm->m_Rs * lrm->m_Isq) * lrm->m_cur_dt
        val = iq24_mul(val, lrm->m_cur_dt);
        // dPsi_sq
        iq24_t dPsi_sq = val;

        lrm->m_Psi_sd += dPsi_sd;
        lrm->m_Psi_sq += dPsi_sq;
    }

    // Rotor.
    //if(rotor_on){
        // dPsi_rd = (- lrm->m_Rr * lrm->m_Ird) * lrm->m_cur_dt
        // 0
        val = 0;
        // lrm->m_Rr * lrm->m_Ird
        tmp = iq24_mul(lrm->m_Rr, lrm->m_Ird);
        // - lrm->m_Rr * lrm->m_Ird
        val = iq24_sub(val, tmp);
        // (- lrm->m_Rr * lrm->m_Ird) * lrm->m_cur_dt
        val = iq24_mul(val, lrm->m_cur_dt);
        // dPsi_rd
        iq24_t dPsi_rd = val;

        // dPsi_rq = (- lrm->m_Rr * lrm->m_Irq) * lrm->m_cur_dt
        // 0
        val = 0;
        // lrm->m_Rr * lrm->m_Irq
        tmp = iq24_mul(lrm->m_Rr, lrm->m_Irq);
        // - lrm->m_Rr * lrm->m_Irq
        val = iq24_sub(val, tmp);
        // (- lrm->m_Rr * lrm->m_Irq) * lrm->m_cur_dt
        val = iq24_mul(val, lrm->m_cur_dt);
        // dPsi_rq
        iq24_t dPsi_rq = val;

        lrm->m_Psi_rd += dPsi_rd;
        lrm->m_Psi_rq += dPsi_rq;
    //}

    // Field.
    if(field_on){
        iq24_t Urect = lrm->m_U_rect;

        iq24_t Rf = lrm->m_Rf;

        if(rect_on == 0){
            Urect = 0;

            if(r_start_on == 1){
                Rf = lrm->m_Rf + lrm->m_Rstart;
            }
        }

        // dPsi_fd = (Urect - Rf * lrm->m_Ifd) * lrm->m_cur_dt
        // Urect
        val = Urect;
        // Rf * lrm->m_Ifd
        tmp = iq24_mul(Rf, lrm->m_Ifd);
        // Urect - Rf * lrm->m_Ifd
        val = iq24_sub(val, tmp);
        // (Urect - Rf * lrm->m_Ifd) * lrm->m_cur_dt
        val = iq24_mul(val, lrm->m_cur_dt);
        // dPsi_fd
        iq24_t dPsi_fd = val;

        lrm->m_Psi_fd += dPsi_fd;
    }
}

static void smotor_model_calc_elec(M_smotor_larionov* lrm)
{
    flag_t rect_on = lrm->m_scrs_opened;
    flag_t rect_on_force = lrm->m_scrs_gated;


    smotor_model_r_start_scr_update_state(lrm);


    flag_t r_start_scr_pos_on = lrm->m_start_r_scrs_state[0];
    flag_t r_start_scr_neg_on = lrm->m_start_r_scrs_state[1];

    flag_t r_start_scr_pos_force = lrm->m_start_r_scrs_gates[0];
    flag_t r_start_scr_neg_force = lrm->m_start_r_scrs_gates[1];

    flag_t r_start_on = r_start_scr_pos_on || r_start_scr_neg_on;

    flag_t stator_on = lrm->in_stator_on;
    flag_t field_on = rect_on || r_start_on;


    smotor_model_update_psis(lrm, stator_on, rect_on, r_start_on);


    iq24_t Urect = lrm->m_U_rect;
    iq24_t Irect = 0;
    iq24_t Irstart = 0;

    iq24_t Isd = 0;
    iq24_t Isq = 0;
    iq24_t Ird = 0;
    iq24_t Irq = 0;
    iq24_t Ifd = 0;
    iq24_t Efd = 0;
    iq24_t Ufd = 0;

    iq24_t Psi_fd = 0;
    iq24_t Psi_sd = 0;
    iq24_t Psi_sq = 0;

    iq24_t val, tmp;

    if(stator_on == 1){
        if(field_on){
            // Ifd = lrm->m_k_ifd_Psi_sd * lrm->m_Psi_sd + lrm->m_k_ifd_Psi_rd * lrm->m_Psi_rd + lrm->m_k_ifd_Psi_fd * lrm->m_Psi_fd;
            // lrm->m_k_ifd_Psi_sd * lrm->m_Psi_sd
            val = iq24_mul(lrm->m_k_ifd_Psi_sd, lrm->m_Psi_sd);
            // lrm->m_k_ifd_Psi_rd * lrm->m_Psi_rd
            tmp = iq24_mul(lrm->m_k_ifd_Psi_rd, lrm->m_Psi_rd);
            // lrm->m_k_ifd_Psi_sd * lrm->m_Psi_sd + lrm->m_k_ifd_Psi_rd * lrm->m_Psi_rd
            val = iq24_add(val, tmp);
            // lrm->m_k_ifd_Psi_fd * lrm->m_Psi_fd
            tmp = iq24_mul(lrm->m_k_ifd_Psi_fd, lrm->m_Psi_fd);
            // lrm->m_k_ifd_Psi_sd * lrm->m_Psi_sd + lrm->m_k_ifd_Psi_rd * lrm->m_Psi_rd + lrm->m_k_ifd_Psi_fd * lrm->m_Psi_fd
            val = iq24_add(val, tmp);

            // Ifd = Ifd * lrm->m_id_denom_inv;
            val = iq24_mul(val, lrm->m_id_denom_inv);
            // Ifd
            Ifd = val;
        }
    }else{
        if(field_on){
            // Ifd = lrm->m_k_ifd_Psi_rd_s_off * lrm->m_Psi_rd + lrm->m_k_ifd_Psi_fd_s_off * lrm->m_Psi_fd;
            // lrm->m_k_ifd_Psi_rd_s_off * lrm->m_Psi_rd
            val = iq24_mul(lrm->m_k_ifd_Psi_rd_s_off, lrm->m_Psi_rd);
            // lrm->m_k_ifd_Psi_fd_s_off * lrm->m_Psi_fd
            tmp = iq24_mul(lrm->m_k_ifd_Psi_fd_s_off, lrm->m_Psi_fd);
            // lrm->m_k_ifd_Psi_rd_s_off * lrm->m_Psi_rd + lrm->m_k_ifd_Psi_fd_s_off * lrm->m_Psi_fd
            val = iq24_add(val, tmp);

            // Ifd = Ifd * lrm->m_id_denom_inv_s_off;
            val = iq24_mul(val, lrm->m_id_denom_inv_s_off);
            // Ifd
            Ifd = val;
        }
    }

    if(field_on){
        if(rect_on){
            if(Urect < 0){ // => Irstart < 0
                r_start_scr_pos_on = r_start_scr_pos_force;

                if(r_start_scr_neg_on){
                    Irstart = iq24_div(Urect, lrm->m_Rstart);

                    if((-Irstart < lrm->m_I_hold) && (r_start_scr_neg_force == 0)){
                        r_start_scr_pos_on = 0;
                        Irstart = 0;
                    }
                }
            }else{ // Urect >= 0 => Irstart >= 0
                r_start_scr_neg_on = r_start_scr_neg_force;

                if(r_start_scr_pos_on){
                    Irstart = iq24_div(Urect, lrm->m_Rstart);

                    if((Irstart < lrm->m_I_hold) && (r_start_scr_pos_force == 0)){
                        r_start_scr_pos_on = 0;
                        Irstart = 0;
                    }
                }
            }

            Irect = Irstart + Ifd;
            if((Irect < 0) || ((Irect < lrm->m_I_hold) && (rect_on_force == 0))){
                rect_on = 0;
                Irect = 0;
                Irstart = 0;
            }
        } else { // if(rect_on == 0)
            if(Ifd < 0){
                r_start_scr_neg_on = r_start_scr_neg_force;

                if((-Ifd < lrm->m_I_hold) && (r_start_scr_pos_force == 0)){
                    r_start_scr_pos_on = 0;
                }else{
                    Irstart = -Ifd;
                }
            }else{ //Ifd >= 0
                r_start_scr_pos_on = r_start_scr_pos_force;

                if((Ifd < lrm->m_I_hold) && (r_start_scr_neg_force == 0)){
                    r_start_scr_neg_on = 0;
                }else{
                    Irstart = -Ifd;
                }
            }
        }

        r_start_on = r_start_scr_pos_on || r_start_scr_neg_on;
        field_on = rect_on || r_start_on;

        if(field_on == 0){
            Irstart = 0;
            Irect = 0;
            Ifd = 0;
            smotor_model_update_psis(lrm, stator_on, rect_on, r_start_on);
        }

    }


    if(stator_on == 1){

        if(field_on){
            // Isd = lrm->m_k_isd_Psi_sd * lrm->m_Psi_sd + lrm->m_k_isd_Psi_rd * lrm->m_Psi_rd + lrm->m_k_isd_Psi_fd * lrm->m_Psi_fd;
            // lrm->m_k_isd_Psi_sd * lrm->m_Psi_sd
            val = iq24_mul(lrm->m_k_isd_Psi_sd, lrm->m_Psi_sd);
            // lrm->m_k_isd_Psi_rd * lrm->m_Psi_rd
            tmp = iq24_mul(lrm->m_k_isd_Psi_rd, lrm->m_Psi_rd);
            // lrm->m_k_isd_Psi_sd * lrm->m_Psi_sd + lrm->m_k_isd_Psi_rd * lrm->m_Psi_rd
            val = iq24_add(val, tmp);
            // lrm->m_k_isd_Psi_fd * lrm->m_Psi_fd
            tmp = iq24_mul(lrm->m_k_isd_Psi_fd, lrm->m_Psi_fd);
            // lrm->m_k_isd_Psi_sd * lrm->m_Psi_sd + lrm->m_k_isd_Psi_rd * lrm->m_Psi_rd + lrm->m_k_isd_Psi_fd * lrm->m_Psi_fd
            val = iq24_add(val, tmp);

            // Isd = Isd * lrm->m_id_denom_inv;
            val = iq24_mul(val, lrm->m_id_denom_inv);
            // Isd
            Isd = val;


            // Isq = lrm->m_k_isq_Psi_sq * lrm->m_Psi_sq + lrm->m_k_isq_Psi_rq * lrm->m_Psi_rq;
            // lrm->m_k_isq_Psi_sq * lrm->m_Psi_sq
            val = iq24_mul(lrm->m_k_isq_Psi_sq, lrm->m_Psi_sq);
            // lrm->m_k_isq_Psi_rq * lrm->m_Psi_rq
            tmp = iq24_mul(lrm->m_k_isq_Psi_rq, lrm->m_Psi_rq);
            // lrm->m_k_isq_Psi_sq * lrm->m_Psi_sq + lrm->m_k_isq_Psi_rq * lrm->m_Psi_rq
            val = iq24_add(val, tmp);

            // Isq = Isq * lrm->m_iq_denom_inv;
            val = iq24_mul(val, lrm->m_iq_denom_inv);
            // Isq
            Isq = val;


            // Ird = lrm->m_k_ird_Psi_sd * lrm->m_Psi_sd + lrm->m_k_ird_Psi_rd * lrm->m_Psi_rd + lrm->m_k_ird_Psi_fd * lrm->m_Psi_fd;
            // lrm->m_k_ird_Psi_sd * lrm->m_Psi_sd
            val = iq24_mul(lrm->m_k_ird_Psi_sd, lrm->m_Psi_sd);
            // lrm->m_k_ird_Psi_rd * lrm->m_Psi_rd
            tmp = iq24_mul(lrm->m_k_ird_Psi_rd, lrm->m_Psi_rd);
            // lrm->m_k_ird_Psi_sd * lrm->m_Psi_sd + lrm->m_k_ird_Psi_rd * lrm->m_Psi_rd
            val = iq24_add(val, tmp);
            // lrm->m_k_ird_Psi_fd * lrm->m_Psi_fd
            tmp = iq24_mul(lrm->m_k_ird_Psi_fd, lrm->m_Psi_fd);
            // lrm->m_k_ird_Psi_sd * lrm->m_Psi_sd + lrm->m_k_ird_Psi_rd * lrm->m_Psi_rd + lrm->m_k_ird_Psi_fd * lrm->m_Psi_fd
            val = iq24_add(val, tmp);

            // Ird = Ird * lrm->m_id_denom_inv;
            val = iq24_mul(val, lrm->m_id_denom_inv);
            // Ird
            Ird = val;


            // Irq = lrm->m_k_irq_Psi_sq * lrm->m_Psi_sq + lrm->m_k_irq_Psi_rq * lrm->m_Psi_rq;
            // lrm->m_k_irq_Psi_sq * lrm->m_Psi_sq
            val = iq24_mul(lrm->m_k_irq_Psi_sq, lrm->m_Psi_sq);
            // lrm->m_k_irq_Psi_rq * lrm->m_Psi_rq
            tmp = iq24_mul(lrm->m_k_irq_Psi_rq, lrm->m_Psi_rq);
            // lrm->m_k_irq_Psi_sq * lrm->m_Psi_sq + lrm->m_k_irq_Psi_rq * lrm->m_Psi_rq
            val = iq24_add(val, tmp);

            // Irq = Irq * lrm->m_iq_denom_inv;
            val = iq24_mul(val, lrm->m_iq_denom_inv);
            // Irq
            Irq = val;


            if(rect_on){
                Ufd = Urect;
                Efd = iq24_add(-Urect, iq24_mul(Ifd, lrm->m_Rf));
            }else{
                Ufd = iq24_mul(-Ifd, lrm->m_Rstart);
                Efd = iq24_mul( Ifd, (lrm->m_Rf + lrm->m_Rstart));
            }

            lrm->m_ef_filter.in_value = Efd;
            lrm->m_ef_filter.out_value = Efd;

        }else{
            // Isd = lrm->m_k_isd_Psi_sd_f_off * lrm->m_Psi_sd + lrm->m_k_isd_Psi_rd_f_off * lrm->m_Psi_rd;
            // lrm->m_k_isd_Psi_sd_f_off * lrm->m_Psi_sd
            val = iq24_mul(lrm->m_k_isd_Psi_sd_f_off, lrm->m_Psi_sd);
            // lrm->m_k_isd_Psi_rd_f_off * lrm->m_Psi_rd
            tmp = iq24_mul(lrm->m_k_isd_Psi_rd_f_off, lrm->m_Psi_rd);
            // lrm->m_k_isd_Psi_sd_f_off * lrm->m_Psi_sd + lrm->m_k_isd_Psi_rd_f_off * lrm->m_Psi_rd
            val = iq24_add(val, tmp);

            // Isd = Isd * lrm->m_id_denom_inv_f_off;
            val = iq24_mul(val, lrm->m_id_denom_inv_f_off);
            // Isd
            Isd = val;


            // Isq = lrm->m_k_isq_Psi_sq_f_off * lrm->m_Psi_sq + lrm->m_k_isq_Psi_rq_f_off * lrm->m_Psi_rq;
            // lrm->m_k_isq_Psi_sq_f_off * lrm->m_Psi_sq
            val = iq24_mul(lrm->m_k_isq_Psi_sq_f_off, lrm->m_Psi_sq);
            // lrm->m_k_isq_Psi_rq_f_off * lrm->m_Psi_rq
            tmp = iq24_mul(lrm->m_k_isq_Psi_rq_f_off, lrm->m_Psi_rq);
            // lrm->m_k_isq_Psi_sq_f_off * lrm->m_Psi_sq + lrm->m_k_isq_Psi_rq_f_off * lrm->m_Psi_rq
            val = iq24_add(val, tmp);

            // Isq = Isq * lrm->m_iq_denom_inv_f_off;
            val = iq24_mul(val, lrm->m_iq_denom_inv_f_off);
            // Isq
            Isq = val;


            // Ird = lrm->m_k_ird_Psi_sd_f_off * lrm->m_Psi_sd + lrm->m_k_ird_Psi_rd_f_off * lrm->m_Psi_rd;
            // lrm->m_k_ird_Psi_sd_f_off * lrm->m_Psi_sd
            val = iq24_mul(lrm->m_k_ird_Psi_sd_f_off, lrm->m_Psi_sd);
            // lrm->m_k_ird_Psi_rd_f_off * lrm->m_Psi_rd
            tmp = iq24_mul(lrm->m_k_ird_Psi_rd_f_off, lrm->m_Psi_rd);
            // lrm->m_k_ird_Psi_sd_f_off * lrm->m_Psi_sd + lrm->m_k_ird_Psi_rd_f_off * lrm->m_Psi_rd
            val = iq24_add(val, tmp);

            // Ird = Ird * lrm->m_id_denom_inv_f_off;
            val = iq24_mul(val, lrm->m_id_denom_inv_f_off);
            // Ird
            Ird = val;


            // Irq = lrm->m_k_irq_Psi_sq_f_off * lrm->m_Psi_sq + lrm->m_k_irq_Psi_rq_f_off * lrm->m_Psi_rq;
            // lrm->m_k_irq_Psi_sq_f_off * lrm->m_Psi_sq
            val = iq24_mul(lrm->m_k_irq_Psi_sq_f_off, lrm->m_Psi_sq);
            // lrm->m_k_irq_Psi_rq_f_off * lrm->m_Psi_rq
            tmp = iq24_mul(lrm->m_k_irq_Psi_rq_f_off, lrm->m_Psi_rq);
            // lrm->m_k_irq_Psi_sq_f_off * lrm->m_Psi_sq + lrm->m_k_irq_Psi_rq_f_off * lrm->m_Psi_rq
            val = iq24_add(val, tmp);

            // Irq = Irq * lrm->m_iq_denom_inv_f_off;
            val = iq24_mul(val, lrm->m_iq_denom_inv_f_off);
            // Irq
            Irq = val;


            // Psi_fd = lrm->m_k_Psi_fd_isd * Isd + lrm->m_k_Psi_fd_ird * Ird;
            // lrm->m_k_Psi_fd_isd * Isd
            val = iq24_mul(lrm->m_k_Psi_fd_isd, Isd);
            // lrm->m_k_Psi_fd_ird * Ird
            tmp = iq24_mul(lrm->m_k_Psi_fd_ird, Ird);
            // lrm->m_k_Psi_fd_isd * Isd + lrm->m_k_Psi_fd_ird * Ird
            val = iq24_add(val, tmp);
            // Psi_fd
            Psi_fd = val;

            val = iq24_div(lrm->m_Psi_fd - Psi_fd, lrm->m_cur_dt);
            // Efd
            Efd = val;

            lrm->m_Psi_fd = Psi_fd;

            lrm->m_ef_filter.in_value = Efd;
            CALC(lrm->m_ef_filter);
            Efd = lrm->m_ef_filter.out_value;

            Ufd = -Efd;

        }

    }else{ //stator_on == 0

        if(field_on){
            // Ird = lrm->m_k_ird_Psi_rd_s_off * lrm->m_Psi_rd + lrm->m_k_ird_Psi_fd_s_off * lrm->m_Psi_fd;
            // lrm->m_k_ird_Psi_rd_s_off * lrm->m_Psi_rd
            val = iq24_mul(lrm->m_k_ird_Psi_rd_s_off, lrm->m_Psi_rd);
            // lrm->m_k_ird_Psi_fd_s_off * lrm->m_Psi_fd
            tmp = iq24_mul(lrm->m_k_ird_Psi_fd_s_off, lrm->m_Psi_fd);
            // lrm->m_k_ird_Psi_rd_s_off * lrm->m_Psi_rd + lrm->m_k_ird_Psi_fd_s_off * lrm->m_Psi_fd
            val = iq24_add(val, tmp);

            // Ird = Ird * lrm->m_id_denom_inv_s_off;
            val = iq24_mul(val, lrm->m_id_denom_inv_s_off);
            // Ird
            Ird = val;

            // Irq = lrm->m_Psi_rq * lrm->m_iq_denom_inv_s_off;
            val = iq24_mul(lrm->m_Psi_rq, lrm->m_iq_denom_inv_s_off);
            // Irq
            Irq = val;

            // Psi_sd = lrm->m_k_Psi_sd_ird * Ird + lrm->m_k_Psi_sd_ifd * Ifd;
            // lrm->m_k_Psi_sd_ird * Ird
            val = iq24_mul(lrm->m_k_Psi_sd_ird, Ird);
            // lrm->m_k_Psi_sd_ifd * Ifd
            tmp = iq24_mul(lrm->m_k_Psi_sd_ifd, Ifd);
            // lrm->m_k_Psi_sd_ird * Ird + lrm->m_k_Psi_sd_ifd * Ifd
            val = iq24_add(val, tmp);
            // Psi_sd
            Psi_sd = val;

            // Psi_sq = lrm->m_k_Psi_sq_irq * Irq;
            val = iq24_mul(lrm->m_k_Psi_sq_irq, Irq);
            // Psi_sq
            Psi_sq = val;

            if(rect_on){
                Ufd = Urect;
                Efd = iq24_add(-Urect, iq24_mul(Ifd, lrm->m_Rf));
            }else{
                Ufd = iq24_mul(-Ifd, lrm->m_Rstart);
                Efd = iq24_mul( Ifd, (lrm->m_Rf + lrm->m_Rstart));
            }

            lrm->m_Psi_sd = Psi_sd;
            lrm->m_Psi_sq = Psi_sq;

            lrm->m_ef_filter.in_value = Efd;
            lrm->m_ef_filter.out_value = Efd;

        }else{

            // Ird = lrm->m_Psi_rd * lrm->m_id_denom_inv_sf_off;
            val = iq24_mul(lrm->m_Psi_rd, lrm->m_id_denom_inv_sf_off);
            // Ird
            Ird = val;

            // Irq = lrm->m_Psi_rq * lrm->m_iq_denom_inv_sf_off;
            val = iq24_mul(lrm->m_Psi_rq, lrm->m_iq_denom_inv_sf_off);
            // Irq
            Irq = val;

            // Psi_sd = lrm->m_k_Psi_sd_ird * Ird;
            val = iq24_mul(lrm->m_k_Psi_sd_ird, Ird);
            // Psi_sd
            Psi_sd = val;

            // Psi_sq = lrm->m_k_Psi_sq_irq * Irq;
            val = iq24_mul(lrm->m_k_Psi_sq_irq, Irq);
            // Psi_sq
            Psi_sq = val;

            // Psi_fd = lrm->m_k_Psi_fd_ird * Ird;
            val = iq24_mul(lrm->m_k_Psi_fd_ird, Ird);
            // Psi_fd
            Psi_fd = val;

            val = iq24_div(lrm->m_Psi_fd - Psi_fd, lrm->m_cur_dt);
            // Efd
            Efd = val;

            lrm->m_Psi_sd = Psi_sd;
            lrm->m_Psi_sq = Psi_sq;
            lrm->m_Psi_fd = Psi_fd;

            lrm->m_ef_filter.in_value = Efd;
            CALC(lrm->m_ef_filter);
            Efd = lrm->m_ef_filter.out_value;

            Ufd = -Efd;

        }

    }

    lrm->m_start_r_scrs_state[0] = r_start_scr_pos_on;
    lrm->m_start_r_scrs_state[1] = r_start_scr_neg_on;

    lrm->m_Isd = Isd;
    lrm->m_Isq = Isq;
    lrm->m_Ird = Ird;
    lrm->m_Irq = Irq;
    lrm->m_Ifd = Ifd;
    lrm->m_Efd = Efd;
    lrm->m_Ufd = Ufd;
    lrm->m_Irstart = Irstart;
    lrm->m_Irect = Irect;

////    lrm->m_stator_on_z1 = lrm->in_stator_on;
////    lrm->m_field_on_z1 = field_on;

}

static iq24_t smotor_larionov_calc_Mc(M_smotor_larionov* lrm)
{
    iq24_t tmp;

    iq24_t w = lrm->m_w;
    iq24_t Kf = lrm->m_Kf;
    //iq24_t W_nom = IQ24(1.0);
    iq24_t Mc_nom = lrm->m_Mc;

    iq24_t W_EPS = IQ24(1e-3);

    iq24_t Mf = iq24_mul(Kf, Mc_nom);

    tmp = iq24_abs(w);

    if(tmp < W_EPS){
        Mf = 0;
    }

//    Mc = ((abs(w) ./ W_nom) .^ 2) .* (Mc_nom - Mf);
//    Mc = Mc * lrm->in_k_Mc;
    //tmp = iq24_abs(w);
    //tmp = iq24_div(tmp, W_nom); // W_nom == 1.0
    tmp = iq24_mul(tmp, tmp);
    tmp = iq24_mul(tmp, Mc_nom - Mf);
    iq24_t Mc = iq24_mul(tmp, lrm->in_k_Mc);

    iq24_t Mc_sum = Mc + Mf;

    if(w < 0){
        Mc_sum = -Mc_sum;
    }

//#warning DEBUG!
//    if(iq24_abs(w) < W_EPS){
//        return 0;
//    }else{
//        if(w >= 0){
//            return lrm->m_Mc;
//        }else{
//            return -lrm->m_Mc;
//        }
//    }

    return Mc_sum;
}

static void smotor_model_calc_mech(M_smotor_larionov* lrm)
{
    iq24_t Psi_sd_I_sq = iq24_mul(lrm->m_Psi_sd, lrm->m_Isq);
    iq24_t Psi_sq_I_sd = iq24_mul(lrm->m_Isd, lrm->m_Psi_sq);

    iq24_t M = iq24_sub(Psi_sd_I_sq, Psi_sq_I_sd);
    // 2-phase -> 3-phase: M = M * (3/2).
    M = (M * 3) >> 1;

    lrm->m_M = M;
}

static void smotor_model_update_mech(M_smotor_larionov* lrm)
{
    iq24_t Mc = smotor_larionov_calc_Mc(lrm);

    iq24_t dt_Tj = iq24_mul(lrm->m_cur_dt, lrm->m_Tj_inv);//lrm->m_Tj

    iq24_t dw = iq24_mul(lrm->m_M - Mc, dt_Tj);
    iq24_t w = lrm->m_w + dw;

    iq24_t dteta = iq24_mul(lrm->m_w, lrm->m_cur_dt);
    // rad -> pu
    dteta = iq24_mul(dteta, IQ24_INV_2PI);
    iq24_t teta = lrm->m_teta + dteta;

    lrm->m_teta = teta;
    lrm->m_w = w;
}

static void smotor_model_calc(M_smotor_larionov* lrm)
{
    // Обновление скорости и угла поворота ротора до текущего момента.
    smotor_model_update_mech(lrm);

    lrm->m_teta = iq24_angle_norm_pu(lrm->m_teta);

    // Преобразование из 3х фазной системы в двухфазную.
    lrm->m_clarke.in_A = lrm->m_cur_stator_Uab;
    lrm->m_clarke.in_B = lrm->m_cur_stator_Ubc;
    lrm->m_clarke.in_C = lrm->m_cur_stator_Uca;
    CALC(lrm->m_clarke);
    lrm->m_Usa = lrm->m_clarke.out_A;
    lrm->m_Usb = lrm->m_clarke.out_B;

    lrm->m_park.in_A = lrm->m_Usa;
    lrm->m_park.in_B = lrm->m_Usb;
    lrm->m_park.in_cos_angle = iq24_cos_pu(lrm->m_teta);
    lrm->m_park.in_sin_angle = iq24_sin_pu(lrm->m_teta);
    CALC(lrm->m_park);
    lrm->m_Usd = lrm->m_park.out_A;
    lrm->m_Usq = lrm->m_park.out_B;

    smotor_model_calc_elec(lrm);
    smotor_model_calc_mech(lrm);

    lrm->m_park_inv.in_A = lrm->m_Isd;
    lrm->m_park_inv.in_B = lrm->m_Isq;
    lrm->m_park_inv.in_cos_angle = lrm->m_park.in_cos_angle;
    lrm->m_park_inv.in_sin_angle = lrm->m_park.in_sin_angle;
    CALC(lrm->m_park_inv);
    lrm->m_Isa = lrm->m_park_inv.out_A;
    lrm->m_Isb = lrm->m_park_inv.out_B;

    lrm->m_clarke_inv.in_A = lrm->m_Isa;
    lrm->m_clarke_inv.in_B = lrm->m_Isb;
    CALC(lrm->m_clarke_inv);
    lrm->out_stator_Iab = lrm->m_clarke_inv.out_A;
    lrm->out_stator_Ibc = lrm->m_clarke_inv.out_B;
    lrm->out_stator_Ica = lrm->m_clarke_inv.out_C;

    lrm->out_M = lrm->m_M;
    lrm->out_w = lrm->m_w;

    lrm->m_U_load = lrm->m_Ufd;
    lrm->m_I_load = lrm->m_Irect;

    // Напряжение нагрузки переводится в с.е. двигателя.
    lrm->out_U = iq24_mul(lrm->m_U_load, lrm->m_rfpu_k_U_rf2mt);
    // Ток нагрузки переводится в с.е. двигателя.
    lrm->out_I = iq24_mul(lrm->m_I_load, lrm->m_rfpu_k_I_rf2mt);
    // Ток пускового сопротивления переводится в с.е. двигателя.
    lrm->out_Irstart = iq24_mul(lrm->m_Irstart, lrm->m_rfpu_k_I_rf2mt);

    lrm->m_Psi_sd_z1 = lrm->m_Psi_sd;
    lrm->m_Psi_sq_z1 = lrm->m_Psi_sq;
    lrm->m_Psi_rd_z1 = lrm->m_Psi_rd;
    lrm->m_Psi_rq_z1 = lrm->m_Psi_rq;
    lrm->m_Psi_fd_z1 = lrm->m_Psi_fd;
}


// Вычисление.
ALWAYS_INLINE static void smotor_larionov_load_SM_calc(M_smotor_larionov* lrm){
    smotor_model_calc(lrm);
}

// Сброс.
//static void smotor_larionov_load_SM_reset(M_smotor_larionov* lrm){
//}

// Обновление констант.
static status_t smotor_larionov_load_SM_update(M_smotor_larionov* lrm)
{
    smotor_model_update(lrm);

    return STATUS_READY;
}


// Модель Ларионова.

// Проверяет наличие хотя бы одного флага в массиве.
static flag_t smotor_larionov_has_active_state(flag_t *f)
{
    int i;
    for (i = 0; i < SMOTOR_LARIONOV_KEYS_COUNT; i++) {
        if (f[i]) {
            return 1;
        }
    }
    return 0;
}

// Проверяет наличие хотя бы одного флага в массиве.
static void smotor_larionov_reset_state(flag_t *f)
{
    int i;
    for (i = 0; i < SMOTOR_LARIONOV_KEYS_COUNT; i++) {
        f[i] = 0;
    }
}

static int smotor_larionov_next_scr_index(int index)
{
    int next_index = index - 1;

    if (next_index < 0) {
        next_index += SMOTOR_LARIONOV_KEYS_COUNT;
    }

    return next_index;
}

static flag_t smotor_larionov_set_states(flag_t* out_states, flag_t* in_states)
{
    flag_t has_any = FLAG_NONE;

    int i;
    for (i = 0; i < SMOTOR_LARIONOV_KEYS_COUNT; i++) {
        out_states[i] = in_states[i];

        if(in_states[i]){
            has_any = FLAG_ACTIVE;
        }
    }

    return has_any;
}

// Обновляет управляющие.
static void smotor_larionov_update_gates(M_smotor_larionov* lrm)
{
    // Флаг наличия управляющих.
    flag_t has_gates = smotor_larionov_has_active_state(lrm->m_gates_state);
    // Если есть.
    if(has_gates){
        // Угол с начала подачи управления.
        iq24_t gates_da = iq24_angle_norm_pu(
                lrm->m_cur_Uref_angle - lrm->m_gates_ref_angle);
        // Если превышает заданную продолжительность.
        if(gates_da > lrm->in_control_duration_angle){
            // Сбросим управляющие.
            smotor_larionov_reset_state(lrm->m_gates_state);
        }
    }

    lrm->m_scrs_gated = has_gates;
}

// Обновляет выходное напряжение.
static void smotor_larionov_update_voltage_and_state(M_smotor_larionov* lrm)
{
    iq24_t Uab, Ubc, Uca;

    // Перевод напряжений в с.е. ротора.
    Uab = iq24_mul(lrm->m_cur_Uab, lrm->m_rfpu_k_U_ms2rf);
    Ubc = iq24_mul(lrm->m_cur_Ubc, lrm->m_rfpu_k_U_ms2rf);
    Uca = iq24_mul(lrm->m_cur_Uca, lrm->m_rfpu_k_U_ms2rf);

    // [ AB, AC, BC, BA, CA, CB ]
    iq24_t voltages[SMOTOR_LARIONOV_KEYS_COUNT] = {
             Uab, -Uca,  Ubc,
            -Uab,  Uca, -Ubc
    };

    int i;

    int pair_first = -1;
    int pair_second = -1;
    iq24_t U = lrm->m_U_load;

    // Выбор максимального напряжения открытых пар тиристоров и соответствующей пары.
    for (i = 0; i < SMOTOR_LARIONOV_KEYS_COUNT; i++) {
        int self_index = i;
        int pair_index = smotor_larionov_next_scr_index(i);

        flag_t self_gated = lrm->m_gates_state[self_index];
        flag_t pair_gated = lrm->m_gates_state[pair_index];

        flag_t self_opened = lrm->m_scrs_state[self_index];
        flag_t pair_opened = lrm->m_scrs_state[pair_index];

        iq24_t voltage = voltages[i];

        if((self_gated != 0 && pair_gated != 0 && voltage > lrm->m_U_load) ||
           (self_opened != 0 && pair_opened != 0)){

            if(voltage > U || pair_first == -1){
                pair_first = self_index;
                pair_second = pair_index;
                U = voltage;
            }
        }
    }

    // Выпрямленное напряжение.
    lrm->m_U_rect = U;

    flag_t scrs_opened = FLAG_NONE;

    // Установка состояния тиристоров.
    for (i = 0; i < SMOTOR_LARIONOV_KEYS_COUNT; i++) {
        if(i == pair_first || i == pair_second){
            lrm->m_scrs_state[i] = 1;

            scrs_opened = FLAG_ACTIVE;
        }else{
            lrm->m_scrs_state[i] = 0;
        }
    }

    lrm->m_scrs_opened = scrs_opened;
}

// Вычисляет нагрузку, в зависимости от типа.
static void smotor_larionov_calc_load(M_smotor_larionov* lrm){
    smotor_larionov_load_SM_calc(lrm);
}

// Обновляет токи и состояния тиристоров.
static void smotor_larionov_update_currents_and_state(M_smotor_larionov* lrm)
{
    // Модель всегда "отпирает" только два тиристора,
    // Поэтому считать число открытых тиристоров не нужно,
    // Ток через каждый открытый тиристор
    // будет всегда равен току нагрузки.

    // Ток нагрузки переводится в с.е. сети.
    iq24_t I_load = iq24_mul(lrm->m_I_load, lrm->m_rfpu_k_I_rf2ms);

    int i;

    // Обновление тока тиристоров.
    for (i = 0; i < SMOTOR_LARIONOV_KEYS_COUNT; i++) {
        if(lrm->m_scrs_state[i] != 0){
            lrm->m_scrs_I[i] = I_load;
        }else{
            lrm->m_scrs_I[i] = 0;
        }
    }

    // Обновление состояния тиристоров.
    for (i = 0; i < SMOTOR_LARIONOV_KEYS_COUNT; i++) {
        //if(lrm->m_scrs_I[i] < lrm->m_I_hold){
        if(((iq24_abs(lrm->m_scrs_I[i]) < lrm->m_I_hold) && (lrm->m_gates_state[i] == 0)) || (lrm->m_scrs_I[i] < 0)){
            lrm->m_scrs_state[i] = 0;
        }
    }

}

// Обновляет выходные переменные.
static void smotor_larionov_update_outputs(M_smotor_larionov* lrm)
{
    lrm->out_Iab = lrm->m_scrs_I[SMOTOR_LARIONOV_A_HI] - lrm->m_scrs_I[SMOTOR_LARIONOV_A_LO];
    lrm->out_Ibc = lrm->m_scrs_I[SMOTOR_LARIONOV_B_HI] - lrm->m_scrs_I[SMOTOR_LARIONOV_B_LO];
    lrm->out_Ica = lrm->m_scrs_I[SMOTOR_LARIONOV_C_HI] - lrm->m_scrs_I[SMOTOR_LARIONOV_C_LO];

    // Эти значения присваиваются в
    // smotor_model_calc
//    lrm->out_U = lrm->m_U_load;
//    lrm->out_I = lrm->m_I_load;

}

// Выполняет расчёт модели.
static void smotor_larionov_sim(M_smotor_larionov* lrm)
{
    // Обновим состояния управляющих.
    smotor_larionov_update_gates(lrm);

    // Обновим напряжения и состояния.
    smotor_larionov_update_voltage_and_state(lrm);

    // Вычисление модели.
    smotor_larionov_calc_load(lrm);

    // Обработаем ток модели.
    smotor_larionov_update_currents_and_state(lrm);

}

static void smotor_larionov_calc(M_smotor_larionov* lrm)
{
    // Минимальное время для обсчёта.
    #define DT_EPS IQ24(1.0e-5)

    // Обработка управления.

    // Если разрешён расчёт.
    if (lrm->control & CONTROL_ENABLE) {
        // Флаг начала подачи управления.
        flag_t control_occurred = 0;
        // Доля времени до подачи управления.
        iq24_t dt_ratio = 0.0;

        // Есть ли управление?
        flag_t has_control = smotor_larionov_has_active_state(lrm->in_control);
        // Если есть новое управление -
        // Сохраним для обработки.
        if(has_control){
            lrm->m_need_control = 1;
            smotor_larionov_set_states(lrm->m_control, lrm->in_control);

            lrm->m_control_delay_angle = lrm->in_control_delay_angle;
            lrm->m_control_ref_Uab = lrm->in_Uab;
            lrm->m_control_ref_Ubc = lrm->in_Ubc;
            lrm->m_control_ref_Uca = lrm->in_Uca;

            lrm->m_control_ref_stator_Uab = lrm->in_stator_Uab;
            lrm->m_control_ref_stator_Ubc = lrm->in_stator_Ubc;
            lrm->m_control_ref_stator_Uca = lrm->in_stator_Uca;

            lrm->m_control_ref_angle = lrm->in_Uref_angle;
        }

        // Если есть текущее управление.
        if(lrm->m_need_control == 1){
            // Прошедший угол с момента получения управления.
            iq24_t control_da = iq24_angle_norm_pu(
                    lrm->in_Uref_angle - lrm->m_control_ref_angle);

            // Если с момента получения произошло управление.
            if(control_da > lrm->m_control_delay_angle){
                // Сбросим флаг необходимости управления.
                lrm->m_need_control = 0;

                // Доля времени до подачи упраления.
                dt_ratio = iq24_div(lrm->m_control_delay_angle, control_da);

                // Установим флаг того что управление произошло.
                control_occurred = 1;

            }else if(has_control == 0){
                // Иначе сохраним текущий момент как опорный.
                lrm->m_control_delay_angle = lrm->m_control_delay_angle - control_da;
                lrm->m_control_ref_Uab = lrm->in_Uab;
                lrm->m_control_ref_Ubc = lrm->in_Ubc;
                lrm->m_control_ref_Uca = lrm->in_Uca;

                lrm->m_control_ref_stator_Uab = lrm->in_stator_Uab;
                lrm->m_control_ref_stator_Ubc = lrm->in_stator_Ubc;
                lrm->m_control_ref_stator_Uca = lrm->in_stator_Uca;

                lrm->m_control_ref_angle = lrm->in_Uref_angle;
            }

        }


        // Расчёт.
        // Установим текущий интервал времени.
        // dt* = dt / t_base = dt * t_base_inv = dt * w_base
        lrm->m_cur_dt = iq15_mul(lrm->in_dt, motor.r_t_base_inv);

        // Если произошло управление.
        if(control_occurred){
            // Интервал времени до момента управления.
            iq24_t cur_dt = iq24_mul(lrm->m_cur_dt, dt_ratio);

            if(cur_dt >= DT_EPS){
                // Интервал времени после момента управления.
                iq24_t next_dt = lrm->m_cur_dt - cur_dt;
                if(next_dt < DT_EPS){
                    cur_dt = lrm->m_cur_dt;
                    next_dt = 0;
                }
                // Установим интервал времени до момента управления.
                lrm->m_cur_dt = cur_dt;
                // Установим текущий угол.
                lrm->m_cur_Uref_angle = lrm->m_control_ref_angle + lrm->m_control_delay_angle;
                // Проинтерполируем напряжения к моменту подачи управления.
                lrm->m_cur_Uab = iq24_lerp(lrm->m_control_ref_Uab, lrm->in_Uab, dt_ratio);
                lrm->m_cur_Ubc = iq24_lerp(lrm->m_control_ref_Ubc, lrm->in_Ubc, dt_ratio);
                lrm->m_cur_Uca = iq24_lerp(lrm->m_control_ref_Uca, lrm->in_Uca, dt_ratio);

                lrm->m_cur_stator_Uab = iq24_lerp(lrm->m_control_ref_stator_Uab, lrm->in_stator_Uab, dt_ratio);
                lrm->m_cur_stator_Ubc = iq24_lerp(lrm->m_control_ref_stator_Ubc, lrm->in_stator_Ubc, dt_ratio);
                lrm->m_cur_stator_Uca = iq24_lerp(lrm->m_control_ref_stator_Uca, lrm->in_stator_Uca, dt_ratio);

                smotor_larionov_sim(lrm);

                // Установим интервал времени после момента управления.
                lrm->m_cur_dt = next_dt;
            }

            // Установим начало подачи управления.
            smotor_larionov_set_states(lrm->m_gates_state, lrm->m_control);
            lrm->m_gates_ref_angle = lrm->m_cur_Uref_angle;
        }

        if(lrm->m_cur_dt > DT_EPS){
            // Установим текущий угол.
            lrm->m_cur_Uref_angle = lrm->in_Uref_angle;
            // Устновим текущие значения напряжений.
            lrm->m_cur_Uab = lrm->in_Uab;
            lrm->m_cur_Ubc = lrm->in_Ubc;
            lrm->m_cur_Uca = lrm->in_Uca;

            lrm->m_cur_stator_Uab = lrm->in_stator_Uab;
            lrm->m_cur_stator_Ubc = lrm->in_stator_Ubc;
            lrm->m_cur_stator_Uca = lrm->in_stator_Uca;

            // Симуляция модели.
            smotor_larionov_sim(lrm);
        }

        // Обновление выходов.
        smotor_larionov_update_outputs(lrm);

    }

    #undef DT_EPS
}



//
// Метода модуля.
//

static status_t recalc_values(M_smotor_larionov* lrm)
{
    status_t res_status = STATUS_READY;
    status_t status = STATUS_NONE;

    // Обновим рассчитываемые константы.
    status = smotor_larionov_load_SM_update(lrm);
    if(status != STATUS_READY) { res_status = status; }

    return res_status;
}

METHOD_INIT_IMPL(M_smotor_larionov, lrm)
{
    INIT(lrm->m_clarke);
    INIT(lrm->m_clarke_inv);
    INIT(lrm->m_park);
    INIT(lrm->m_park_inv);
    INIT(lrm->m_ef_filter);

    IDLE((*lrm));
}

METHOD_DEINIT_IMPL(M_smotor_larionov, lrm)
{
    DEINIT(lrm->m_clarke);
    DEINIT(lrm->m_clarke_inv);
    DEINIT(lrm->m_park);
    DEINIT(lrm->m_park_inv);
    DEINIT(lrm->m_ef_filter);
}

METHOD_CALC_IMPL(M_smotor_larionov, lrm)
{
    smotor_larionov_calc(lrm);
}

METHOD_IDLE_IMPL(M_smotor_larionov, lrm)
{
    status_t status = recalc_values(lrm);

    if(status == STATUS_READY){
        lrm->warnings = SMOTOR_LARIONOV_WARNING_NONE;
        lrm->status = STATUS_NONE;
    }else{
        lrm->warnings = SMOTOR_LARIONOV_WARNING_INVALID_PARAMS;
        lrm->status = STATUS_WARNING;
    }
}
