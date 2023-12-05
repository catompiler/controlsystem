#include "rms.h"
#include "bits/bits.h"
#include "iqmath/iqmath.h"


METHOD_INIT_IMPL(M_rms, rms)
{
}

METHOD_DEINIT_IMPL(M_rms, rms)
{
}


static void calc_rms(M_rms* rms)
{
    liq24_t acc = rms->m_sum;

#if IS_POW2(RMS_LEN)
    acc >>= GET_POW2(RMS_LEN);
#else //IS_POW2(RMS_LEN)
    acc = (acc * IQ24F(1, RMS_LEN)) >> 24;
#endif //IS_POW2(RMS_LEN)

    // Средний квадрат значений.
    iq24_t mean_sq = iq24_sat(acc);
    // Среднее квадратичное.
    iq24_t rms_value = iq24_sqrt(mean_sq);

    rms->out_value = rms_value;
}

METHOD_CALC_IMPL(M_rms, rms)
{
    if(!(rms->control & CONTROL_ENABLE)) return;

    iq24_t value_sq = iq24_mul(rms->in_value, rms->in_value);

    rms->m_sum -= rms->m_data[rms->m_put_index];
    rms->m_data[rms->m_put_index] = value_sq;
    rms->m_sum += value_sq;

    // Индекс записи в конце буфера.
    if(rms->m_put_index == (RMS_LEN - 1)){
        rms->m_put_index = 0;
    }else{
        rms->m_put_index ++;
    }

    if(rms->m_count < RMS_LEN) rms->m_count ++;

    // calc.
    calc_rms(rms);

    if(rms->m_count == RMS_LEN){
        rms->status = STATUS_VALID;
    }
}
