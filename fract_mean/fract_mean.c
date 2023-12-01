#include "fract_mean.h"
#include "iqmath/iqutils.h"



METHOD_INIT_IMPL(M_fract_mean, mean)
{
}

METHOD_DEINIT_IMPL(M_fract_mean, mean)
{
}

METHOD_CALC_IMPL(M_fract_mean, mean)
{
    // Поместим данные в буфер.
    mean->m_buf[mean->m_index] = mean->in_value;
    // Увеличим индекс.
    mean->m_index ++;
    // Кольцо.
    if(mean->m_index >= FRACT_MEAN_BUF_LEN) mean->m_index = 0;

    iq24_t val = 0;
    iq24_t sum_s = 0;
    iq24_t sum_l = 0;

    size_t index = mean->m_index;
    size_t i;
    // Цикл по малой части.
    #pragma GCC unroll 8
    for(i = 0; i < FRACT_MEAN_COUNT_S; i ++){
        index ++;
        if(index >= FRACT_MEAN_BUF_LEN) index = 0;

        val = mean->m_buf[index];

        sum_l = iq24_add(sum_l, val);
        sum_s = iq24_add(sum_s, val);
    }
    // Оставшееся значение для большой части.
    index ++;
    if(index >= FRACT_MEAN_BUF_LEN) index = 0;
    sum_l = iq24_add(sum_l, mean->m_buf[index]);

    // Компенсация разницы в задержке в 0.5 семпла.
    iq24_t sum_s_z05 = iql_mean2(sum_s, mean->m_sum_s_z1); //iq24_add(sum_s, mean->m_sum_s_z1) >> 1;
    mean->m_sum_s_z1 = sum_s;

    // res = Ks * sum_s + Kl * sum_l.
    iq24_t part_s = iq24_mul(sum_s_z05, FRACT_MEAN_KS);
    iq24_t part_l = iq24_mul(sum_l, FRACT_MEAN_KL);

    iq24_t res = iq24_add(part_s, part_l);

    mean->out_value = res;
}
