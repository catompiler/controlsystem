#include "iqmath/iqmath.h"
#include "fake_adc.h"
#include "modules/modules.h"


static status_t recalc_values(M_fake_adc* adc)
{
    if(!(conf.status & STATUS_VALID)) return STATUS_NONE;

    status_t status = STATUS_READY;

    adc->m_Ua_gain = iq24_mul(adc->p_Ua_gain, conf.r_inv_U_nom);
    adc->m_Ub_gain = iq24_mul(adc->p_Ub_gain, conf.r_inv_U_nom);
    adc->m_Uc_gain = iq24_mul(adc->p_Uc_gain, conf.r_inv_U_nom);

    return status;
}


METHOD_INIT_IMPL(M_fake_adc, adc)
{
    adc->status = STATUS_NONE;
    adc->m_acnt = 0;

    status_t status = recalc_values(adc);

    if(status & STATUS_READY){
        adc->status = STATUS_READY;
    }
}

METHOD_DEINIT_IMPL(M_fake_adc, adc)
{
    adc->status = STATUS_NONE;
}

METHOD_CALC_IMPL(M_fake_adc, adc)
{
    if(!(adc->status & STATUS_READY)) return;

    /*
     * Сырые значения АЦП.
     */

    /*
     * Сетевое напряжение.
     */

    iq24_t angle = adc->m_acnt;

    iq24_t Ua_inst_k = iq24_sin_pu(angle); // 0
    iq24_t Ub_inst_k = iq24_sin_pu(angle +     IQ24_2PI_PU/3); // 120
    iq24_t Uc_inst_k = iq24_sin_pu(angle + 2 * IQ24_2PI_PU/3); // 240

    int32_t Ua_raw = iq24_mul(Ua_inst_k, ADC_UPHASE_AMPL) + ADC_OFFSET;
    int32_t Ub_raw = iq24_mul(Ub_inst_k, ADC_UPHASE_AMPL) + ADC_OFFSET;
    int32_t Uc_raw = iq24_mul(Uc_inst_k, ADC_UPHASE_AMPL) + ADC_OFFSET;

    adc->out_Ua_raw = Ua_raw;
    adc->out_Ub_raw = Ub_raw;
    adc->out_Uc_raw = Uc_raw;

    // Увеличим фазу.
    adc->m_acnt = (adc->m_acnt + ADC_SAMPLE_ANGLE_PU) & IQ24_FRACT_MASK;

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
    adc->status = STATUS_READY | STATUS_VALID;
}

METHOD_IDLE_IMPL(M_fake_adc, adc)
{
    status_t status = recalc_values(adc);

    if(status & STATUS_READY){
        adc->status |= STATUS_READY;
    }
}
