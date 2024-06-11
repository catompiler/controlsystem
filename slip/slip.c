#include "slip.h"
#include "modules/modules.h"


METHOD_INIT_IMPL(M_slip, slip)
{
}

METHOD_DEINIT_IMPL(M_slip, slip)
{
}

METHOD_CALC_IMPL(M_slip, slip)
{
    if(slip->control & CONTROL_ENABLE){

        iq24_t w = slip->in_value;
        iq24_t w0_inv = motor.r_f_base_inv;

        // s = 1 - (w0 - w)/w0 = w/w0 = w*w0_inv.
        iq24_t res = iq24_mul(w, w0_inv);
        //iq24_t res = iq24_sub(IQ24I(1), tmp);

        slip->out_value = res;

        slip->status = STATUS_VALID;
    }
}
