#include "mux4.h"
#include <stddef.h>
#include "bits/bits.h"
#include "utils/utils.h"



METHOD_INIT_IMPL(M_mux4, mux)
{
}

METHOD_DEINIT_IMPL(M_mux4, mux)
{
}

METHOD_CALC_IMPL(M_mux4, mux)
{
    size_t sel = mux->p_sel;

#if IS_POW2(MUX4_INPUTS)
    sel = sel & ((1 << GET_POW2(MUX4_INPUTS)) - 1);
#else //IS_POW2(MUX4_INPUTS)
    sel = MIN(sel, MUX4_INPUTS-1);
#endif

    mux->out_value = mux->in_value[sel];
}
