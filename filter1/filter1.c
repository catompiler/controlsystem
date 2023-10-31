#include "filter1.h"


METHOD_INIT_IMPL(M_filter1, flt)
{
    IDLE((*flt));
}

METHOD_DEINIT_IMPL(M_filter1, flt)
{
}

METHOD_CALC_IMPL(M_filter1, flt)
{
    iq24_t x = flt->in_value;
    iq24_t y_z1 = flt->out_value;

    iq24_t xk = iq24_mul(flt->m_kx, x);
    iq24_t yk = iq24_mul(flt->m_ky, y_z1);

    iq24_t y = iq24_add(xk, yk);

    flt->out_value = y;
}

METHOD_IDLE_IMPL(M_filter1, flt)
{
    iq24_t T = flt->p_T;
    iq24_t Ts = flt->r_Ts;

    iq24_t T_Ts = iq24_add(T, Ts);

    iq24_t ky = iq24_div(T, T_Ts);
    iq24_t kx = iq24_div(Ts, T_Ts);

    flt->m_ky = ky;
    flt->m_kx = kx;
}
