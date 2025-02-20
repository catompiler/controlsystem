#include "prot.h"
#include "modules/modules.h"
#include "iqmath/iqmath.h"


static status_t recalc_values(M_prot* prot)
{
    status_t res_status = STATUS_READY;

    return res_status;
}


METHOD_INIT_IMPL(M_prot, prot)
{
    INIT(prot->r_mains_lost_timer);
    INIT(prot->r_mains_invalid_timer);
    INIT(prot->r_mains_undervoltage_timer);
    INIT(prot->r_mains_overvoltage_timer);
    INIT(prot->r_overcurrent_timer);
    INIT(prot->r_overvoltage_timer);
    //INIT(prot->r_);

    IDLE((*prot));
}

METHOD_DEINIT_IMPL(M_prot, prot)
{
    DEINIT(prot->r_mains_lost_timer);
    DEINIT(prot->r_mains_invalid_timer);
    DEINIT(prot->r_mains_undervoltage_timer);
    DEINIT(prot->r_mains_overvoltage_timer);
    DEINIT(prot->r_overcurrent_timer);
    DEINIT(prot->r_overvoltage_timer);
}

static error_t prot_calc_error(M_timer_on* tmr, flag_t trig_value, error_t error_mask, error_t errors)
{
    tmr->in_value = trig_value;
    CALC((*tmr));

    error_t error_state = (tmr->out_value != FLAG_NONE) ? error_mask : 0;

    return (errors & ~error_mask) | error_state;
}

static void prot_calc_mains_lost(M_prot* prot)
{
    flag_t value = FLAG_NONE;

    value |= rms_Ua.out_value < prot->p_mains_lost_U_low;
    value |= rms_Ub.out_value < prot->p_mains_lost_U_low;
    value |= rms_Uc.out_value < prot->p_mains_lost_U_low;

    prot->raw_errors1 = prot_calc_error(&prot->r_mains_lost_timer, value, PROT_ERR1_MAINS_LOST, prot->raw_errors1);
}

static void prot_calc_mains_invalid(M_prot* prot)
{
    flag_t value = FLAG_NONE;

    iq24_t Aa = phase_ampl_Ua.out_phase;
    iq24_t Ab = phase_ampl_Ub.out_phase;
    iq24_t Ac = phase_ampl_Uc.out_phase;

    iq24_t Aab = Aa - Ab;
    iq24_t Abc = Ab - Ac;
    iq24_t Aca = Ac - Aa;

    if(Aab < 0) Aab += IQ24_2PI_PU;
    if(Abc < 0) Abc += IQ24_2PI_PU;
    if(Aca < 0) Aca += IQ24_2PI_PU;

    iq24_t dAab = iq24_abs(Aab - IQ24_2PI_PU / 3);
    iq24_t dAbc = iq24_abs(Abc - IQ24_2PI_PU / 3);
    iq24_t dAca = iq24_abs(Aca - IQ24_2PI_PU / 3);

//    float fAab = (360.0f/(1<<24))*(Aab);
//    float fAbc = (360.0f/(1<<24))*(Abc);
//    float fAca = (360.0f/(1<<24))*(Aca);

    iq24_t F = IQ_N_TO_M(conf.r_f_base, 15, 24);
    iq24_t dFa = iq24_abs(filter_freq_Ua.out_value - F);
    iq24_t dFb = iq24_abs(filter_freq_Ub.out_value - F);
    iq24_t dFc = iq24_abs(filter_freq_Uc.out_value - F);

    value |= dAab > prot->p_mains_invalid_A_delta;
    value |= dAbc > prot->p_mains_invalid_A_delta;
    value |= dAca > prot->p_mains_invalid_A_delta;

    value |= dFa > prot->p_mains_invalid_F_delta;
    value |= dFb > prot->p_mains_invalid_F_delta;
    value |= dFc > prot->p_mains_invalid_F_delta;

    prot->raw_errors1 = prot_calc_error(&prot->r_mains_invalid_timer, value, PROT_ERR1_MAINS_INVALID, prot->raw_errors1);
}

static void prot_calc_mains_undervoltage(M_prot* prot)
{
    flag_t value = FLAG_NONE;

    value |= rms_Ua.out_value < prot->p_mains_undervoltage_U_low;
    value |= rms_Ub.out_value < prot->p_mains_undervoltage_U_low;
    value |= rms_Uc.out_value < prot->p_mains_undervoltage_U_low;

    prot->raw_errors1 = prot_calc_error(&prot->r_mains_undervoltage_timer, value, PROT_ERR1_MAINS_UNDERVOLTAGE, prot->raw_errors1);
}

static void prot_calc_mains_overvoltage(M_prot* prot)
{
    flag_t value = FLAG_NONE;

    value |= rms_Ua.out_value > prot->p_mains_overvoltage_U_hi;
    value |= rms_Ub.out_value > prot->p_mains_overvoltage_U_hi;
    value |= rms_Uc.out_value > prot->p_mains_overvoltage_U_hi;

    prot->raw_errors1 = prot_calc_error(&prot->r_mains_overvoltage_timer, value, PROT_ERR1_MAINS_OVERVOLTAGE, prot->raw_errors1);
}

static void prot_calc_mains_overcurrent(M_prot* prot)
{
    flag_t value = FLAG_NONE;

    value |= rms_Ia.out_value > prot->p_mains_overcurrent_I_hi;
    value |= rms_Ib.out_value > prot->p_mains_overcurrent_I_hi;
    value |= rms_Ic.out_value > prot->p_mains_overcurrent_I_hi;

    prot->raw_errors1 = prot_calc_error(&prot->r_mains_overcurrent_timer, value, PROT_ERR1_MAINS_OVERCURRENT, prot->raw_errors1);
}

static void prot_calc_overvoltage(M_prot* prot)
{
    flag_t value = FLAG_NONE;

    value |= mean_Uarm.out_value > prot->p_overvoltage_U_hi;

    prot->raw_errors1 = prot_calc_error(&prot->r_overvoltage_timer, value, PROT_ERR1_OVERVOLTAGE, prot->raw_errors1);
}

static void prot_calc_overcurrent(M_prot* prot)
{
    flag_t value = FLAG_NONE;

    value |= mean_Iarm.out_value > prot->p_overcurrent_I_hi;

    prot->raw_errors1 = prot_calc_error(&prot->r_overcurrent_timer, value, PROT_ERR1_OVERCURRENT, prot->raw_errors1);
}

//static void prot_calc_(M_prot* prot)
//{
//}

METHOD_CONTROL_IMPL(M_prot, prot)
{
    if(prot->control & CONTROL_RESET){
        prot->errors0 = ERROR_NONE;
        prot->errors1 = ERROR_NONE;
        prot->errors2 = ERROR_NONE;

        prot->control &= ~CONTROL_RESET;
    }
}

METHOD_CALC_IMPL(M_prot, prot)
{
    CONTROL((*prot));

    prot_calc_mains_lost(prot);
    prot_calc_mains_invalid(prot);
    prot_calc_mains_undervoltage(prot);
    prot_calc_mains_overvoltage(prot);
    prot_calc_mains_overcurrent(prot);
    prot_calc_overvoltage(prot);
    prot_calc_overcurrent(prot);

    error_t errors0 = prot->errors0 | (prot->raw_errors0 & prot->mask_errors0);
    error_t errors1 = prot->errors1 | (prot->raw_errors1 & prot->mask_errors1);
    error_t errors2 = prot->errors2 | (prot->raw_errors2 & prot->mask_errors2);

    error_t any_errors = errors0 | errors1 | errors2;

    error_t new_errors0 = errors0 ^ prot->errors0;
    error_t new_errors1 = errors1 ^ prot->errors1;
    error_t new_errors2 = errors2 ^ prot->errors2;

    error_t any_new_errors = new_errors0 | new_errors1 | new_errors2;

    prot->out_has_errors = (any_errors == 0) ? FLAG_NONE : FLAG_ACTIVE;
    prot->out_error_occured = (any_new_errors == 0) ? FLAG_NONE : FLAG_ACTIVE;

    prot->errors0 = errors0;
    prot->errors1 = errors1;
    prot->errors2 = errors2;
}

METHOD_IDLE_IMPL(M_prot, prot)
{
    recalc_values(prot);
}
