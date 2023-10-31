#include "adc.h"
#include "iqmath/iqmath.h"
#include "modules/modules.h"


static status_t recalc_values(M_adc* adc)
{
    status_t res_status = STATUS_READY;

    // Напряжения сети.
    adc->m_Ua_gain = iq24_mul(adc->p_Ua_gain, conf.r_U_base_inv);
    adc->m_Ub_gain = iq24_mul(adc->p_Ub_gain, conf.r_U_base_inv);
    adc->m_Uc_gain = iq24_mul(adc->p_Uc_gain, conf.r_U_base_inv);

    // Токи сети.
    adc->m_Ia_gain = iq24_mul(adc->p_Ia_gain, conf.r_I_base_inv);
    adc->m_Ib_gain = iq24_mul(adc->p_Ib_gain, conf.r_I_base_inv);
    adc->m_Ic_gain = iq24_mul(adc->p_Ic_gain, conf.r_I_base_inv);

    // Напряжение выхода.
    adc->m_Uarm_gain = iq24_mul(adc->p_Uarm_gain, conf.r_U_base_inv);

    // Ток выхода.
    adc->m_Iarm_gain = iq24_mul(adc->p_Iarm_gain, conf.r_I_base_inv);

    return res_status;
}


METHOD_INIT_IMPL(M_adc, adc)
{
    IDLE((*adc));
}

METHOD_DEINIT_IMPL(M_adc, adc)
{
    adc->status = STATUS_NONE;
}

METHOD_CALC_IMPL(M_adc, adc)
{
    //if(!(adc->control & CONTROL_ENABLE)) return;

    /*
     * Сырые значения АЦП.
     */

    /*
     * Сетевое напряжение.
     */
    int32_t Ua_raw = 0;
    int32_t Ub_raw = 0;
    int32_t Uc_raw = 0;

    adc->out_Ua_raw = Ua_raw;
    adc->out_Ub_raw = Ub_raw;
    adc->out_Uc_raw = Uc_raw;

    /*
     * Сетевой ток.
     */
    int32_t Ia_raw = 0;
    int32_t Ib_raw = 0;
    int32_t Ic_raw = 0;

    adc->out_Ia_raw = Ia_raw;
    adc->out_Ib_raw = Ib_raw;
    adc->out_Ic_raw = Ic_raw;

    /*
     * Напряжение выхода.
     */
    int32_t Uarm_raw = 0;

    adc->out_Uarm_raw = Uarm_raw;

    /*
     * Ток выхода.
     */
    int32_t Iarm_raw = 0;

    adc->out_Iarm_raw = Iarm_raw;

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

    /*
     * Сетевой ток.
     */
    // IQ24 = IQ0 * IQ24.
    iq24_t Ia = (Ia_raw - adc->p_Ia_offset) * adc->m_Ia_gain;
    iq24_t Ib = (Ib_raw - adc->p_Ib_offset) * adc->m_Ib_gain;
    iq24_t Ic = (Ic_raw - adc->p_Ic_offset) * adc->m_Ic_gain;

    adc->out_Ia = Ia;
    adc->out_Ib = Ib;
    adc->out_Ic = Ic;

    /*
     * Напряжение выхода.
     */
    // IQ24 = IQ0 * IQ24.
    iq24_t Uarm = (Uarm_raw - adc->p_Uarm_offset) * adc->m_Uarm_gain;

    adc->out_Uarm = Uarm;

    /*
     * Ток выхода.
     */
    // IQ24 = IQ0 * IQ24.
    iq24_t Iarm = (Iarm_raw - adc->p_Iarm_offset) * adc->m_Iarm_gain;

    adc->out_Iarm = Iarm;

    // Установим статус.
    adc->status = STATUS_VALID;

    // Вызвать коллбэк.
    CALLBACK_CALL(adc->on_conversion);
}

METHOD_IDLE_IMPL(M_adc, adc)
{
    recalc_values(adc);
}
