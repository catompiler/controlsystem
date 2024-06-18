#include "value_3phase.h"



METHOD_INIT_IMPL(M_value_3phase, v3ph)
{
}

METHOD_DEINIT_IMPL(M_value_3phase, v3ph)
{
}

METHOD_CALC_IMPL(M_value_3phase, v3ph)
{
    uint32_t sel;

    iq24_t A, B, C;

    A = v3ph->in_A;
    B = v3ph->in_B;
    C = v3ph->in_C;

    sel = v3ph->p_sel;

    switch(sel){
    default:
    case VALUE_3PHASE_CALC_NONE:
        break;
    case VALUE_3PHASE_CALC_A:
        A = - (B + C);
        break;
    case VALUE_3PHASE_CALC_B:
        B = - (C + A);
        break;
    case VALUE_3PHASE_CALC_C:
        C = - (A + B);
        break;
    }

    v3ph->out_A = A;
    v3ph->out_B = B;
    v3ph->out_C = C;
}
