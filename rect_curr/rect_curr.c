#include "rect_curr.h"
#include "utils/utils.h"
#include "modules/modules.h"


METHOD_INIT_IMPL(M_rect_curr, rc)
{
}

METHOD_DEINIT_IMPL(M_rect_curr, rc)
{
}

METHOD_CALC_IMPL(M_rect_curr, rc)
{
    iq24_t Ia, Ib, Ic, Ires;

    Ia = ABS(rc->in_Ia);
    Ib = ABS(rc->in_Ib);
    Ic = ABS(rc->in_Ic);

    Ires = MAX(Ia, Ib);
    Ires = MAX(Ires, Ic);

    // Ток относительно сети в ток относительно двигателя.
    Ires = iq24_mul(Ires, motor.r_k_I_mains_to_mot);

    rc->out_I = Ires;
}
