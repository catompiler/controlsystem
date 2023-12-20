#include "mux8.h"
#include <stddef.h>
#include "bits/bits.h"
#include "utils/utils.h"



METHOD_INIT_IMPL(M_mux8, mux)
{
}

METHOD_DEINIT_IMPL(M_mux8, mux)
{
}

METHOD_CALC_IMPL(M_mux8, mux)
{
    size_t sel = mux->p_sel;

#if IS_POW2(MUX8_INPUTS)
    sel = sel & ((1 << GET_POW2(MUX8_INPUTS)) - 1);
#else //IS_POW2(MUX8_INPUTS)
    sel = MIN(sel, MUX8_INPUTS-1);
#endif

    mux->out_value = mux->in_value[sel];
}
