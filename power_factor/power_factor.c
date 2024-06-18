#include "power_factor.h"


METHOD_INIT_IMPL(M_power_factor, pf)
{
}

METHOD_DEINIT_IMPL(M_power_factor, pf)
{
}

METHOD_CALC_IMPL(M_power_factor, pf)
{
    iq24_t S, P, Q;

    iq24_t cos_phi = 0;
    iq24_t sin_phi = 0;
    iq24_t tan_phi = 0;

    S = pf->in_S;
    P = pf->in_P;
    Q = pf->in_Q;

    if(S != 0){
        cos_phi = iq24_div_sat(P, S);
        sin_phi = iq24_div_sat(Q, S);
    }

    if(P != 0){
        tan_phi = iq24_div_sat(Q, P);
    }

    pf->out_cos_phi = cos_phi;
    pf->out_sin_phi = sin_phi;
    pf->out_tan_phi = tan_phi;
}
