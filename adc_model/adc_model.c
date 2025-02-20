#include "adc_model.h"
#include "iqmath/iqmath.h"
#include "modules/modules.h"
#include "utils/utils.h"


static status_t recalc_values(M_adc_model* adc)
{
    status_t res_status = STATUS_READY;

    // Напряжения сети.
    adc->m_Ua_gain = iq24_mul(adc->p_Ua_gain, conf.r_U_base_inv);
    adc->m_Ub_gain = iq24_mul(adc->p_Ub_gain, conf.r_U_base_inv);
    adc->m_Uc_gain = iq24_mul(adc->p_Uc_gain, conf.r_U_base_inv);

    // Напряжения статора.
    adc->m_s_Ua_gain = iq24_mul(adc->p_s_Ua_gain, motor.r_s_U_base_inv);
    adc->m_s_Ub_gain = iq24_mul(adc->p_s_Ub_gain, motor.r_s_U_base_inv);
    adc->m_s_Uc_gain = iq24_mul(adc->p_s_Uc_gain, motor.r_s_U_base_inv);

    return res_status;
}


METHOD_INIT_IMPL(M_adc_model, adc)
{
    adc->m_mains_acnt = ADC_MODEL_MAINS_U_PHASE;
    adc->m_stator_acnt = ADC_MODEL_STATOR_U_PHASE;

    INIT(adc->m_clarke_inv);
    INIT(adc->m_s_clarke_inv);

    IDLE((*adc));
}

METHOD_DEINIT_IMPL(M_adc_model, adc)
{
    DEINIT(adc->m_s_clarke_inv);
    DEINIT(adc->m_clarke_inv);

    adc->status = STATUS_NONE;
}

/*
 * Сетевое напряжение.
 */
static void calc_Uabc(M_adc_model* adc)
{
    // Текущая фаза.
    iq24_t angle = adc->m_mains_acnt;

    // Увеличим фазу.
    adc->m_mains_acnt = (adc->m_mains_acnt + iq24_mul(adc->in_F_scale, ADC_MODEL_SAMPLE_ANGLE_PU)) & IQ24_FRACT_MASK;

    iq24_t Ualpha = iq24_mul(adc->in_U_scale, iq24_cos_pu(angle)); // 0
    iq24_t Ubeta  = iq24_mul(adc->in_U_scale, iq24_sin_pu(angle)); // 90

    adc->m_clarke_inv.in_A = Ualpha;
    adc->m_clarke_inv.in_B = Ubeta;
    CALC(adc->m_clarke_inv);

    iq24_t Ua_inst_k = adc->m_clarke_inv.out_A;
    iq24_t Ub_inst_k = adc->m_clarke_inv.out_B;
    iq24_t Uc_inst_k = adc->m_clarke_inv.out_C;

//    iq24_t Ua_inst_k = iq24_mul(adc->in_U_scale, iq24_sin_pu(angle)); // 0
//    iq24_t Ub_inst_k = iq24_mul(adc->in_U_scale, iq24_sin_pu(angle + 2 * IQ24_2PI_PU/3)); // 120
//    iq24_t Uc_inst_k = iq24_mul(adc->in_U_scale, iq24_sin_pu(angle + 1 * IQ24_2PI_PU/3)); // 240

    iq15_t Ua_adc = iq24_mul(Ua_inst_k, IQ15(ADC_MODEL_MAINS_U_AMPL_RAW));
    iq15_t Ub_adc = iq24_mul(Ub_inst_k, IQ15(ADC_MODEL_MAINS_U_AMPL_RAW));
    iq15_t Uc_adc = iq24_mul(Uc_inst_k, IQ15(ADC_MODEL_MAINS_U_AMPL_RAW));

    int32_t Ua_raw = iq15_int(iq15_round(Ua_adc)) + ADC_MODEL_MAINS_U_OFFSET;
    int32_t Ub_raw = iq15_int(iq15_round(Ub_adc)) + ADC_MODEL_MAINS_U_OFFSET;
    int32_t Uc_raw = iq15_int(iq15_round(Uc_adc)) + ADC_MODEL_MAINS_U_OFFSET;

    Ua_raw = CLAMP(Ua_raw, ADC_MODEL_MAINS_RAW_MIN, ADC_MODEL_MAINS_RAW_MAX);
    Ub_raw = CLAMP(Ub_raw, ADC_MODEL_MAINS_RAW_MIN, ADC_MODEL_MAINS_RAW_MAX);
    Uc_raw = CLAMP(Uc_raw, ADC_MODEL_MAINS_RAW_MIN, ADC_MODEL_MAINS_RAW_MAX);

//    int32_t Ua_raw = iq24_mul(Ua_inst_k, ADC_MODEL_MAINS_U_AMPL_RAW) + ADC_MODEL_MAINS_U_OFFSET;
//    int32_t Ub_raw = iq24_mul(Ub_inst_k, ADC_MODEL_MAINS_U_AMPL_RAW) + ADC_MODEL_MAINS_U_OFFSET;
//    int32_t Uc_raw = iq24_mul(Uc_inst_k, ADC_MODEL_MAINS_U_AMPL_RAW) + ADC_MODEL_MAINS_U_OFFSET;

    adc->out_Ua_raw = Ua_raw;
    adc->out_Ub_raw = Ub_raw;
    adc->out_Uc_raw = Uc_raw;

    // IQ24 = IQ0 * IQ24.
    iq24_t Ua = (Ua_raw - adc->p_Ua_offset) * adc->m_Ua_gain;
    iq24_t Ub = (Ub_raw - adc->p_Ub_offset) * adc->m_Ub_gain;
    iq24_t Uc = (Uc_raw - adc->p_Uc_offset) * adc->m_Uc_gain;

    adc->out_Ua = Ua;
    adc->out_Ub = Ub;
    adc->out_Uc = Uc;
}

/*
 * Напряжение статора.
 */
static void calc_s_Uabc(M_adc_model* adc)
{
    // Текущая фаза.
    iq24_t angle = adc->m_stator_acnt;

    // Увеличим фазу.
    adc->m_stator_acnt = (adc->m_stator_acnt + iq24_mul(adc->in_s_F_scale, ADC_MODEL_SAMPLE_ANGLE_PU)) & IQ24_FRACT_MASK;

    iq24_t Ualpha = iq24_mul(adc->in_s_U_scale, iq24_cos_pu(angle)); // 0
    iq24_t Ubeta  = iq24_mul(adc->in_s_U_scale, iq24_sin_pu(angle)); // 90

    adc->m_s_clarke_inv.in_A = Ualpha;
    adc->m_s_clarke_inv.in_B = Ubeta;
    CALC(adc->m_s_clarke_inv);

#if defined(ADC_MODEL_MAINS_U_ABC) && ADC_MODEL_MAINS_U_ABC == 0
    iq24_t Ua_inst_k = adc->m_s_clarke_inv.out_A;
    iq24_t Ub_inst_k = adc->m_s_clarke_inv.out_B;
    iq24_t Uc_inst_k = adc->m_s_clarke_inv.out_C;
#else
    iq24_t Ua_inst_k = adc->m_s_clarke_inv.out_A;
    iq24_t Ub_inst_k = adc->m_s_clarke_inv.out_C;
    iq24_t Uc_inst_k = adc->m_s_clarke_inv.out_B;
#endif

//    iq24_t Ua_inst_k = iq24_mul(adc->in_s_U_scale, iq24_sin_pu(angle)); // 0
//    iq24_t Ub_inst_k = iq24_mul(adc->in_s_U_scale, iq24_sin_pu(angle + 2 * IQ24_2PI_PU/3)); // 120
//    iq24_t Uc_inst_k = iq24_mul(adc->in_s_U_scale, iq24_sin_pu(angle + 1 * IQ24_2PI_PU/3)); // 240

    iq15_t Ua_adc = iq24_mul(Ua_inst_k, IQ15(ADC_MODEL_STATOR_U_AMPL_RAW));
    iq15_t Ub_adc = iq24_mul(Ub_inst_k, IQ15(ADC_MODEL_STATOR_U_AMPL_RAW));
    iq15_t Uc_adc = iq24_mul(Uc_inst_k, IQ15(ADC_MODEL_STATOR_U_AMPL_RAW));

    int32_t Ua_raw = iq15_int(iq15_round(Ua_adc)) + ADC_MODEL_STATOR_U_OFFSET;
    int32_t Ub_raw = iq15_int(iq15_round(Ub_adc)) + ADC_MODEL_STATOR_U_OFFSET;
    int32_t Uc_raw = iq15_int(iq15_round(Uc_adc)) + ADC_MODEL_STATOR_U_OFFSET;

    Ua_raw = CLAMP(Ua_raw, ADC_MODEL_STATOR_RAW_MIN, ADC_MODEL_STATOR_RAW_MAX);
    Ub_raw = CLAMP(Ub_raw, ADC_MODEL_STATOR_RAW_MIN, ADC_MODEL_STATOR_RAW_MAX);
    Uc_raw = CLAMP(Uc_raw, ADC_MODEL_STATOR_RAW_MIN, ADC_MODEL_STATOR_RAW_MAX);

//    int32_t Ua_raw = iq24_mul(Ua_inst_k, ADC_MODEL_STATOR_U_AMPL_RAW) + ADC_MODEL_STATOR_U_OFFSET;
//    int32_t Ub_raw = iq24_mul(Ub_inst_k, ADC_MODEL_STATOR_U_AMPL_RAW) + ADC_MODEL_STATOR_U_OFFSET;
//    int32_t Uc_raw = iq24_mul(Uc_inst_k, ADC_MODEL_STATOR_U_AMPL_RAW) + ADC_MODEL_STATOR_U_OFFSET;

    adc->out_s_Ua_raw = Ua_raw;
    adc->out_s_Ub_raw = Ub_raw;
    adc->out_s_Uc_raw = Uc_raw;

    // IQ24 = IQ0 * IQ24.
    iq24_t Ua = (Ua_raw - adc->p_s_Ua_offset) * adc->m_s_Ua_gain;
    iq24_t Ub = (Ub_raw - adc->p_s_Ub_offset) * adc->m_s_Ub_gain;
    iq24_t Uc = (Uc_raw - adc->p_s_Uc_offset) * adc->m_s_Uc_gain;

    adc->out_s_Ua = Ua;
    adc->out_s_Ub = Ub;
    adc->out_s_Uc = Uc;
}


METHOD_CALC_IMPL(M_adc_model, adc)
{
    //if(!(adc->control & CONTROL_ENABLE)) return;

    calc_Uabc(adc);
    calc_s_Uabc(adc);

    // Установим статус.
    adc->status = STATUS_VALID;

    // Вызвать коллбэк.
    CALLBACK_CALL(adc->on_conversion);
}

METHOD_IDLE_IMPL(M_adc_model, adc)
{
    recalc_values(adc);
}
