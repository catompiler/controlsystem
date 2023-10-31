#include "rms.h"
#include "bits/bits.h"
#include "iqmath/iqmath.h"


METHOD_INIT_IMPL(M_rms, rms)
{
    rms->m_count = 0;
    rms->m_put_index = 0;
}

METHOD_DEINIT_IMPL(M_rms, rms)
{
}


static void calc_rms(M_rms* rms)
{
    iq24_t* pvalues = (iq24_t*)&rms->m_data[0];

    iq24_t v0, v1, v2, v3;
    liq24_t acc = 0;

    int i;
    #pragma GCC unroll 8
    for(i = 0; i < (RMS_LEN / 4); i ++){
        v0 = *pvalues ++;
        v1 = *pvalues ++;
        v2 = *pvalues ++;
        v3 = *pvalues ++;

        acc += v0;
        acc += v1;
        acc += v2;
        acc += v3;
    }

    #pragma GCC unroll 4
    for(i = ((RMS_LEN / 4) * 4); i < RMS_LEN; i ++){
        acc += *pvalues ++;
    }

#if IS_POW2(RMS_LEN)
    acc >>= GET_POW2(RMS_LEN);
#else //IS_POW2(RMS_LEN)
    acc /= RMS_LEN;
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

    iq24_t value_sq = iq24_mul_sat(rms->in_value, rms->in_value);

    rms->m_data[rms->m_put_index] = value_sq;

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
