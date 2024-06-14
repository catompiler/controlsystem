#include "power.h"
#include "bits/bits.h"


static void power_calc_S(M_power* pwr)
{
    pwr->out_S = iq24_mul_sat(pwr->in_rms_U, pwr->in_rms_I);
}

static void power_calc_P(M_power* pwr)
{
    liq24_t value;

    // Операции с буферами.

    // Буфер мгновенных мощностей.

    value = iq24_mull(pwr->in_U, pwr->in_I);

    pwr->m_p_sum -= pwr->m_p_data[pwr->m_p_put_index];
    pwr->m_p_data[pwr->m_p_put_index] = value;
    pwr->m_p_sum += value;

    // Индекс записи в конце буфера.
    if(pwr->m_p_put_index == (POWER_LEN - 1)){
        pwr->m_p_put_index = 0;
    }else{
        pwr->m_p_put_index ++;
    }

    if(pwr->m_p_count < POWER_LEN) pwr->m_p_count ++;

    // Вычисления.

    value = pwr->m_p_sum;

#if IS_POW2(POWER_LEN)
    value >>= GET_POW2(POWER_LEN);
#else //IS_POW2(POWER_LEN)
    value = (value * IQ24F(1, POWER_LEN)) >> 24;
#endif //IS_POW2(POWER_LEN)

    pwr->out_P = iq24_sat(value);
}

static void power_calc_Q(M_power* pwr)
{
    liq24_t value;

    // Операции с буферами.

    // Буфер сдвинутого тока.

    iq24_t U = pwr->m_uz_data[pwr->m_uz_put_index];

    pwr->m_uz_data[pwr->m_uz_put_index] = pwr->in_U;

    // Индекс записи в конце буфера.
    if(pwr->m_uz_put_index == (POWER_PI2_LEN - 1)){
        pwr->m_uz_put_index = 0;
    }else{
        pwr->m_uz_put_index ++;
    }

    // Буфер мгновенных мощностей.

    value = iq24_mull(U, pwr->in_I);

    pwr->m_q_sum -= pwr->m_q_data[pwr->m_q_put_index];
    pwr->m_q_data[pwr->m_q_put_index] = value;
    pwr->m_q_sum += value;

    // Индекс записи в конце буфера.
    if(pwr->m_q_put_index == (POWER_LEN - 1)){
        pwr->m_q_put_index = 0;
    }else{
        pwr->m_q_put_index ++;
    }

    if(pwr->m_q_count < POWER_LEN) pwr->m_q_count ++;

    // Вычисления.

    value = pwr->m_q_sum;

#if IS_POW2(POWER_LEN)
    value >>= GET_POW2(POWER_LEN);
#else //IS_POW2(POWER_LEN)
    value = (value * IQ24F(1, POWER_LEN)) >> 24;
#endif //IS_POW2(POWER_LEN)

    pwr->out_Q = iq24_sat(value);
}


METHOD_INIT_IMPL(M_power, pwr)
{
}

METHOD_DEINIT_IMPL(M_power, pwr)
{
}

METHOD_CALC_IMPL(M_power, pwr)
{
    if(!(pwr->control & CONTROL_ENABLE)) return;

    power_calc_S(pwr);
    power_calc_P(pwr);
    power_calc_Q(pwr);

    if(pwr->m_p_count == POWER_LEN && pwr->m_p_count == POWER_LEN){
        pwr->status = STATUS_VALID;
    }
}
