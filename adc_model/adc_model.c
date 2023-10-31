#include "adc_model.h"
#include "iqmath/iqmath.h"
#include "modules/modules.h"


static status_t recalc_values(M_adc_model* adc)
{
    status_t res_status = STATUS_READY;

    adc->m_Ua_gain = iq24_mul(adc->p_Ua_gain, conf.r_U_base_inv);
    adc->m_Ub_gain = iq24_mul(adc->p_Ub_gain, conf.r_U_base_inv);
    adc->m_Uc_gain = iq24_mul(adc->p_Uc_gain, conf.r_U_base_inv);

    return res_status;
}


METHOD_INIT_IMPL(M_adc_model, adc)
{
    adc->m_acnt = 0;

    IDLE((*adc));
}

METHOD_DEINIT_IMPL(M_adc_model, adc)
{
    adc->status = STATUS_NONE;
}

METHOD_CALC_IMPL(M_adc_model, adc)
{
    //if(!(adc->control & CONTROL_ENABLE)) return;

    /*
     * Сырые значения АЦП.
     */

    /*
     * Сетевое напряжение.
     */

    iq24_t angle = adc->m_acnt;

    iq24_t Ua_inst_k = iq24_mul(adc->in_U_scale, iq24_sin_pu(angle)); // 0
    iq24_t Ub_inst_k = iq24_mul(adc->in_U_scale, iq24_sin_pu(angle +     IQ24_2PI_PU/3)); // 120
    iq24_t Uc_inst_k = iq24_mul(adc->in_U_scale, iq24_sin_pu(angle + 2 * IQ24_2PI_PU/3)); // 240

    int32_t Ua_raw = iq24_mul(Ua_inst_k, ADC_MODEL_UPHASE_AMPL) + ADC_MODEL_OFFSET;
    int32_t Ub_raw = iq24_mul(Ub_inst_k, ADC_MODEL_UPHASE_AMPL) + ADC_MODEL_OFFSET;
    int32_t Uc_raw = iq24_mul(Uc_inst_k, ADC_MODEL_UPHASE_AMPL) + ADC_MODEL_OFFSET;

    adc->out_Ua_raw = Ua_raw;
    adc->out_Ub_raw = Ub_raw;
    adc->out_Uc_raw = Uc_raw;

    // Увеличим фазу.
    adc->m_acnt = (adc->m_acnt + iq24_mul(adc->in_F_scale, ADC_MODEL_SAMPLE_ANGLE_PU)) & IQ24_FRACT_MASK;

    /*
     * Значения относительно номинальных.
     */

    /*
     * Сетевое напряжение.
     */

    // IQ24 = IQ0 * IQ24.
    iq24_t Ua = (Ua_raw - adc->p_Ua_offset) * adc->m_Ua_gain;
    iq24_t Ub = (Ub_raw - adc->p_Ub_offset) * adc->m_Ub_gain;
    iq24_t Uc = (Uc_raw - adc->p_Uc_offset) * adc->m_Uc_gain;

    adc->out_Ua = Ua;
    adc->out_Ub = Ub;
    adc->out_Uc = Uc;

    // Установим статус.
    adc->status = STATUS_VALID;

    // Вызвать коллбэк.
    CALLBACK_CALL(adc->on_conversion);
}

METHOD_IDLE_IMPL(M_adc_model, adc)
{
    recalc_values(adc);
}
