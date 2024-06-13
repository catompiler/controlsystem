#include "dc_mean.h"
#include "bits/bits.h"



METHOD_INIT_IMPL(M_dc_mean, mean)
{
}

METHOD_DEINIT_IMPL(M_dc_mean, mean)
{
}

METHOD_CALC_IMPL(M_dc_mean, mean)
{
    iq24_t val = mean->in_value;

    size_t index = mean->m_index;

    mean->m_sum -= mean->m_buf[index];
    mean->m_sum += val;

    mean->m_buf[index] = val;

    index ++;
    if(index >= DC_MEAN_BUF_LEN) index = 0;

    mean->m_index = index;

#if IS_POW2(DC_MEAN_BUF_LEN)
    mean->out_value = mean->m_sum >> GET_POW2(DC_MEAN_BUF_LEN);
#else //IS_POW2(DC_MEAN_BUF_LEN)
    mean->out_value = (mean->m_sum * IQ24F(1, DC_MEAN_BUF_LEN)) >> 24;
    //mean->out_value = iq24_sat(mean->m_sum / DC_MEAN_BUF_LEN);
#endif //IS_POW2(DC_MEAN_BUF_LEN)
}
